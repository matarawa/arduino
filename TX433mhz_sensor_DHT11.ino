    /*  TX433mhz_sensor_DHT11
     *   
     *  Wireless temperature and humidity remote sensor data collection. 
     *  Receives temperature and humidity sensor values from remote arduino
     *  via 434MHz ASK radio TX and RX pair.  Prints received data to serial 
     *  monitor.  Requires a corresponding arduino, code and 434MHz transmitter
     *  at the other end.
     *  
     *  Author: cheshoare
     *  Date: 2018
     *  
     *  Developed using the Arduino 1.8.3 software.
     *  Requires the DHT library and RadioHead library (RH_ASK class) - 
     *  thank you to the developers of those libraries.
     */
     
    #include <DHT.h>
    #include <RH_ASK.h>
    #include <SPI.h> // Not actualy used but needed to compile

    // The following is needed when using the DHT11 sensor to collect data
    #define DHTPIN 8 // Defines pin number to which the sensor is connected
    #define DHTTYPE DHT11  // We are using the DHT11 sensor
    DHT dht(DHTPIN, DHTTYPE); // Creats a DHT object
 
    RH_ASK driver;

    // This may only be needed if the count is used to set the duration
    // between transmitions:
    // int countSensorReads = 0;
    
    // Define the data structure for the sensor data
    struct dataStruct{
      float humid ;
      float temp;
    }myData;

    byte tx_buf[sizeof(myData)] = {0};

    void setup()
    {
      Serial.begin(9600);    // Debugging only
      if (!driver.init())
        Serial.println("init failed");
         
      myData.humid = 50.00;
      myData.temp = 20.00;
    }
    
    void loop()
    {
      myData.humid = dht.readHumidity(); // Gets the value of the humidity
      myData.temp = dht.readTemperature(); // Gets the value of the temperature

      // Printing the results on the serial monitor
      Serial.print("Temperature = ");
      Serial.print(myData.temp);
      Serial.print(" *C ");
      Serial.print("    Humidity = ");
      Serial.print(myData.humid);
      Serial.println(" % ");
      
      memcpy(tx_buf, &myData, sizeof(myData) );
      byte zize=sizeof(myData);

      driver.send((uint8_t *)tx_buf, zize);

      // driver.send((uint8_t *)msg, strlen(msg));
      driver.waitPacketSent();
      // myData.counter++;
      delay(2000);
    }
