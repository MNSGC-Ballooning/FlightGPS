#ifndef FlightGPS_h
#define FlightGPS_h

#include <Arduino.h>
#include <TinyGPS.h>

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
    float getLat();
    float getLon();
    float getAlt();
    byte getHour();
    byte getMinute();
    byte getSecond();
    byte getDay();
    byte getMonth();
    byte getYear();
    byte getSats();
    unsigned long getFixAge();
  private:
    Stream* port;
    TinyGPS parser;
    float lat, lon, alt;
    byte day, month, hour, minute, second, hundreths;
    int year;
    unsigned long fixAge;
    byte sats;
};

#endif