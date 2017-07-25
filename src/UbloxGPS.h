#ifndef UbloxGPS_h
#define UbloxGPS_h

#include <Arduino.h>
#include <TinyGPS.h>

//Comment this out if inclusion causes errors, or using hard serial and want to save memory
#include <SoftwareSerial.h>


class UbloxGPS {
	public:
		UbloxGPS(HardwareSerial* port);
#ifdef SoftwareSerial_h
		UbloxGPS(SoftwareSerial* port);
#endif
		void initialize();
		bool setAirborne();
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
		TinyGPS parser;
		HardwareSerial* hardPort;
#ifdef SoftwareSerial_h
		SoftwareSerial* softPort;
#endif
		bool usingSoftSerial;
		float lat, lon, alt;
		byte day, month, hour, minute, second, hundreths;
		int year;
		unsigned long fixAge;
		byte sats;
		void addChecksum(byte message[], byte length);
		bool isAvailable();
		char read();
		void write(byte data[], byte length);
};

#endif

