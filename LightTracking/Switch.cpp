#include "Switch.h"

Switch::Switch(){
  _pin = 2;
}

int Switch::getData(){
  return digitalRead(_pin);
}

