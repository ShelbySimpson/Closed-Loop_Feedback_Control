#include "LED.h"
#include "Arduino.h"

LED::LED(short pin){
  if((pin < 4 || pin > 8) && pin != 13){
    Serial.println("LEDs are pins 4-8 and 13");
    Serial.print("Cannot set LED to pin ");
    Serial.println(pin);
  }
  else{
  _pin = pin;
}
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}

void LED::on(){
  digitalWrite(_pin, HIGH);//turn on
}

void LED::off(){
  digitalWrite(_pin,LOW);//turn off
}

void LED::changePin(int pin)
{
  if((pin < 4 || pin > 8) && pin != 13){
    Serial.println("LEDs are pins 4-8 and 13");
    Serial.print("Cannot set LED to pin ");
    Serial.println(pin);
  }
  else{
    _pin = pin;
  }
}

