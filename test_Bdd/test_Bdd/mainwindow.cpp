//-------------------------------------------------------------
// Test de connection à une base de donnée en utilisant
// un compilateur et la librairie mysql 64bits
// la base de donnee est "cdi"
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

//--------------Bouton connexion-------------------
void MainWindow::on_pushButton_clicked()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    qDebug()<<db.driver();

        db.setHostName("localhost");        //adresse ip si besoin
        db.setUserName("root");
        db.setPassword("");
        db.setDatabaseName("cdi");
        if (db.open())
                    QMessageBox::information(this,"connexion", "connexion au serveur réussi");
              else
                    QMessageBox::information(this,"Problème","connexion au serveur a echoué");


}
//---------------Bouton lecture-------------------------------
void MainWindow::on_pushButton_2_clicked()
{
    QSqlQuery query;
    //execution de la requete SELECT

    if(query.exec("SELECT * FROM livre"))
    {
        while(query.next())
        {
            qDebug()<< "    Nouvelle entrée" ;
            for(int x=0; x < query.record().count(); ++x)
            {
                qDebug()<< "        " <<query.record().fieldName(x) << " = " << query.value(x).toString();
            }
        }
    }
    else
        qDebug()<<"erreur";
}
//-------------Bouton ecriture--------------------------
void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery query;
           if(query.prepare("INSERT INTO personne (nopers, nom, prenom, classe) " "VALUES (?,?,?,?)"))  //preparation de la requete
           {
               query.addBindValue(QVariant());       //id auto increment => valeur=NULL en sql
               query.addBindValue("Mister");        //champs nom de la table
               query.addBindValue("toto");     //champs prenom de la table
               query.addBindValue("2tsciel");     //champs prenom de la tabl
               query.exec();                         //execution de la requete apres remplissage des champs
           }
           else
           {
               qDebug()<<"erreur insert";
           }
}
//---------------------------------------------------------------------------
