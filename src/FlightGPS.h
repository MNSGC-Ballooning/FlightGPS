#ifndef FlightGPS_h
#define FlightGPS_h

#include <Arduino.h>
#include <TinyGPS.h>

//Comment this out if inclusion causes errors, or using hard serial and want to save memory
#include <SoftwareSerial.h>

class FlightGPS {
  public:
    FlightGPS(HardwareSerial* port);
#ifdef SoftwareSerial_h
    FlightGPS(SoftwareSerial* port);
#endif
    virtual ~FlightGPS(){}
    virtual void initialize();
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
  protected:
    bool usingSoftSerial;
    HardwareSerial* hardPort;
#ifdef SoftwareSerial_h
    SoftwareSerial* softPort;
#endif
    bool isAvailable();
    char read();
    void write(byte data[], byte length);
  private:
    TinyGPS parser;
    float lat, lon, alt;
    byte day, month, hour, minute, second, hundreths;
    int year;
    unsigned long fixAge;
    byte sats;
};

#endif