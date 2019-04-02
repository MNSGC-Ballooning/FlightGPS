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
  while (available()) {
    parser.encode(read());
  }
}

//functions for retrieving gps data for program use
double FlightGPS::getLat() {return parser.location.lat();}
double FlightGPS::getLon() {return parser.location.lng();}
double FlightGPS::getAlt_meters() {return parser.altitude.meters();}
double FlightGPS::getAlt_feet() {return parser.altitude.feet();}
byte FlightGPS::getHour() {return parser.time.hour();}
byte FlightGPS::getMinute() {return parser.time.minute();}
byte FlightGPS::getSecond() {return parser.time.second();}
byte FlightGPS::getDay() {return parser.date.day();}
byte FlightGPS::getMonth() {return parser.date.month();}
unsigned int FlightGPS::getYear() {return parser.date.year();}
byte FlightGPS::getSats() {return parser.satellites.value();}
unsigned long FlightGPS::getFixAge() {return parser.altitude.age();}