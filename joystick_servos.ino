// Joystick x- and y- axes are connected to A1 and A0 analog pins of Arduino.
// Servos are connectd to PWM Pins 9 and 10.


#include <Servo.h>

Servo tilt, pan; 

int joyX = A1; //  X - axis of Joystick
int joyY = A0; // y - axis of Joystick
int x, y; 

void setup()
{ 
  tilt.attach(10); // TILT on PIN 10
  pan.attach(9); // PAN on PIN 9
} 

void loop()
{ 
  x = joyX;    // y value btwn 0 and 1023) 
  y = joyY;    // x value btwn 0 and 1023) 
  x = map(analogRead(joyX), 0, 1023, 900, 2100); 
  y = map(analogRead(joyY), 0, 1023, 900, 2100);
  tilt.write(x); 
  pan.write(y);
  delay(15); 
}
