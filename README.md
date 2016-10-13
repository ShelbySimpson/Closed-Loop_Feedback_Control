#Closed-Loop_Feedback_Control

The program uses a circuit board, light sensor, servo, sliding potentiometer,
and a push button. With the use of this equipment the circuit board will "chase" a light source.
A light threshold value helps determine what light source is followed by the circuit board.

The light threshold determines when a 180 scan is needed. If the light sample drops below threshold 
a scan is triggered. The button(D12) will allow you to change light threshold value to the current 
slider(A3) value. The light threshold can not be changed while circuit board is scanning or when waiting 
to see if the light source has returned, so the button is intended to be used when the light threshold 
has been set too low as the circuit board will not be rotating. A light threshold set too high will have the 
circuit board rotating/waiting quite a bit thus making it difficult to get a slider value. When the light 
threshold is too low for current room light the circuit board will function as normal but will never scan 
aside from the initial start up scan.
