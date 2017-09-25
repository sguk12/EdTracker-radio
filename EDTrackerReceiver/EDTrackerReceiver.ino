/**
 * This sketch is for a Receiver-USB unit of EdTracker.
 * This sketch is uploaded to a Pro Micro 8MHz 3.3V or Arduino Micro Pro 16Mhz 5V 
 * It receives the tilt and yaw data from EdTracker-radio unit via the radio channel 102 
 * (2.502GHz is outside of the WIFI band) and presents the data to the USB hub on the PC.
 * 
 * The transmitter is an EdTracker-radio unit. It is not using this sketch.
 * 
 */


#include <RF24.h>
#include <Joystick.h>
#include "RadioJoy.h"

#define LED_PIN 17
boolean blinkState;
// Timer related so track operations between loop iterations (LED flashing, etc)
unsigned long lastMillis = 0;

Joystick_ EdTracker(JOYSTICK_DEFAULT_REPORT_ID + 1, 
  JOYSTICK_TYPE_JOYSTICK, 0, 0,
  true, true, true, false, false, false,
  false, false, false, false, false);
  

RF24 radio(9, 8);// Arduino's pins connected to CE,CS pins on NRF24L01

void setup()
{
  EdTracker.setXAxisRange(-32767, 32767);
  EdTracker.setYAxisRange(-32767, 32767);
  EdTracker.setZAxisRange(-32767, 32767);
  EdTracker.begin(false);

//  Serial.begin(9600);   // Debugging only
//  while (!Serial);             // Leonardo: wait for serial monitor
//  Serial.println("setup");

  radio.begin();
  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(102);
  radio.openWritingPipe(TRANSMITTER_ADDRESS);
  radio.openReadingPipe(1,RECEIVER_ADDRESS);

  // Start the radio listening for data
  radio.startListening();

}

void loop()
{
//  Serial.println(F("loop"));

  // Send an invitation to the edtracker slave
  radio.stopListening();                                    // First, stop listening so we can talk.
  if (!radio.write( &fromEdTrackerToReceiver, sizeof(int8_t) )){ // This will block until complete
//    Serial.println(F("failed throttle"));
  }else{
    readSlaveResponseAndUpdateJoystick();
  }
  
  EdTracker.sendState();
  blink();
  delay(5);
}

void readSlaveResponseAndUpdateJoystick(){
//  Serial.println(F("read"));
  radio.startListening();                                    // Now, continue listening
  unsigned long started_waiting_at = millis();               // Set up a timeout period, get the current microseconds
  boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
  
  while ( ! radio.available() ){                             // While nothing is received
    if (millis() - started_waiting_at > 20 ){            // If waited longer than 20ms, indicate timeout and exit while loop
        timeout = true;
        break;
    }      
  }
      
  if ( timeout ){                                             // Describe the results
//    Serial.println(F("Failed, response timed out."));
  }else{
    RadioJoystick buf;
    radio.read( &buf, sizeof(buf) );
    if (buf.fromToByte == fromEdTrackerToReceiver) {
      // Message with a good checksum received.
      EdTracker.setXAxis(buf.axisX);
      EdTracker.setYAxis(buf.axisY);
      EdTracker.setZAxis(buf.axisRudder);
    } else{
//        Serial.print(F("Message is not from edtracker or not for me: "));
//        Serial.println(buf.fromToByte);
    }
  }
}

/*******************************************************************************************************
* Blink LED function
********************************************************************************************************/
void blink()
{
  unsigned long nowMillis = millis();
  if (nowMillis > lastMillis )
  {
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
    lastMillis = nowMillis + 500;
  }
}

