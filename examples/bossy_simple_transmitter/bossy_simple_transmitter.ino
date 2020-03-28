#include <Bossy.h>
#include <Bossy.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

#define CE_PIN 9
#define CSN_PIN 10
RF24 radio(CE_PIN, CSN_PIN);
const byte ADDRESS[6] = "00001";

// First byte is the input id, Second byte
// is the state or reading of/from input id

uint8_t message_to_send[2] = {0x00, 0x00};
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
    if (bossy.hasChangedState(buttons[i].id)) {
      uint8_t value = bossy.savedState(buttons[i].id);
      send_message(buttons[i].id, value, " Button change. Sent: ");
    }
  }

  for (uint8_t i = 0; i < NUMBER_OF_SWITCHES; i++) {
    if (bossy.hasChangedState(switches[i].id)) {
      uint8_t value = bossy.savedState(switches[i].id);
      send_message(switches[i].id, value, " Switch change. Sent: ");
    }
  }

  for (uint8_t i = 0; i < NUMBER_OF_STICKS; i++) {
    if (bossy.hasChangedState(sticks[i].id)) {
      uint8_t value = bossy.savedState(sticks[i].id);
      send_message(sticks[i].id, value, " Joystick change. Sent: ");
    }
  }

  for (uint8_t i = 0; i < NUMBER_OF_POTENTIOMETERS; i++) {
    if (bossy.hasChangedReading(potentiometers[i])) {
      uint8_t value = bossy.savedReadingLowRes(potentiometers[i]);
      send_message(potentiometers[i], value, " Pot change. Sent: ");

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
