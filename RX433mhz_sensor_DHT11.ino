    /*  RX433mhz_sensor_DHT11
     *   
     *  Wireless temperature and humidity sensor.  Uses DHT11 sensor to 
     *  measure temperature and humidity, then read by an arduino board.
     *  Reads the sensor data.  Sends sensor data from one arduino to
     *  another via a 434MHz ASK radio transmitter.  Requires a 
     *  corresponding arduino, code and 434MHz receiver at the other end.
     *  
     *  Author: cheshoare
     *  Date: 2018
     *  
     *  Developed using the Arduino 1.8.3 software.
     *  Requires the DHT library and RadioHead library (RH_ASK class) - 
     *  thank you to the developers of those libraries.
     */

     
    #include <RH_ASK.h>
    #include <SPI.h> // Not actualy used but needed to compile

    RH_ASK driver;

    // Define the data structure for the sensor data
    struct dataStruct{
      float humidity ;
      float temp;
    }myData;

    void setup()
    {
      Serial.begin(9600);  // Debugging only
      if (!driver.init())
         Serial.println("init failed");     
    }
    
    void loop()
    {
      uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
      uint8_t buflen = sizeof(buf);

      if (driver.recv(buf, &buflen)) // Non-blocking
      {
        int i;

        // Message with a good checksum received, dump it.
        driver.printBuffer("Got:", buf, buflen);
        memcpy(&myData, buf, sizeof(myData));
        Serial.print(myData.temp);
        Serial.print(",");
        Serial.print(myData.humidity);
        Serial.print('\n');
      }
    }
