/*******************************************************
 *  Pellardy Maxime                  14/09/2026
 *  Fonction du projet
 *
 *******************************************************/


#include "mainwindow.h"
#include "ui_mainwindow.h"

#define LOCAL_EDGE "Local"

using namespace Automation::BDaq;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Etats de départ
    bancDemarre = false;
    roueFixee = false;
    ancienneKey1 = false;


    // =================================
    // INITIALISATION DE LA CARTE
    // =================================

    QString desc = "USB-4704,BID#0";

    instantDiCtrl = InstantDiCtrl::Create();
    instantDoCtrl = InstantDoCtrl::Create();

    std::wstring description = desc.toStdWString();

    DeviceInformation selected(description.c_str());

    instantDiCtrl->setSelectedDevice(selected);
    instantDoCtrl->setSelectedDevice(selected);

    portCount = instantDiCtrl->getPortCount();


    // =================================
    // CONFIGURATION DES SLIDERS
    // =================================

    // Slider étrier gauche
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(65);
    ui->horizontalSlider->setValue(20);

    // Slider étrier droit
    ui->horizontalSlider_2->setMinimum(0);
    ui->horizontalSlider_2->setMaximum(65);
    ui->horizontalSlider_2->setValue(20);

    // Le slider droit se déplace dans l'autre sens
    ui->horizontalSlider->setInvertedAppearance(true);


    // =================================
    // BOUTON DEMARRAGE DU BANC
    // =================================

    connect(ui->btnDemarrage, &QPushButton::clicked,
            this, [this]()
            {
                bancDemarre = !bancDemarre;

                if (bancDemarre)
                {
                    ui->btnDemarrage->setText("ARRETER");

                    ui->labelEtatBanc->setText("BANC DEMARRE");
                    ui->labelEtatGeneral->setText("Banc prêt");
                }
                else
                {
                    bancDemarre = false;
                    roueFixee = false;

                    ui->btnDemarrage->setText("DEMARRER");

                    ui->labelEtatBanc->setText("BANC ARRETE");
                    ui->labelEtatEtrier->setText("ROUE NON FIXEE");
                    ui->labelEtatGeneral->setText("Banc arrêté");

                    ui->btnDemarrerTest->setEnabled(false);
                }
            });


    // =================================
    // TIMER
    // =================================

    myTimer = new QTimer(this);

    connect(myTimer,
            &QTimer::timeout,
            this,
            &MainWindow::lectureDI);

    // Lecture toutes les 100 ms
    myTimer->start(100);
}


MainWindow::~MainWindow()
{
    delete ui;
}


// =================================
// LECTURE DES BOUTONS
// =================================

void MainWindow::lectureDI()
{
    quint8 *portStates = new quint8[portCount];

    // Lecture de la carte USB-4704
    instantDiCtrl->Read(0, 1, portStates);


    // =================================
    // LECTURE DES TOUCHES
    // =================================

    // Boutons actifs à 0

    bool key1 = !(portStates[0] & 0x01); // KEY1 = démarrage
    bool key2 = !(portStates[0] & 0x02); // KEY2 = avance
    bool key3 = !(portStates[0] & 0x04); // KEY3 = recule
    bool key4 = !(portStates[0] & 0x08); // KEY4 = desserre
    bool key5 = !(portStates[0] & 0x10); // KEY5 = serre

    // =================================
    // KEY1 : DEMARRER / ARRETER
    // =================================

    if (key1 && !ancienneKey1)
    {
        bancDemarre = !bancDemarre;

        if (bancDemarre)
        {
            ui->labelEtatBanc->setText("BANC DEMARRE");
            ui->labelEtatGeneral->setText("Banc prêt");
        }
        else
        {
            roueFixee = false;

            ui->labelEtatBanc->setText("BANC ARRETE");
            ui->labelEtatEtrier->setText("ROUE NON FIXEE");
            ui->labelEtatGeneral->setText("Banc arrêté");

            ui->btnDemarrerTest->setEnabled(false);
        }
    }

    ancienneKey1 = key1;


    // =================================
    // ROUE : AVANCE
    // =================================

    if (key2 && bancDemarre && roueFixee)
    {
        int position = ui->labelRoue_2->x();

        if (position < 100)
            position++;

        ui->labelRoue_2->move(position, ui->labelRoue_2->y());

        ui->labelEtatGeneral->setText("ROUE : AVANCE");
    }


    // =================================
    // ROUE : RECULE
    // =================================

    if (key3 && bancDemarre && roueFixee)
    {
        int position = ui->labelRoue_2->x();

        if (position > 0)
            position--;

        ui->labelRoue_2->move(position, ui->labelRoue_2->y());

        ui->labelEtatGeneral->setText("ROUE : RECUL");
    }

    // =================================
    // DESSERRAGE DE L'ETRIER
    // =================================

    if (key4 && bancDemarre)
    {
        int gauche = ui->horizontalSlider_2->value();
        int droite = ui->horizontalSlider->value();

        // Diminution jusqu'à 0
        if (gauche > 0)
            gauche--;

        if (droite > 0)
            droite--;

        // Mise à jour
        ui->horizontalSlider_2->setValue(gauche);
        ui->horizontalSlider->setValue(droite);

        // La roue n'est plus fixée
        roueFixee = false;

        ui->labelEtatEtrier->setText("DESSERRAGE...");
        ui->labelEtatGeneral->setText("ROUE NON FIXEE");
    }
    // =================================
    // SERRAGE DE L'ETRIER
    // =================================

    if (key5 && bancDemarre)
    {
        int gauche = ui->horizontalSlider_2->value();
        int droite = ui->horizontalSlider->value();

        // Augmentation jusqu'à 65
        if (gauche < 65)
            gauche++;

        if (droite < 65)
            droite++;

        // Bloque les valeurs à 65
        if (gauche > 65)
            gauche = 65;

        if (droite > 65)
            droite = 65;

        // Mise à jour des deux côtés
        ui->horizontalSlider_2->setValue(gauche);
        ui->horizontalSlider->setValue(droite);


        // Vérification du serrage
        if (gauche >= 65 && droite >= 65)
        {
            roueFixee = true;

            ui->labelEtatEtrier->setText("ROUE FIXEE");
            ui->labelEtatGeneral->setText("ROUE FIXEE");
        }
        else
        {
            roueFixee = false;

            ui->labelEtatEtrier->setText("SERRAGE...");
            ui->labelEtatGeneral->setText("Serrage de la roue");
        }
    }


    // =================================
    // AUTORISATION DU TEST
    // =================================

    if (bancDemarre && roueFixee)
    {
        ui->btnDemarrerTest->setEnabled(true);
    }
    else
    {
        ui->btnDemarrerTest->setEnabled(false);
    }


    delete[] portStates;
}

