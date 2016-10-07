#ifndef Slide_h
#define Slide_h
#include "Arduino.h"

using namespace std;

class Slide{

  private:
    int _pin;//slider pin for digital sandbox

  public:
    Slide();//Constructor sets _pin
    int getData();//retrieve data from slider
};


#endif
