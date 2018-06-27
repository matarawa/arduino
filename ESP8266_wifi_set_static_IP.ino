/*--------------------------------------------------------------
  Program:      WiFi_set_static_IP

  Description:  Sets a static IP address for the wifi device
                connecting to the LAN.
  
  Hardware:     Tested with NodeMCU ESP8266 12E
                
  Software:     Developed using Arduino 1.8.3 software.
  
  References:   - WiFi library documentation:
                  https://www.arduino.cc/en/Reference/WiFi

  Date:         27 June 2018
 
  Author:       cheshoare
--------------------------------------------------------------*/

#include <ESP8266WiFi.h>

const char* ssid = "SPARK-B315-532E";
const char* password = "YGF8Y070BE0";

IPAddress staticIP(192,168,1,14);
IPAddress gateway(192,168,1,254);
IPAddress subnet(255,255,255,0);

void setup(void)
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s\n", ssid);
  WiFi.begin(ssid, password);
  WiFi.config(staticIP, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {}
