#ifndef UbloxGPS_h
#define UbloxGPS_h

#include "FlightGPS.h"

#define UBLOX_BAUD 9600

class UbloxGPS : public FlightGPS {
  public:
    UbloxGPS(Stream* port);
    void init();
    bool setAirborne();
};

#endif

