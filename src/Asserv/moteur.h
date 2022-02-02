#ifndef _MOTEUR_H
#define _MOTEUR_H
#include "mbed.h"

#define VMOY 20
#define VMAX 50
//PWM3_OUT backward j4
//ICAPT1 forward j4
//PWM2_OUT forward j3
//PWM1_OUT backward j3
class Moteur
{
    public:
        Moteur(PinName  forwardPinInput, PinName  backwardPinInput);
        void Speed(float vitesse);
    private:
        PwmOut forwardPin;
        PwmOut backwardPin;
};

#endif


