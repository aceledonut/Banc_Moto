#ifndef ACQUISITION
#define ACQUISITION

#ifndef __int64
#define __int64 long long
#endif

#include "bdaqctrl.h"
using namespace Automation::BDaq;

#include "Structure.h"

class Acquisition_USB_4704
{
public:
    Acquisition_USB_4704();
    ~Acquisition_USB_4704();

    void acquerir_donnees_mecaniques();
    DonneesMecaniques get_sMecanique_data();

private:
    DonneesMecaniques donnees;
    InstantAiCtrl* instantAiCtrl;
    double valeurAI0;
    double valeurAI1;
    double valeurAI2;


};

#endif // ACQUISITION_USB_47_4_H
