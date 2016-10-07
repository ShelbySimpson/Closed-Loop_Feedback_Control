#include "Thermometer.h"


Thermometer::Thermometer(){
  _pin = A0;
}

float Thermometer::getData(){
  return analogRead(_pin);//get reading from A0 sensor
}

float Thermometer::getCelsius(){
  float voltage = getData() * (5 / 1023.00);
  _celsius = (voltage - 0.5) * 100; //convert from voltage value to degrees celsius
  return _celsius;
}

float Thermometer::getFahrenheit(){
 _celsius = getCelsius(); //get temp in celsius for purpose of converting to fahrenheit
 _fahrenheit = ((_celsius * 9) / 5) + 32; //celsius to fahrenheit formula
  return _fahrenheit;
}

