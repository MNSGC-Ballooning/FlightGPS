#include "FlightGPS.h"

//constructor
FlightGPS::FlightGPS(Stream* port):
  port(port) {
}

//call during setup to get initial gps values
void FlightGPS::init() {
  update();
}

//call during loop to read and parse gps data
void FlightGPS::update() {
  bool newData;
  while (available()) {
    if(parser.encode(read())) newData = true;
  }
  if (newData) {
    parser.f_get_position(&lat, &lon, &fixAge);
    alt = parser.f_altitude();
    sats = parser.satellites();
    parser.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundreths, &fixAge);
  }
}

//functions for retrieving gps data for program use
float FlightGPS::getLat() {return lat;}
float FlightGPS::getLon() {return lon;}
float FlightGPS::getAlt() {return alt;}
byte FlightGPS::getHour() {return hour;}
byte FlightGPS::getMinute() {return minute;}
byte FlightGPS::getSecond() {return second;}
byte FlightGPS::getDay() {return day;}
byte FlightGPS::getMonth() {return month;}
byte FlightGPS::getYear() {return year;}
byte FlightGPS::getSats() {return sats;}
unsigned long FlightGPS::getFixAge() {return fixAge;}