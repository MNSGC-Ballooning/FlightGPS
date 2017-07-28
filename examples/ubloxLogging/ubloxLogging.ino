/*  Sample code to read a ublox gps and log data to an SD card.
 *  Includes calibration for airborne mode.
 */

#include <SD.h>
#include <UbloxGPS.h>

#define chipSelect 10 //Switch to appropriate pin for breakout/shield used

//GPS object needs a serial line to read
SoftwareSerial ss = SoftwareSerial(2,3);
//Pass a reference to this serial line to the GPS constructor
UbloxGPS gps = UbloxGPS(&ss);
//Alternately, use a hard serial line if the microcontroller supports it
//UbloxGPS gps = UbloxGPS(&Serial1);

//global variable for datalogging
char filename[] = "Ublox00.csv";
File datalog;
unsigned long timer = 0;

void setup() {
  //set up file for datalogging
  if(SD.begin(chipSelect)) {
    for(byte i = 0; i < 100; i++) {
      filename[5] = i/10 + '0';
      filename[6] = i%10 + '0';
      if (!SD.exists(filename)) {
        datalog = SD.open(filename, FILE_WRITE);
        break;
      }
    }
  }
  
  //Begins gps communication. Also attempts to set to airborne mode once by default, but doesn't indicate success
  gps.initialize();

  //Attempt to set to airborne 3 times. If successful, records result and breaks loop. If unsuccessful, saves warning and moves on
  byte i = 0;
  while (i < 3) {
    i++;
    if (gps.setAirborne()) {
      datalog.println("Air mode successfully set.");
      break;
    }
    else if (i == 3)
      datalog.println("WARNING: Failed to set to air mode (3 attemtps). Altitude data may be unreliable.");
    else
      datalog.println("Error: Air mode set unsuccessful. Reattempting...");
  }

  //print header line to SD file
  String header = "Date,Time,Lattitude,Longitude,Altitude (m),Satellites,Fix";
  datalog.println(header);
  datalog.close();
}

void loop() {
  //Update the gps - both reads and parses data
  gps.update();

  //log data once every second
  if(millis() - timer > 1000) {
    timer = millis();
    //All data is returned as numbers (int or float as appropriate), so values must be converted to strings before logging
    String data = String(gps.getMonth()) + "/" + String(gps.getDay()) + "/" + String(gps.getYear()) + ","
                  + String(gps.getHour()) + ":" + String(gps.getMinute()) + ":" + String(gps.getSecond()) + ","
                  + String(gps.getLat(), 4) + "," + String(gps.getLon(), 4) + "," + String(gps.getAlt(), 1) + ","
                  + String(gps.getSats()) + ",";
    //GPS should update once per second, if data is more than 2 seconds old, fix was likely lost
    if(gps.getFixAge() > 2000)
      data += "No Fix,";
    else
      data += "Fix,";
    datalog = SD.open(filename, FILE_WRITE);
    datalog.println(data);
    datalog.close();
  }
  //slows down program slightly to prevent unnecessary repeated calls to update(). Remove if running additional code.
  delay(10);
}

