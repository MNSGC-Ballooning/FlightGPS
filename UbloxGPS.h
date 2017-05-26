#ifndef UbloxGPS_h
#define UbloxGPS_h

#include <Arduino.h>
#include <TinyGPS.h>


class UbloxGPS {
	public:
		UbloxGPS(Stream* port);
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
		Stream* port;
		float lat, lon, alt;
		byte day, month, hour, minute, second, hundreths;
		unsigned int year;
		unsigned long fixAge;
		byte sats;
		unsigned short findChecksum(char[] buffer);
}

#endif

