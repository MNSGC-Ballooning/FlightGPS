# UbloxGPS

A library for Ublox gps modules intended for high-altitude balloon use.
Supports reading and processing of NMEA data, and calibration of device to airborne mode.

## Library Dependencies

This library depends on the following additional Arduino libraries:
* [TinyGPS](https://github.com/mikalhart/TinyGPS)

## Serial Connection Notes

This library is designed to support both hard and software serial connections to gps modules. By default,
this library automatically #includes the SoftwareSerial.h library. If building for a board that doesn't
support SoftwareSerial, simply //comment out the #include statement on line 8 of [UbloxGPS.h](src/UbloxGPS.h).
This can also be done to save memory if no SoftwareSerial connections are used.