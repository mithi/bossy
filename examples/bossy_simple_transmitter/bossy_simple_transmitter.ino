/*
  This sketch communicates data wireless everytime Bossy detects a change.
  It also prints this in the Serial monitor.
  It sends two bytes at a time, the first byte contains the id of the input
  while the second byte contains the current state or reading of that said input.

  This sketch does NOT use the LED Matrix.
  Use `bossy_simple_receiver.ino` in the receiving microcontroller
  to verify that Bossy is successfully transmitting data
*/


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

#include <Bossy.h>

using namespace BossyInputSets;
using namespace BossyConstants;

#define CE_PIN 9
#define CSN_PIN 10
RF24 radio(CE_PIN, CSN_PIN);
const byte ADDRESS[6] = "00001";

// First byte is the input id, Second byte
// is the state or reading of/from input id
uint8_t message_to_send[2] = {0xFF, 0x00};

Bossy bossy;

void setup() {
 while (!Serial);
 Serial.begin(9600);

 printf_begin();
 radio.begin();
 //radio.setAutoAck(false);
 radio.setDataRate(RF24_2MBPS);
 radio.setPALevel(RF24_PA_MIN);
 radio.setRetries(3, 5);
 radio.openWritingPipe(ADDRESS);
 radio.stopListening();
 radio.printDetails();
}

void loop() {

  for (uint8_t i = 0; i < NUMBER_OF_BUTTONS; i++) {
    if (bossy.hasChangedState(button_ids[i])) {
      uint8_t value = bossy.savedState(button_ids[i]);
      send_message(button_ids[i], value, "Button changed. Sent: ");
    }
  }

  for (uint8_t i = 0; i < NUMBER_OF_SWITCHES; i++) {
    if (bossy.hasChangedState(switch_ids[i])) {
      uint8_t value = bossy.savedState(switch_ids[i]);
      send_message(switch_ids[i], value, "Switch changed. Sent: ");
    }
  }

  for (uint8_t i = 0; i < NUMBER_OF_STICKS; i++) {
    if (bossy.hasChangedState(stick_ids[i])) {
      uint8_t value = bossy.savedState(stick_ids[i]);
      send_message(stick_ids[i], value, "Joystick changed. Sent: ");
    }
  }

  for (uint8_t i = 0; i < NUMBER_OF_POTENTIOMETERS; i++) {
    if (bossy.hasChangedReading(potentiometer_ids[i])) {
      uint8_t value = bossy.savedReadingLowRes(potentiometer_ids[i]);
      send_message(potentiometer_ids[i], value, "Potentiometer changed. Sent: ");
    }
  }
}

void send_message(uint8_t input_id, uint8_t value, String notice) {
  message_to_send[0] = input_id;
  message_to_send[1] = value;
  radio.write(&message_to_send, sizeof(message_to_send));

  Serial.print(notice);
  Serial.print(message_to_send[0]);
  Serial.print(" ");
  Serial.println(message_to_send[1]);
}
