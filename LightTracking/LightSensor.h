#ifndef LightSensor_h
#define LightSensor_h
#include "Arduino.h"

class LightSensor{
  private:
  int  _pin; //light sensor pin for digital sandbox
  short _prevData;//light sensor's current value

  public:
    LightSensor();//Constructor, sets _pin var
    short getData();//retrieve data from light sensor
    void setPrevData(short currData);
    short getPrevData();
  
};


#endif
