#ifndef UbloxGPS_h
#define UbloxGPS_h

#include "FlightGPS.h"

class UbloxGPS: public FlightGPS {
  public:
    UbloxGPS(HardwareSerial* port);
#ifdef SoftwareSerial_h
    UbloxGPS(SoftwareSerial* port);
#endif
    void initialize();
    bool setAirborne();
  private:
    typedef FlightGPS super;
};

#endif

