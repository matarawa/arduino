/*--------------------------------------------------------------
  Program:      RX433mhz_basic

  Description:  Displays to serial port a message received by an
                Arduino with a 433MHz recceiver.
  
  Hardware:     Arduino Uno and RF 433MHz receiver. Needs a
                corresponding RF 433MHz transmitter and Arduino
                at the transmitting end.
                
  Software:     Developed using Arduino 1.8.3 software.  Uses
                the RadioHead library.
  
  References:   - http://randomnerdtutorials.com 

  Date:         24 January 2018
 
  Author:       Cheshoare
--------------------------------------------------------------*/

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

void setup()
{
    Serial.begin(9600); // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      Serial.println((char*)buf); // the received message.
    }
}
