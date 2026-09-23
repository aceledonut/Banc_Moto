#include "acquisition.h"

Acquisition::Acquisition()
{
    // Valeurs par défaut
    sMecaniques_data.regime = 0;
    sMecaniques_data.vitesse = 0;
    sMecaniques_data.puissance = 0;
    sMecaniques_data.couple = 0;

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

    // Conversion de la mesure
    sMecaniques_data.regime = valeur * 3600;

    sMecaniques_data.vitesse = valeur * 60;

    sMecaniques_data.couple = sMecaniques_data.vitesse * 2 ;

    sMecaniques_data.puissance = (sMecaniques_data.couple * sMecaniques_data.vitesse) / 9550 ;
}


donnees_mecaniques Acquisition::get_sMecaniques_data()
{
    return sMecaniques_data;
}


Acquisition::~Acquisition()
{
}
