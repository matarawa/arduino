#!/usr/bin/python

##
## Script listens to serial port, and inserts values into a database with a timestamp
##
## Requires pySerial to be installed 

import serial
from time import strftime, time
import psycopg2

serial_port = '/dev/ttyUSB0'; #Edit this if needed to change the defined port
baud_rate = 9600; #In arduino, Serial.begin(baud_rate)

# Read line from serial port data, split the line at each comma
ser = serial.Serial(serial_port, baud_rate)
print('\n' + strftime("%Y-%m-%d %H:%M:%S"));
print(ser.name + ' is open...');
line = ser.readline();
line = line.split(",");

# Connect to an existing database
conn = psycopg2.connect(database="testdb", user = "papa", password = "PGPapa@557", host = "127.0.0.1", port = "5432")
print "Opened database successfully"

# Open a cursor to perform database operations
cur = conn.cursor()

# Insert data from serial port into database, together with timestamp
cur.execute("INSERT INTO myschema.dht11logs (time, temperature, humidity) VALUES (%s, %s, %s)", (strftime("%Y-%m-%d %H:%M:%S"), float(line[0]), float(line[1])))
print "Data inserted from serial port read into database successfully"

# Make the changes to the database persistent
conn.commit()
print "Made database changes persistent"

# Close communication with the database
cur.close()
conn.close()
print "Closed database successfully\n"