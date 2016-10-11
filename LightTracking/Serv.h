#ifndef Serv_h
#define Serv_h
#include "Arduino.h"
#include <Servo.h>

using namespace std;

class Serv {
  public:
    Serv();
    void rotate(short pos);
    void initAttach();
    short getPos();
    
  private: 
    short _pos;  
    Servo myServo; 
};

#endif
