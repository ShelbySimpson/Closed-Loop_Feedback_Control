#include "Serv.h"

Serv::Serv(){
  //myServo.attach(3);
  _pos = 0;
}

void Serv::rotate(short pos)
{
  myServo.write(pos);
  _pos = pos;
}

void Serv::initAttach(){
  myServo.attach(3);
}

short Serv::getPos(){
  return _pos;
}



