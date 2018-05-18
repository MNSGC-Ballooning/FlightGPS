#include "CopernicusGPS.h"

//constructor for hardware serial connection
CopernicusGPS::CopernicusGPS(HardwareSerial* port):FlightGPS(port) {}

//constructor for software serial connection
#ifdef SoftwareSerial_h
CopernicusGPS::CopernicusGPS(SoftwareSerial* port):FlightGPS(port) {}
#endif

//call during setup to begin appropriate serial connection
void CopernicusGPS::initialize() {
#ifdef SoftwareSerial_h
  if (usingSoftSerial)
    softPort->begin(4800);
  else
#endif
    hardPort->begin(4800);
  update();
}