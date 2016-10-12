#ifndef Serv_h
#define Serv_h
#include "Arduino.h"
#include "LightSensor.h"
#include <Servo.h>

using namespace std;

class Serv {
  public:
    Serv();
    void rotate(short pos);
    void initAttach();// call class attach funtion
    short getPos();//get position of servo
    //Scans 180 and returns the position that had the highest light value -
    short scanHighPos(LightSensor lightSensor,short degreeInterval);
    
  private: 
    short _pos;//servo position
    Servo myServo; //servo instance
};

#endif
