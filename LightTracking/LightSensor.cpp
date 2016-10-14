#include "LightSensor.h"

LightSensor::LightSensor(){
  _pin = A1;//set pin
}

 short LightSensor::getData(){
  return analogRead(_pin);//read in data
}

