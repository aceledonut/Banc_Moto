#include "acquisition.h"
#include "qdebug.h"

Acquisition::Acquisition()
{
    qDebug() << "CREATION ACQUISITION";

    // Valeurs par défaut
    sMecaniques_data.regime = 0;
    sMecaniques_data.vitesse = 0;
    sMecaniques_data.puissance = 0;
    sMecaniques_data.couple = 0;

    // Test de la structure
    qDebug() << "Regime    :" << sMecaniques_data.regime;
    qDebug() << "Vitesse   :" << sMecaniques_data.vitesse;
    qDebug() << "Couple    :" << sMecaniques_data.couple;
    qDebug() << "Puissance :" << sMecaniques_data.puissance;

    // Création de la carte
    instantAiCtrl = InstantAiCtrl::Create();

    // Sélection de la USB-4704
    QString desc = "USB-4704,BID#0";

    std::wstring description = desc.toStdWString();

    DeviceInformation device(description.c_str());

    instantAiCtrl->setSelectedDevice(device);
}


void Acquisition::acquerir_donnees_mecanique()
{
    double valeur = 0;

    // Lecture de AI0
    instantAiCtrl->Read(0, 1, &valeur);
    qDebug() << "ACQUISITION VALEUR";
    qDebug() << "Valeur AI0 :" << valeur;

    // Conversion de la mesure
    sMecaniques_data.regime = valeur * 3600;
    sMecaniques_data.vitesse = valeur * 60;

    // Calcul vitesse et regime
    sMecaniques_data.vitesse = 60 * valeur;
    sMecaniques_data.regime = 3600 * valeur;

    sMecaniques_data.couple = sMecaniques_data.vitesse * 2 ;
    sMecaniques_data.puissance = (sMecaniques_data.couple * sMecaniques_data.vitesse) / 9550 ;

    // Calcul vitesse et regime
    qDebug() << "Couple :" << sMecaniques_data.couple;
    qDebug() << "Puissance :" << sMecaniques_data.puissance;


}


donnees_mecaniques Acquisition::get_sMecaniques_data()
{
    qDebug() << "RECUPERATION STRUCTURE";

    qDebug() << "Regime    :" << sMecaniques_data.regime;
    qDebug() << "Vitesse   :" << sMecaniques_data.vitesse;
    qDebug() << "Couple    :" << sMecaniques_data.couple;
    qDebug() << "Puissance :" << sMecaniques_data.puissance;
    return sMecaniques_data;
}


Acquisition::~Acquisition()
{
 qDebug() << "DESTRUCTION ACQUISITION";
}
