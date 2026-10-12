//-------------------------------------------------------------
// Test de connection à une base de donnée en utilisant
// un compilateur et la librairie mysql 32bits
//  fab 2024    V1.0
//-------------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"
//-----------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
//-----------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//----------------------------------------------
void MainWindow::on_pushButton_clicked()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    qDebug()<<db.driver();

        db.setHostName("localhost");
        db.setUserName("root");
        db.setPassword("");
        db.setDatabaseName("cdi");
        if (db.open())
                    QMessageBox::information(this,"connexion", "connexion au serveur réussi");
              else
                    QMessageBox::information(this,"Problème","connexion au serveur a echoué");


}
//----------------------------------------------
