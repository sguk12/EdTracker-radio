/**
 * This is a declaration file for the shared structures of 
 * Radio Joy project.
 * It uses NRF24L01 2.4GHz breakout board for wireless communications.
 * 
 */ 


/**
 * This structure is used to transfer the data between the sensor units:
 * -Joystick and Throttle
 * -Rudder pedals
 * and the USB "stick"
 */
struct RadioJoystick {
  byte fromToByte;
  int16_t axisX;
  int16_t axisY;
  int16_t axisThrottle;
  int16_t axisPropellor;
  int16_t axisTrim;
  int16_t axisRudder;
  int16_t buttons;
} ;

/**
 * These constants are to identify the senders and receivers 
 */
const int8_t receiverId = B00010000;
const int8_t rudderId = B00000001;
const int8_t throttleId = B00000010;
const int8_t edTrackerId = B00000011;
const int8_t fromRudderToReceiver = receiverId | rudderId;
const int8_t fromThrottleToReceiver = receiverId | throttleId;
const int8_t fromEdTrackerToReceiver = receiverId | edTrackerId;

byte RECEIVER_ADDRESS[6] = "1_Joy";
byte TRANSMITTER_ADDRESS[6] = "2_Joy";


