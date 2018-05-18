#ifndef CopernicusGPS_h
#define CopernicusGPS_h

#include "FlightGPS.h"

class CopernicusGPS: public FlightGPS {
  public:
    CopernicusGPS(HardwareSerial* port);
#ifdef SoftwareSerial_h
    CopernicusGPS(SoftwareSerial* port);
#endif
    void initialize();
};

#endif