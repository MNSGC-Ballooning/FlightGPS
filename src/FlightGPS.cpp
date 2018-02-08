#include "FlightGPS.h"

//constructor for hardware serial connection
FlightGPS::FlightGPS(HardwareSerial* port):
  hardPort(port) {
  usingSoftSerial = false;
}

//constructor for software serial connection
#ifdef SoftwareSerial_h
FlightGPS::FlightGPS(SoftwareSerial* port):
  softPort(port) {
  usingSoftSerial = true;
}
#endif

//call during setup to begin appropriate serial connection
void FlightGPS::initialize() {
#ifdef SoftwareSerial_h
  if (usingSoftSerial)
    softPort->begin(9600);
  else
#endif
    hardPort->begin(9600);
  update();
}

//call during loop to read and parse gps data
void FlightGPS::update() {
  bool newData;
  while (isAvailable()) {
    if(parser.encode(read())) newData = true;
  }
  if (newData) {
    parser.f_get_position(&lat, &lon, &fixAge);
    alt = parser.f_altitude();
    sats = parser.satellites();
    parser.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundreths, &fixAge);
  }
}

//checks appropriate serial connection for available data
bool FlightGPS::isAvailable() {
#ifdef SoftwareSerial_h
  if (usingSoftSerial)
    return (softPort->available() > 0);
  else
#endif
    return (hardPort->available() > 0);
}

//calls read() function of appropriate serial connection
char FlightGPS::read() {
#ifdef SoftwareSerial_h
  if (usingSoftSerial)
    return (softPort->read());
  else
#endif
    return (hardPort->read());
}

//calls write() function of appropriate serial connection
void FlightGPS::write(byte data[], byte length) {
#ifdef SoftwareSerial_h
  if (usingSoftSerial)
    softPort->write(data, length);
  else
#endif
    hardPort->write(data, length);
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