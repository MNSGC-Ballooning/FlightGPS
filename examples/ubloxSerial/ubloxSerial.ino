/* Sample code to read a ublox gps and output data to the Serial Monitor
 */

#include <UbloxGPS.h>
#include <SoftwareSerial.h>

//GPS object needs a serial line to read
SoftwareSerial ss = SoftwareSerial(2,3);
//Pass a reference to this serial line to the GPS constructor
UbloxGPS gps = UbloxGPS(&ss);
//Alternately, use a hard serial line if the microcontroller supports it
//UbloxGPS gps = UbloxGPS(&Serial1);

//timer variable for regular print statements
unsigned long timer = 0;

void setup() {
  //Begins serial monitor communication
  Serial.begin(115200);

  //GPS serial connection needs to be started manually
  ss.begin(UBLOX_BAUD); //If using SoftwareSerial
  //Serial1.begin(UBLOX_BAUD); //If using Serial1
  
  //Start tracking gps and attempt to set airborne mode (no indication of success)
  gps.init();

  //Attempt to set to airborne mode, and report results to serial monitor
  if(gps.setAirborne())
    Serial.println("Air mode successfully set.");
  else
    Serial.println("WARNING: Failed to set to air mode. Altitude data may be unreliable.");
}

void loop() {
  //Update the gps - both reads and parses data
  gps.update();

  //once per second, print results to serial monitor
  if(millis() - timer > 1000) {
    timer = millis();
    Serial.print("Date: " + String(gps.getMonth()) + "/" + String(gps.getDay()) + "/" + String(gps.getYear()));
    Serial.print("  Time: " + String(gps.getHour()) + ":" + String(gps.getMinute()) + ":" + String(gps.getSecond()));
    Serial.print("  Position: " + String(gps.getLat()) + ", " + String(gps.getLon()) + ", " + String(gps.getAlt()));
    Serial.println("  Sats: " + String(gps.getSats()));
  }
}