//#include "Thermometer.h"
//#include "LED.h"
#include "LightSensor.h"
//#include "Microphone.h"
//#include "Slide.h"
#include "Switch.h"
//#include "Button.h"
#include "ColorLED.h"
#include "Serv.h"
#include <Servo.h>
short rotateL = 0;
short GREEN = 10;
int posServo = 0;
bool settingUp;
short degreeInterval;
short lightPrev = 0;//previous light reading
short lightCurr;//current light reading
short lightDegree;//Degree at where highest current light reading is recorded
short nextMove = 0;
short dir = -1;
short posCurr 0;
//--------
//Initate instances 
//Thermometer therm = Thermometer();
//LED leds[6] = {LED(4), LED(5), LED(6), LED(7), LED(8), LED(13)};
LightSensor lightSensor = LightSensor();
//Microphone mic = Microphone();
//Slide slide = Slide();
Switch swch = Switch();
//Button bttn = Button();
ColorLED cLED = ColorLED(GREEN);
Serv servo = Serv();

bool isMove(short curr, short prev){
  bool move = true;
  if(curr <= (prev + 20) && curr >= (prev - 20)){
    move = false;
  }
  return move;
}

void setup() {
  Serial.begin(57600);
  Serial.println("Start");
  settingUp = true;
  degreeInterval = 5;//light data sample based on degreeInterval
  servo.rotateLeft();
  
}

void loop() {
//  Test code - 
//  if(nextMove ==0){
//  servo.rotate(180);
//  nextMove = 5;
//  delay(1000);
//  }else{
//    servo.rotate(0);
//    delay(1000);
//    nextMove = 0;
//  }


  cLED.on(255);
  //Setup 
  //1.)find the degree to which light has the most intensity.
    //for each degree interval(0-180) find highest light sensor reading,sandbox scans inviroment.
    //this will have sandbox in a close enough proximity as long the intervals are reasonable.
    if(swch.getData() == 1){
    while(settingUp){
    servo.rotate(0);
    for(short i = 0; i < 181; i = i + degreeInterval){
      servo.rotate(i);//rotate at degree intervals to test light intensity.
      delay(150);//allow time for servo movement
      lightCurr = lightSensor.getData();//get light data at current degree.
      if(lightCurr > lightPrev){//keep track of highest light degree reading
        lightPrev = lightCurr;//current becomes previous as another data sample will be taken
        lightDegree = i;
//        Serial.print("Light High - ");
//        Serial.println(lightHigh);
//        Serial.print("Light Degree - ");
//        Serial.println(lightDegree);
      }
      servo.rotate(lightDegree);//move to area with most light
    }
    settingUp = false;
    Serial.println("Finished Setting Up");
    Serial.println(lightPrev);
    }
      //Begin looking for light changes
      lightCurr = lightSensor.getData();
      delay(100);
      //Determine if there has been a significant change in the light source to make a move
      if(isMove(lightCurr,lightPrev)){
        servo.rotate(0)//temp just for testing
        
        while(){
        lightPrev = lightCurr;//exchange values before new data sample
        posCurr = abs(lightDegree * dir + degreeInterval);
        servo.rotate(currPos);//rotate by interval
          Serial.println("atest");
           Serial.println(abs(lightDegree * dir + degreeInterval));
           Serial.println(lightDegree);
           dir *= -1;
           Serial.print("dir------>");
           Serial.println(dir);
        }
        //check if new position has a greater light source
        if(lightSensor.getData() > lightPrev){
          //
        }
        Serial.println("This is a move");
        nextMove++;
        Serial.println(nextMove);
        Serial.println(lightCurr);
      }
    }
//
//    if(lightSensor.getData()<= lightHigh - 10 || lightSensor.getData() >= lightHigh + 10){
//      if(nextMove == 0){
//          nextMove = nextMove + degreeInterval;
//      }else if(nextMove == 180){
//        nextMove == nextMove - degreeInterval;
//        servo.rotate(nextMove);
//    }
//    }
}
