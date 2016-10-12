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
short RED = 9;
int posServo = 0;
bool settingUp;
short degreeInterval;
short lightPrev = 0;//previous light reading
short lightCurr;//current light reading
short nextMove = 0;
short dir = 1;
short posCurr = 180;//current position of servo(0-180)
//--------
//Initate instances 
//Thermometer therm = Thermometer();
//LED leds[6] = {LED(4), LED(5), LED(6), LED(7), LED(8), LED(13)};
LightSensor lightSensor = LightSensor();
//Microphone mic = Microphone();
//Slide slide = Slide();
Switch swch = Switch();
//Button bttn = Button();
ColorLED cLED = ColorLED(RED);
Serv servo = Serv();

bool isMove(short curr, short prev){
  bool move = true;
  if(curr <= (prev + 20) && curr >= (prev - 20)){
    move = false;
  }
  return move;
}

short scan(){
    cLED.off();
    cLED.setColor(RED);//green mean its a go
    cLED.on(255);//on and ready for flashlight movement.
    servo.rotate(0);//set to intial testing position
    short newPos = 0;
    for(short i = 0; i < 181; i = i + degreeInterval){
      servo.rotate(i);//rotate at degree intervals to test light intensity.
      delay(50);//allow time for servo movement
      lightCurr = lightSensor.getData();//get light data at current degree.
      if(lightCurr > lightPrev){//keep track of highest light degree reading
        lightPrev = lightCurr;//current becomes previous as another data sample will be taken
        newPos = i;
      }
    }
    return newPos;
}

void setup() {
  Serial.begin(57600);
  Serial.println("Start");
  settingUp = true;
  degreeInterval = 5;//light data sample based on degreeInterval
  servo.initAttach();
  
}

void loop() {
  //Setup 
  //1.)find the degree to which light has the most intensity.
    //for each degree interval(0-180) find highest light sensor reading,sandbox scans inviroment.
    //this will have sandbox in a close enough proximity as long the intervals are reasonable.
    if(swch.getData() == 1){
    while(settingUp){
    cLED.on(255);//turn red light on until finished setting up
    servo.rotate(0);//set to intial testing position
    for(short i = 0; i < 181; i = i + degreeInterval){
      servo.rotate(i);//rotate at degree intervals to test light intensity.
      delay(50);//allow time for servo movement
      lightCurr = lightSensor.getData();//get light data at current degree.
      if(lightCurr > lightPrev){//keep track of highest light degree reading
        lightPrev = lightCurr;//current becomes previous as another data sample will be taken
        posCurr = i;
      }
    }
    servo.rotate(posCurr);//move to area with most light
    //servo.rotate(90);//temp testing
    delay(50);
    settingUp = false;
    //cLED.off();
    //cLED.setColor(GREEN);//green mean its a go
    //cLED.on(255);//on and ready for flashlight movement.
    Serial.println("Finished Setting Up");
    }
      //Begin looking for light changes--------------------------------------------------------------------------------------
      //if light's reading is < 100 scan enviroment
            lightCurr = lightSensor.getData();
      Serial.println(lightCurr);
      if(lightCurr < 100){
        delay(1000);
        lightCurr = lightSensor.getData();
          if(lightCurr < 100){
            servo.rotate(scan()); 
            delay(50);
                cLED.off();
                cLED.setColor(GREEN);//green mean its a go
                cLED.on(255);//on and ready for flashlight movement.
          }
      }
      //Determine if there has been a significant change in the light source to make a move
      if(isMove(lightCurr,lightPrev)){
        lightPrev = lightCurr;//update value before new data sample
        posCurr = abs(servo.getPos() * dir + degreeInterval);
        servo.rotate(posCurr);
        delay(50);
        //get light source and compare to prev
        if(lightSensor.getData() < lightPrev){
          //light source decrease indication is that light is in 
          //other direction,switch and move
          dir *= -1;//switch direction
          servo.rotate(degreeInterval *2 * dir + servo.getPos());
          delay(50);
        }
      }
    }
}
