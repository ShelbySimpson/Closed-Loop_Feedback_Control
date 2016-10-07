#include "Slide.h"

Slide::Slide(){
  _pin = A3;//set pin
}

int Slide::getData(){
  return analogRead(_pin);//retrieve pin data
}

