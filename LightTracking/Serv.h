#ifndef Serv_h
#define Serv_h
#include "Arduino.h"
#include <Servo.h>

using namespace std;

class Serv {
  public:
    Serv();
    void init(Servo myServo);
    void rotate(short pos);
    void rotateLeft();
    void rotateRight();
    
  private: 
    short _pos;  
    Servo myServo; 
};

#endif
