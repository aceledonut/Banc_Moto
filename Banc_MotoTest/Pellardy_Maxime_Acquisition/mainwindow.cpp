#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Création d'un objet de la classe Acquisition_USB_4704
    mes_Acquisitions = new Acquisition_USB_4704();

    myTimer = new QTimer();

    connect(myTimer,&QTimer::timeout,this,&MainWindow::afficher);

    myTimer->start(1000);
}
void MainWindow::afficher()
{
    //Mise à jour des données
    mes_Acquisitions->acquerir_donnees_mecaniques();


    //Mise en mémoire des données acquéries
    DonneesMecaniques mesDonnees = mes_Acquisitions->get_sMecanique_data();


    //Affichage en QDebug
    qDebug()<<"Valeur de vitesse :"<< mesDonnees.vitesse;
    qDebug()<<"Valeur de régime :"<< mesDonnees.regime;
    qDebug()<<"-----------------------------------------------------------";
}
MainWindow::~MainWindow()
{
    delete ui;
}
