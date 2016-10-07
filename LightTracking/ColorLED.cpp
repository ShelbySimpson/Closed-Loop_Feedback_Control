#include "ColorLED.h"

ColorLED::ColorLED(int pin){
  if(pin < 9 || pin > 11){
    Serial.println("Color LEDs are pins 9-11, invalid pin entered");
  }
  else{
    _pin = pin;//set pin to user intput
}
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void ColorLED::on(int brightness){
  if(brightness < 0)
    brightness = 0;
  else if (brightness > 255)
    brightness = 255;
  analogWrite(_pin, brightness);
}

void ColorLED::off(){
  analogWrite(_pin,LOW);
}

void ColorLED::setColor(int color)
{
  if(color < 9 || color > 11) {
    Serial.println("Can only set the Color LED to pins 9, 10, and 11"); 
  }
  
  switch (color){
    case 9:
      _pin = 9;
      break;
    case 10:
      _pin = 10;
      break;
    case 11:
      _pin = 11;
      break;
  }
}

