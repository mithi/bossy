/*
  IMPORTANT: Do not upload this to your Bossy Controller.

  Sample code to test if the receiver is successfully
  able to get transmitted message from the Bossy Controller
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);
const byte ADDRESS[6] = "00001";

void setup() {
  while (!Serial);
  Serial.begin(9600);
  printf_begin();
  radio.begin();
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.setRetries(3,5);
  radio.openReadingPipe(0, ADDRESS);
  radio.startListening();

  radio.printDetails();
}

void loop() {
  if (radio.available()) {
    uint8_t received_message[2] = {0xFF, 0x00};
    radio.read(&received_message, sizeof(received_message));

    uint8_t input_id = received_message[0];
    uint8_t value = received_message[1];

    // The received message only makes sense if
    // we know the input id
    const uint8_t NUMBER_OF_INPUTS = 25;
    if (input_id < NUMBER_OF_INPUTS) {
      Serial.print("input id: ");
      Serial.print(input_id);
      Serial.print(" | ");
      Serial.print("value: ");
      Serial.println(value);
    }
  }
}
