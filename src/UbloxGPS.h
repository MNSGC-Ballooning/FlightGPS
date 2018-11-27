#ifndef UbloxGPS_h
#define UbloxGPS_h

#include "FlightGPS.h"

class UbloxGPS : public FlightGPS {
  public:
    UbloxGPS(Stream* port);
    void init();
    bool setAirborne();
  private:
    typedef FlightGPS super;
};

#endif

