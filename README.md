# FlightGPS

A library for various gps modules intended for high-altitude balloon use.
Supports reading and processing of NMEA data on all modules. Uses subclasses to implement module-specific functions (currently only calibration for airborne mode on Ublox devices).

## Library Dependencies

This library depends on the following additional Arduino libraries:
* [TinyGPS](https://github.com/mikalhart/TinyGPS)