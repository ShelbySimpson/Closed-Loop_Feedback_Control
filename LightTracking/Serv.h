#ifndef Serv_h
#define Serv_h
#include "Arduino.h"
#include "LightSensor.h"
#include <Servo.h>

using namespace std;

class Serv {
  public:
    Serv();//constuctor sets _pos to 0
    
    void rotate(short pos);//rotate servo
    
    void initAttach();// call class attach funtion
    
    short getPos();//get position of servo
    
    //Scans 180 and returns the position that had the highest light value
    short scanHighPos(LightSensor lightSensor,short degreeInterval);
    
    //ensure that servo doesn't grind by going to position beyond stop
    short checkAdjustLimits(short posCurr);
    
  private: 
    short _pos;//servo position
    Servo myServo; //servo instance
};

#endif
