#include <Arduino.h>
#include "Ublox.h"

UbloxGPS::UbloxGPS(Stream* port) {
	this.port = port;
}

void UbloxGPS::initialize() {
	port->begin(9600);
	setAirborne();
}

void UbloxGPS::setAirborne() {
	byte[] message = [0xB5,0x62,0x06,0x24,0x24,0x00,0x00,0x05,0x06,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0,0];
	byte[36] buffer;
	for (int i = 0; i < 36; i++) {
		buffer[i] = message[i+5];
	}
	unsigned short checksum = findChecksum(buffer);
	message[42] = byte((checksum / 0x100));
	message[43] = byte((checksum % 0x100));
	port->print(message);
}

unsigned short UbloxGPS::findChecksum(byte[] buffer); {
	byte ckA=0, ckB=0;
	for (int i = 0; i<sizeOf(buffer)/sizeOf(buffer[0]); i++) {
		ckA = ckA + buffer[i];
		ckB = ckB + ckA;
	}
	return (ckA * 0x100 + ckB);
}

void UbloxGPS::read() {
	while (port->available() > 0) {
		if(parser.encode(port->read())) {
			parser.f_get_position(&lat, &lon, &fixAge);
			alt = parser.f_altitude();
			parser.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundreths, &fixAge);
		}
	}
}

float UbloxGPS::getLat() {return lat;}
float UbloxGPS::getLon() {return lon;}
float UbloxGPS::getAlt() {return alt;}
byte UbloxGPS::getHour() {return hour;}
byte UbloxGPS::getMinute() {return minute}
byte UbloxGPS::getSecond() {return second}
byte UbloxGPS::getDay() {return day;}
byte UbloxGPS::getMonth() {return month;}
byte UbloxGPS::getYear() {return year;}
byte UbloxGPS::getSats() {return sats}
unsigned long UbloxGPS::getFixAge() {return fixAge}