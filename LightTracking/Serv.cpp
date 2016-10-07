#include "Serv.h"

Serv::Serv(){
  myServo.attach(3);
  _pos = 0;
}

void Serv::rotate(short pos)
{
  if (_pos += pos > 180)
  {
    _pos = 180;
  }
  else if(_pos += pos < 0)
  {
    _pos = 0;
  }
  else
  {
    _pos += pos;
  }
  myServo.write(pos);
}

void Serv::rotateLeft(){
  myServo.write(0);
}

void Serv::rotateRight(){
  myServo.write(180);
}



