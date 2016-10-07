#ifndef Switch_h
#define Switch_h
#include "Arduino.h"

using namespace std;

class Switch{
  
  private:
    int _pin;//switch pin for digital sandbox
    
  public:
    Switch();//constructor sets _pin variable
    int getData();//retrieve switch data
};


#endif
