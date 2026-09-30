#include "acquisition.h"
#include <qDebug>

#define description L"USB-4704,BID#0"

Acquisition_USB_4704::Acquisition_USB_4704() {

    //Initialisation des valeurs de la structure
    donnees.regime=0;
    donnees.vitesse=0;
    donnees.couple=0;
    donnees.puissance=0;


    instantAiCtrl = InstantAiCtrl::Create();
    DeviceInformation selected(description);
    instantAiCtrl->setSelectedDevice(selected);
}

DonneesMecaniques Acquisition_USB_4704::get_sMecanique_data() {
    return donnees;
}

void Acquisition_USB_4704::acquerir_donnees_mecaniques() {

    //Lecture de l'input
    instantAiCtrl->Read(0, valeurAI0);
    donnees.vitesse = 60 * valeurAI0;

    instantAiCtrl->Read(1,valeurAI1);
    donnees.regime  = 3600 * valeurAI1;

    instantAiCtrl->Read(2,valeurAI2);
    donnees.couple = 60 * valeurAI2;

    donnees.puissance = donnees.couple * (2 * M_PI * donnees.regime / 60.0) / 1000.0 ;

}

Acquisition_USB_4704::~Acquisition_USB_4704() {
}
