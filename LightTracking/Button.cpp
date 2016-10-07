#include "Button.h"

Button::Button(){
  _pin = 12;//set pin
}

//retrieve data from button
int Button::getData(){
  return digitalRead(_pin);
}

