#ifndef UbloxGPS_h
#define UbloxGPS_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>


class UbloxGPS {
	public:
		UbloxGPS(HardwareSerial* port);
		UbloxGPS(SoftwareSerial* port);
		void initialize();
		void setAirborne();
		void read();
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
		TinyGPS parser;
		HardwareSerial* hardPort;
		SoftwareSerial* softPort;
		bool usingSoftSerial;
		float lat, lon, alt;
		byte day, month, hour, minute, second, hundreths;
		int year;
		unsigned long fixAge;
		byte sats;
		unsigned short findChecksum(byte buffer[]);
		bool isAvailable();
};

#endif

