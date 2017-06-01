#include <Arduino.h>
#include "UbloxGPS.h"

UbloxGPS::UbloxGPS(HardwareSerial* port) {
	hardPort = port;
	usingSoftSerial = false;
}

UbloxGPS::UbloxGPS(SoftwareSerial* port) {
	softPort = port;
	usingSoftSerial = true;
}

void UbloxGPS::initialize() {
	if (usingSoftSerial) softPort->begin(9600);
	else hardPort->begin(9600);
	setAirborne();
}

String UbloxGPS::setAirborne() {
	byte airMode[] = {0xB5,0x62,0x06,0x24,0x24,0x00,0x00,0x05,0x06,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0,0};
	byte length = 44;
	addChecksum(airMode, length);
	String response = "";
	write(airMode, length);
	delay(10);
	while (isAvailable()) {response += read();}
	return response;
}

void UbloxGPS::addChecksum(byte message[], byte length) {
	byte ckA=0, ckB=0;
	for (int i = 2; i<length-2; i++) {
		ckA = ckA + message[i];
		ckB = ckB + ckA;
	}
	message[length-2] = ckA;
	message[length-1] = ckB;
}

void UbloxGPS::update() {
	bool newData;
	char c;
	while (isAvailable()) {
		if(parser.encode(read())) newData = true;
	}
	if (newData) {
		parser.f_get_position(&lat, &lon, &fixAge);
		alt = parser.f_altitude();
		parser.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundreths, &fixAge);
	}
}

bool UbloxGPS::isAvailable() {
	if (usingSoftSerial) return (softPort->available() > 0);
	else return (hardPort->available() > 0);
}

char UbloxGPS::read() {
	if (usingSoftSerial) return (softPort->read());
	else return (hardPort->read());
}

void UbloxGPS::write(byte data[], byte length) {
	if (usingSoftSerial) softPort->write(data, length);
	else hardPort->write(data, length);
}

float UbloxGPS::getLat() {return lat;}
float UbloxGPS::getLon() {return lon;}
float UbloxGPS::getAlt() {return alt;}
byte UbloxGPS::getHour() {return hour;}
byte UbloxGPS::getMinute() {return minute;}
byte UbloxGPS::getSecond() {return second;}
byte UbloxGPS::getDay() {return day;}
byte UbloxGPS::getMonth() {return month;}
byte UbloxGPS::getYear() {return year;}
byte UbloxGPS::getSats() {return sats;}
unsigned long UbloxGPS::getFixAge() {return fixAge;}