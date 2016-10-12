//#include "Thermometer.h"
//#include "LED.h"
#include "LightSensor.h"
//#include "Microphone.h"
#include "Slide.h"
#include "Switch.h"
#include "Button.h"
#include "ColorLED.h"
#include "Serv.h"
#include <Servo.h>
short rotateL = 0;
short GREEN = 10;
short RED = 9;
int posServo = 0;
bool settingUp;
short degreeInterval;
short lightPrev;//previous light reading
short lightCurr;//current light reading
short nextMove = 0;
short dir = 1;
short posCurr = 180;//current position of servo(0-180)
short lightThreshold = 100;//the point at which the area will be scanned for light source.
//--------
//Initate instances 
//Thermometer therm = Thermometer();
//LED leds[6] = {LED(4), LED(5), LED(6), LED(7), LED(8), LED(13)};
LightSensor lightSensor = LightSensor();
//Microphone mic = Microphone();
Slide slide = Slide();
Switch swch = Switch();
Button bttn = Button();
ColorLED cLED = ColorLED(RED);
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
  servo.initAttach();
  cLED.setColor(RED);
  cLED.on(255);
  servo.rotate(0);
  servo.rotate(servo.scanHighPos(lightSensor,degreeInterval));
  lightThreshold = map(slide.getData(),0,1023,0,200);
  Serial.print("Light Threshold - ");
  Serial.println(lightThreshold);
  cLED.off();
  cLED.setColor(GREEN);//green mean its a go
  cLED.on(255);//on and ready for flashlight movement.
  delay(50);
  
  
}

void loop() {
      //------------------------------------  READ ME ---------------------------------------------------------------------------
      //the lightThreshold determines the highest level of light to trigger a 180
      //scan. The button(D12) will allow you to change lightThreshold to the slider(A3) value.
      //lightThreshold can not be changed while sandbox is scanning so the button is intended
      //to be used when the lightThreshold has been set too low as the sandbox will not be rotating. A 
      //lightThreshold set too high will have the sandbox rotating most of the time thus making
      //it difficult to get slider value. While at a lightThreshold set very low the sandbox will
      //not rotate but will still function as intended but will never scan to look for a strong light
      //source such as a flashlight.
      //----------------------------------------------------------------------------------------------------------------------------

      lightCurr = lightSensor.getData();
      if(bttn.getData() == 1){
        lightThreshold = slide.getData();
      }
      Serial.println(lightCurr);
      if(lightCurr < lightThreshold){
        //delay and try again to check if light source is back
        delay(1000);
        lightCurr = lightSensor.getData();
          if(lightCurr < lightThreshold){
            cLED.off();
            cLED.setColor(RED);
            cLED.on(255);
            servo.rotate(servo.scanHighPos(lightSensor,degreeInterval));
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
