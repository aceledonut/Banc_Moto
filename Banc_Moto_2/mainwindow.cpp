/*******************************************************
 *  Pellardy Maxime                  14/09/2026
 *  Fonction du projet
 *
 *******************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Création de l'objet Acquisition
    mes_Acquisitions = new Acquisition();

    // Bouton Enregistrer / Acquisition
    connect(ui->pushButton,&QPushButton::clicked, this, &MainWindow::saveDonnees);

    // Timer
    myTimer = new QTimer(this);

    connect(myTimer, &QTimer::timeout, this, &MainWindow::lectureAI);

    // Lecture toutes les 100 ms
    myTimer->start(100);

    // Configuration des compteurs
    ui->compteurRegime->setMaximum(18000);
    ui->compteurRegime->setUnit("tr/min");

    ui->compteurVitesse->setMaximum(300);
    ui->compteurVitesse->setUnit("km/h");
}


void MainWindow::saveDonnees()
{
    // Demande à la classe Acquisition de faire une mesure
    mes_Acquisitions->acquerir_donnees_mecanique();

    // Récupération de la structure
    donnees_mecaniques donnees;

    donnees = mes_Acquisitions->get_sMecaniques_data();

    // Affichage du régime
    ui->labelRegime->setText(QString::number(donnees.regime) );

    // Affichage de la vitesse
    ui->labelVitesse->setText(QString::number(donnees.vitesse));

    // Affichage de la puissance
    ui->labelPuissance->setText(QString::number(donnees.puissance));

    // Affichage du couple
    ui->labelCouple->setText( QString::number(donnees.couple));

}

void MainWindow::lectureAI()
{
    // Demande une nouvelle acquisition
    mes_Acquisitions->acquerir_donnees_mecanique();

    // Récupération de la structure
    donnees = mes_Acquisitions->get_sMecaniques_data();

    // Affichage LCD
    ui->lcdNumber->display(donnees.regime);
    ui->lcdVitesse->display(donnees.vitesse);

    // Déplacement des aiguilles
    ui->compteurRegime->setValue(donnees.regime);
    ui->compteurVitesse->setValue(donnees.vitesse);
}


MainWindow::~MainWindow()
{
    delete mes_Acquisitions;
    delete ui;
}
