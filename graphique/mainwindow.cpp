#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts>
#include <cmath>

//-------------------------------------
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //------création de mon objet chart-------------------------
    monchart=new QChart();
    monchart->setTitle("Valeurs du Banc de Moto");

    //----------création d'une series donc ---------------------
    vitesse=new QLineSeries();

    regime=new QLineSeries();
    QPen rouge(QRgb(0xff0000));
    regime->setPen(rouge);

    couple=new QLineSeries();
    QPen vert(QRgb(0x008000));
    couple->setPen(vert);

    puissance=new QLineSeries();
    QPen noir(QRgb(0x000000));
    puissance->setPen(noir);

    // QPen moncrayon(QRgb(0xff7f50));        //pour une courbe rouge
    // macourbe->setPen(moncrayon);
    //----------attacher la courbe au chart----------------------
    monchart->addSeries(vitesse);
    vitesse->setName("Vitesse (en km/h)");
    monchart->addSeries(regime);
    regime->setName("Régime (t/min)");
    monchart->addSeries(couple);
    couple->setName("Couple (en N.m)");
    monchart->addSeries(puissance);
    puissance->setName("Puissance (en kW)");
    //---------gérer les axes------------------------------------
    axe_X=new QValueAxis();
    axe_Y=new QValueAxis();
    axe_Y_regime=new QValueAxis();
    monchart->addAxis(axe_X,Qt::AlignBottom);
    monchart->addAxis(axe_Y,Qt::AlignLeft);
    monchart->addAxis(axe_Y_regime,Qt::AlignRight);

    //--------attacher sa serie  (courbe)--------aux axes--------
    vitesse->attachAxis(axe_X);
    vitesse->attachAxis(axe_Y);

    regime->attachAxis(axe_X);
    regime->attachAxis(axe_Y_regime);

    couple->attachAxis(axe_X);
    couple->attachAxis(axe_Y);

    puissance->attachAxis(axe_X);
    puissance->attachAxis(axe_Y);

    axe_X->setRange(0,30);
    axe_X->setTitleText("Temps");

    axe_Y->setRange(0,350);
    axe_Y->setTitleText("Vitesse/Couple/Puissance");

    axe_Y_regime->setRange(0,18000);
    axe_Y_regime->setTitleText("Régime");

    monchart->setAnimationOptions(QChart::AllAnimations);   //animation à l'ouverture du chart

    chartView = new QChartView(monchart);
    chartView->setRenderHint(QPainter::Antialiasing);         //quand la courbe est tracée

    ui->verticalLayout->addWidget(chartView);

    x=0;

    mes_Acquisitions = new Acquisition_USB_4704();

    myTimer = new QTimer();

    connect(myTimer,&QTimer::timeout,this,&MainWindow::dessiner);
}
//---------------------------------------

void MainWindow::on_pushButton_clicked()
{
    myTimer->start(ui->lineEdit->text().toInt());
}

void MainWindow::on_pushButton_clicked_3()
{
    myTimer->stop();
}

void MainWindow::dessiner()
{
    //Mise à jour des données
    mes_Acquisitions->acquerir_donnees_mecaniques();


    //Mise en mémoire des données acquéries
    DonneesMecaniques mesDonnees = mes_Acquisitions->get_sMecanique_data();


    vitesse->append(x,mesDonnees.vitesse);
    regime->append(x,mesDonnees.regime);
    couple->append(x,mesDonnees.couple);
    puissance->append(x,mesDonnees.puissance);
    x+=(myTimer->interval()/1000.0);
}
//---------------------------------------
MainWindow::~MainWindow()
{
    delete monchart;
    delete vitesse;
    delete regime;
    delete couple;
    delete puissance;
    delete ui;
}

