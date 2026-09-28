#include "acquisition_usb_4704.h"
#include <qDebug>

#define description L"USB-4704,BID#0"

Acquisition_USB_4704::Acquisition_USB_4704() {
    qDebug()<<"Création de la classe Acquisition";

    //Initialisation des valeurs de la structure
    donnees.regime=0;
    donnees.vitesse=0;
    donnees.puissance=0;
    donnees.couple=0;

    //voir si les valeur sont bien initialiser
    qDebug()<<"Regime inisialiser a = "<< donnees.regime;
    qDebug()<<"Vitesse inisialiser a = "<< donnees.vitesse;
    qDebug()<<"Puissance inisialiser a = "<< donnees.puissance;
    qDebug()<<"Couple inisialiser a = "<< donnees.couple;

    //creation de la carte
    instantAiCtrl = InstantAiCtrl::Create();
    DeviceInformation selected(description);
    instantAiCtrl->setSelectedDevice(selected);
}

DonneesMecaniques Acquisition_USB_4704::get_sMecanique_data() {
    qDebug()<<"Retour des informations de la structure";
    return donnees;
}

void Acquisition_USB_4704::acquerir_donnees_mecaniques() {

    //Lecture de l'input
    instantAiCtrl->Read(0, valeurAI0);

    //calcule pour les valeur selon la donnees souhaité
    donnees.vitesse = 60 * valeurAI0;
    donnees.regime = 3600 * valeurAI0;
    donnees.puissance = 60 * valeurAI0;
    donnees.couple = 2 * valeurAI0;

    qDebug()<<"Vitesse stockée dans la structure :" << donnees.vitesse;
    qDebug()<<"Régime stocké dans la structure :" << donnees.regime;
}
Acquisition_USB_4704::~Acquisition_USB_4704() {
    qDebug()<<"Destruction de la classe Acquisition";
}
