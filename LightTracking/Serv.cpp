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

short Serv::scanHighPos(LightSensor lightSensor,short degreeInterval){
    myServo.write(0);//set to intial testing position
    delay(50);
    short newPos = 0;
    short lightCurr = 0;
    short lightPrev = 0;
    for(short i = 0; i < 181; i = i + degreeInterval){
      myServo.write(i);//rotate by degreeInterval through entire sweep.
      delay(50);//allow time for servo movement
      lightCurr = lightSensor.getData();//get light data at current degree.
      if(lightCurr > lightPrev){//keep track of highest light degree reading
        lightPrev = lightCurr;//current becomes previous as another data sample will be taken
        newPos = i;//last value stored will be position with the highest light value
      }
    }
    return newPos;
}



