#ifndef ACQUISITION_H
#define ACQUISITION_H

#include <QString>
#include <QTimer>

#include "bdaqctrl.h"

using namespace Automation::BDaq;

struct donnees_mecaniques
{
    int regime;
    int vitesse;
    float puissance;
    float couple;
};

class Acquisition
{
public:
    Acquisition();
    ~Acquisition();

    void acquerir_donnees_mecanique();

    donnees_mecaniques get_sMecaniques_data();

private:
    donnees_mecaniques sMecaniques_data;

    InstantAiCtrl *instantAiCtrl;
};

#endif // ACQUISITION_H
