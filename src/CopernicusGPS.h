#ifndef CopernicusGPS_h
#define CopernicusGPS_h

#include "FlightGPS.h"

class CopernicusGPS : public FlightGPS {
  public:
    CopernicusGPS(Stream* port);
};

#endif