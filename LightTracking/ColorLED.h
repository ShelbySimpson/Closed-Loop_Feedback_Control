#ifndef ColorLED_h
#define ColorLED_h
#include "Arduino.h"

using namespace std;

class ColorLED{
  private:
    int _pin;//current colored led pin
    
  public:
    ColorLED(int _pin);//constructor, set pen
    void on(int brightness);//turn on 
    void off();//turn off
    void setColor(int color);
};


#endif
