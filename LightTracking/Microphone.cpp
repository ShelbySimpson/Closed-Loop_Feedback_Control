#include "Microphone.h"

Microphone::Microphone(){
  _pin = A2;//set pin
}

int Microphone::getData(){
  return analogRead(_pin);//retrieve data from mic
}

