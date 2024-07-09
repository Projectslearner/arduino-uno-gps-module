#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Create a SoftwareSerial object for the GPS module
SoftwareSerial gpsSerial(4, 3); // RX, TX

// Create a TinyGPS++ object
TinyGPSPlus gps;

void setup() {
  // Start the serial communication with the computer
  Serial.begin(9600);
  // Start the serial communication with the GPS module
  gpsSerial.begin(9600);

  Serial.println("GPS Module with Arduino Uno");
}

void loop() {
  // This sketch displays information every time a new sentence is correctly encoded.
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      displayInfo();
    }
  }

  // If 5 seconds pass and there are no GPS characters received, show a warning
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println("No GPS detected: check wiring.");
    while(true);
  }
}

void displayInfo() {
  if (gps.location.isValid()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());

    Serial.print("Date: ");
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());

    Serial.print("Time: ");
    Serial.print(gps.time.hour());
    Serial.print(":");
    Serial.print(gps.time.minute());
    Serial.print(":");
    Serial.println(gps.time.second());
  } else {
    Serial.println("Location not valid");
  }

  Serial.println();
}
