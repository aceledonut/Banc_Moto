#ifndef ACQUISITION_USB_47_4_H
#define ACQUISITION_USB_47_4_H

#ifndef __int64
#define __int64 long long
#endif

#include "bdaqctrl.h"
using namespace Automation::BDaq;

#include "structure.h"

class Acquisition_USB_4704
{
public:
    Acquisition_USB_4704();
    ~Acquisition_USB_4704();

    //Méthodes pour récupérer et afficher les données
    void acquerir_donnees_mecaniques();
    DonneesMecaniques get_sMecanique_data();


private:
    //Initialisation de la structure sous le nom donnees
    DonneesMecaniques donnees;
    InstantAiCtrl* instantAiCtrl;
    double valeurAI0;


};


#endif // ACQUISITION_USB_47_4_H
