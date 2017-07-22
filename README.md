# EdTracker-radio
This is a fork of EDTracker2 from https://github.com/brumster/EDTracker2
This version of EdTracker has two units: 
1) the sensor unit, which reads MPU values and transmits them to a receiver. It does not need to be plugged to usb at the time of play. It needs to be connected to USB for calibration only. It uses the stock EdTracker calibration application.
2) the receiver unit, which is connected to USB and presents itself as a joystick. It receives the MPU data and refreshes the joystick axis values.

## The sensor unit
The below is the list of libraries needed for the sensor unit. Most of them are taken from the original EDTracker2 Hardware repo https://github.com/brumster/EDTracker2_ArduinoHardware
- I2Cdev
- InvensenseMotionDriver
- SoftwareSerial
- RF24-master - https://tmrh20.github.io/RF24

## The receiver unit
The receiver/joystick unit needs the following libraries:
- Joystick - https://github.com/MHeironimus/ArduinoJoystickLibrary
- RF24-master - https://tmrh20.github.io/RF24


