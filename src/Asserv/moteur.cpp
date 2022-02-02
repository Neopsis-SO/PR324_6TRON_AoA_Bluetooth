#include "mbed.h"
#include "moteur.h"


// Constructeur
Moteur::Moteur(PinName  forwardPinInput, PinName  backwardPinInput) :forwardPin(forwardPinInput),backwardPin(backwardPinInput)
{
  forwardPin=forwardPinInput;
  backwardPin=backwardPinInput;
}

void Moteur::Speed(float vitesse)
{
  if(vitesse>=0){
    forwardPin.write(abs(vitesse));
    backwardPin.write(0);
  }else{
    backwardPin.write(abs(vitesse));
    forwardPin.write(0);
  }
}

