#ifndef Microphone_h
#define Microphone_h
#include "Arduino.h"

class Microphone{
  private:
    int _pin;//Mic pin for digital sandbox
  public:
    Microphone();//Constructor sets _pin var
    int getData();//retrieve data from mic sensor
};


#endif
