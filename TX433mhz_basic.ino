/*--------------------------------------------------------------
  Program:      TX433mhz_basic

  Description:  Sends simple message from Arduino using RF
                433MHz transmitter.
  
  Hardware:     Arduino Uno and RF 433MHz transmitter. Needs a
                corresponding RF 433MHz receiver and Arduino at
                the receiving end.
                
  Software:     Developed using Arduino 1.8.3 software.  Uses
                the RadioHead library.
  
  References:   - http://randomnerdtutorials.com 

  Date:         24 January 2018
 
  Author:       Cheshoare
--------------------------------------------------------------*/

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

void setup()
{
    Serial.begin(9600);   // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    const char *msg = "Received ok.";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(1000);
}
