#ifndef FlightGPS_h
#define FlightGPS_h

#include <Arduino.h>
#include <TinyGPS++.h>

#define ADAFRUIT_BAUD 9600
#define COPERNICUS_BAUD 4800

class FlightGPS : public Stream {
  public:
    //Constructor and Destructor
    FlightGPS(Stream* port);
    virtual ~FlightGPS(){}
    //Virtual Stream functions
    int available() {return port->available();}
    int peek() {return port->peek();}
    int read() {return port->read();}
    //Virtual Print functions
    int availableForWrite() {return port->availableForWrite();}
    void flush() {port->flush();}
    size_t write(uint8_t b) {return port->write(b);}
    size_t write(const uint8_t *buffer, size_t size) {return port->write(buffer, size);}
    //setup function
    virtual void init();
    //data polling functions
    void update();
    double getLat();
    double getLon();
    double getAlt_meters();
    double getAlt_feet();
    byte getHour();
    byte getMinute();
    byte getSecond();
    byte getDay();
    byte getMonth();
    unsigned int getYear();
    byte getSats();
    unsigned long getFixAge();
  private:
    Stream* port;
    TinyGPSPlus parser;
};

#endif