#include "UbloxGPS.h"

//constructor for hardware serial connection
UbloxGPS::UbloxGPS(HardwareSerial* port):FlightGPS(port) {}

//constructor for software serial connection
#ifdef SoftwareSerial_h
UbloxGPS::UbloxGPS(SoftwareSerial* port):FlightGPS(port) {}
#endif

//call during setup to begin appropriate serial connection and set to airborne mode
void UbloxGPS::initialize() {
	super::initialize();
	setAirborne();
}

//sends calibration message to force module into airborne mode
bool UbloxGPS::setAirborne() {
	byte airMode[] = {0xB5,0x62,0x06,0x24,0x24,0x00,0xFF,0xFF,0x06,0x02,0x00,0x00,0x00,0x00,0x10,0x27,0x00,
						0x00,0x05,0x00,0xFA,0x00,0xFA,0x00,0x64,0x00,0x2C,0x01,0x00,0x00,0x00,0x00,0x10,
						0x27,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4C,0xBA};
	byte length = 44;
	byte response[10];
	byte acknowledge[] = {0xB5, 0x62, 0x05, 0x01, 0x02, 0x00, 0x06, 0x24, 0x32, 0x5B};
	bool ack = true;
	update();
	write(airMode, length);
	delay(100);
	for (byte i=0; i < 10; i++) {
		response[i] = read();
	}
	for (byte i=0; i < 10; i++) {
		if (response[i] != acknowledge[i]) ack = false;
	}
	return ack;
}