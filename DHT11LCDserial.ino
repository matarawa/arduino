// include the library code:
#include <LiquidCrystal.h>
#include "DHT.h"

// set the DHT Pin
#define DHTPIN 8

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int countSensorReads = 0;

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  dht.begin();
  Serial.begin(9600);
  
  // Print a message to the LCD.
  lcd.print("Temp:  Humidity:");
}

void loop() {

  delay(500);
      
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // read humidity
  float h = dht.readHumidity();
  //read temperature in Celsius
  float c = dht.readTemperature();

  if (isnan(h) || isnan(c)) {
    lcd.print("ERROR");
    return;
  }

  lcd.print(c);
  lcd.setCursor(7,1);
  lcd.print(h);  

  if (countSensorReads >= 18) {
    Serial.print(c);
    Serial.print(",");
    Serial.print(h);
    Serial.print('\n');
    countSensorReads = 0;
  }
  else {
    countSensorReads++;
  }
}
