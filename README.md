#Closed-Loop_Feedback_Control

The program works with Arduino's Digital Sandbox, using the light sensor, servo, sliding potentiometer,
and a push button. Program can easily be ported to another embedded system. With the use of this equipment the Digital Sandbox will "chase" a light source.

A light threshold value helps determine what light source is followed by the Digital Sandbox.
The light threshold determines when a 180 scan is needed. If the light sample drops below threshold 
a scan is triggered. The button(D12) will allow you to change light threshold value to the current 
slider(A3) value. The light threshold can not be changed while Digital Sandbox is scanning or when waiting 
to see if the light source has returned, so the button is intended to be used when the light threshold 
has been set too low as the Digital Sandbox will not be rotating. A light threshold set too high will have the 
Digital Sandboard rotating/waiting quite a bit thus making it difficult to get a slider value. When the light 
threshold is too low for the current room light the Digital Sandbox will function as normal but will never scan.
