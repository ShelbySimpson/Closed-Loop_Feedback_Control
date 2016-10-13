#include "LightSensor.h"
#include "Slide.h"
#include "Switch.h"
#include "Button.h"
#include "ColorLED.h"
#include "Serv.h"
#include <Servo.h>

const short GREEN = 10;//apply to ColorLED
const short RED = 9;//apply to ColorLED
short degreeInterval;
short lightPrev;//previous light reading
short lightCurr;//current light reading
short dir = 1;//used to switch servo rotating direction
short posCurr;//current position of servo(0-180)
short lightThreshold;//the point at which the area will be scanned for light source.
short pad = 20;//padding for light samples.
short moveDelay = 50;//delay given after servo has been instructed to move
//time sandbox waits when light value goes below lightThreshold
//before checking again to see if light source has returned - 
short waitDelay = 2000;
//--------
//Initate instances 
LightSensor lightSensor = LightSensor();//used to track light
Slide slide = Slide();//used to determine lightThreshold
Button bttn = Button();//used to change lightThreshold
ColorLED cLED = ColorLED(RED);//red signifes scanning, green signifies tracking
Serv servo = Serv();//cordinates with light sensor

//Function determines rather a change in the light source value is significant enough to "chase" light source.
//lightCurr - current light sample
//lightPrev - previous light sample
//pad - a value that determines, in neg and pos direction, how much of a light value change
//is allowed before system will take another light sensor sample.
bool isMove(short lightCurr, short lightPrev, short pad){
  bool move = true;
  if(lightCurr <= (lightPrev + pad) && lightCurr >= (lightPrev - pad)){
    move = false;
  }
  return move;
}

void setup() {
  Serial.begin(57600);
  Serial.println("Start");
  degreeInterval = 5;//light data to be sampled based on degreeInterval
  servo.initAttach();//initiate servo
  cLED.setColor(RED);//set to red until inital scan finishes
  cLED.on(255);
  servo.rotate(0);//move
  delay(moveDelay);//allow time for servo to move
  servo.rotate(servo.scanHighPos(lightSensor,degreeInterval));//move to highest light source
  lightThreshold = slide.getData();//set lightThreshold
  Serial.print("Light Threshold - ");
  Serial.println(lightThreshold);
  cLED.off();//turn of RED light
  cLED.setColor(GREEN);//green mean its a go
  cLED.on(255);//on and ready for flashlight movement
  Serial.println("Finished Setting Up");
   
}

      //------------------------------------  READ ME ---------------------------------------------------------------------------
      //the lightThreshold determines the highest level of light to trigger a 180
      //scan. The button(D12) will allow you to change lightThreshold to the slider(A3) value.
      //lightThreshold can not be changed while sandbox is scanning or when waiting to see if light soruce has returned, 
      //so the button is intended to be used when the lightThreshold has been set too low as the sandbox will not be rotating. A 
      //lightThreshold set too high will have the sandbox rotating most of the time thus making
      //it difficult to get slider value. While at a lightThreshold set very low the sandbox will
      //not rotate but will still function as intended but will never scan to look for a strong light
      //source such as a flashlight.
      //----------------------------------------------------------------------------------------------------------------------------

void loop() {
      lightCurr = lightSensor.getData();//sample light data
      Serial.print("dir: ");
      Serial.println(dir);
      Serial.print("posCurr: ");
      Serial.println(posCurr);
      Serial.print("Light Level: ");
      Serial.println(lightCurr);
      //determine if a new lightThreshold sample is to taken
      if(bttn.getData() == 1){
        //button was pressed sample light data
        lightThreshold = slide.getData();
      }
      //check to see if light has gone below LightThreshold
      if(lightCurr < lightThreshold){
        //light has gone below thresHold delay and try again 
        //to check if light source is back
        delay(waitDelay);
        lightCurr = lightSensor.getData();//new sample
          if(lightCurr < lightThreshold){
            //light source is still gone, turn on red light and scan
            //enviroment
            cLED.off();
           cLED.setColor(RED);
            cLED.on(255);
            posCurr = servo.scanHighPos(lightSensor,degreeInterval);
            servo.rotate(servo.checkAdjustLimits(posCurr));
            
            delay(moveDelay);
                cLED.off();
                cLED.setColor(GREEN);//green mean its a go
                cLED.on(255);//on and ready for light changes.
          }
      }
      //Determine if there has been a significant change in the light source to make a move
      if(isMove(lightCurr,lightPrev,pad)){
        lightPrev = lightCurr;//update value before new data sample
        //get new position according to degreeInterval and rotate
        posCurr = servo.checkAdjustLimits(degreeInterval *2 * dir + servo.getPos());//get position
        servo.rotate(posCurr);//check for upper limit,adjust if needed,move
        Serial.print("upper limit - ");
        Serial.println(posCurr);
        delay(moveDelay);//allow time for servo movement
        //get light source and compare to prev
        if(lightSensor.getData() < lightPrev){
          //light source has decreased indicating that light source is
          //most likely in the other direction,switch and move
          dir *= -1;//switch direction
          posCurr = servo.checkAdjustLimits(degreeInterval *2 * dir + servo.getPos());//get position
          servo.rotate(posCurr);//check for upper limit,adjust if needed,move
          Serial.print("upper limit - ");
          Serial.println(posCurr);
          delay(moveDelay);//allow time for servo movement
        }
      }
}
