#include "Serv.h"

Serv::Serv(){
  //myServo.attach(3);
  _pos = 0;
}

void Serv::rotate(short pos)
{
  myServo.write(pos);

//  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myServo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    myServo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }

}

void Serv::rotateLeft(){
  //myServo.write(0);
  myServo.attach(3);
}

void Serv::rotateRight(){
  myServo.write(180);
}



