//#include "Thermometer.h"
//#include "LED.h"
#include "LightSensor.h"
//#include "Microphone.h"
//#include "Slide.h"
#include "Switch.h"
//#include "Button.h"
#include "ColorLED.h"
#include "Serv.h"
short rotateL = 0;
short GREEN = 10;
int posServo = 0;
bool settingUp;
short degreeInterval;
short lightHigh = 0;//highest light reading
short lightCurr;//current light reading
short lightDegree;//Degree at where highest current light reading is recorded

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

void setup() {
  Serial.begin(57600);
  settingUp = true;
  degreeInterval = 5;//light data sample based on degreeInterval
}

void loop() {
  cLED.on(50);
  //Setup 
  //1.)find the degree to which light has the most intensity.
    //for each degree(all 180) find highest light sensor reading,sandbox scans inviroment.
    while(settingUp){
    servo.rotate(0);
    for(short i = 0; i < 180; i = i + degreeInterval){
      servo.rotate(i);//rotate at degree intervals to test light intensity.
      delay(50);//allow time for servo movement
      lightCurr = lightSensor.getData();//get light data at current degree.
      if(lightCurr > lightHigh){//keep track of highest light degree reading
        lightHigh = lightCurr;
        lightDegree = i;
        Serial.print("Light High - ");
        Serial.println(lightHigh);
        Serial.print("Light Degree - ");
        Serial.println(lightDegree);
      }
      servo.rotate(lightDegree);//move to area with most light
    }
    settingUp = false;
    Serial.println("Finished Setting Up");
    }
}
