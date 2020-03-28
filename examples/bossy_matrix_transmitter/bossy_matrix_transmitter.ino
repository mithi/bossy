/*
  This sketch communicates data wireless everytime Bossy detects a change.
  It sends two bytes at a time, the first byte contains the id of the input
  while the second byte contains the current state or reading of that said input

  It also does everything what the `bossy_matrix.ino`,
  user feedback is provided via the LED Matrix

  Use `bossy_simple_receiver.ino` in the receiving microcontroller
  to verify that Bossy is successfully transmitting datain
*/
#include <Bossy.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

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
uint8_t message_to_send[2] = {0xFF, 0x00};

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();
Bossy bossy;

/* RECALL that the possible states are just
different ways to interpret a number from 0 to 4

 0------------1------------2------------3------------4            > SCALE
 |            |            |            |            |
 PUSH.........|............|............|............NOT_PUSHED   > button
 LEFT.........|............|............|............RIGHT        > spdt switch on-on
 LEFT.........|.........NEUTRAL.........|............RIGHT        > spdt switch on-off-on
 LEFT....LEFT_CENTER....NEUTRAL.....RIGHT_CENTER.....RIGHT        > joystick x axis
 UP......UP_CENTER......NEUTRAL.....DOWN_CENTER......DOWN         > joystick y axis
 UP...........|.........NEUTRAL.........|............DOWN
 UP...........|............|............|............DOWN
 |            |            |            |            |
 0------------1------------2------------3------------4            > SCALE

*/
const uint8_t NUMBER_OF_STATES = 5;
const uint8_t button_colors[NUMBER_OF_STATES] =  {LED_GREEN, LED_GREEN, LED_GREEN, LED_GREEN, LED_RED};
const uint8_t stick_first_colors[NUMBER_OF_STATES] = {LED_RED, LED_RED, LED_GREEN, LED_GREEN, LED_GREEN};
const uint8_t stick_second_colors[NUMBER_OF_STATES] = {LED_GREEN, LED_GREEN, LED_GREEN, LED_RED, LED_RED};

const uint8_t sw_first_colors[NUMBER_OF_STATES] = {LED_RED, LED_RED, LED_YELLOW, LED_YELLOW, LED_YELLOW};
const uint8_t sw_second_colors[NUMBER_OF_STATES] = {LED_YELLOW, LED_YELLOW, LED_RED, LED_YELLOW, LED_YELLOW};
const uint8_t sw_third_colors[NUMBER_OF_STATES] = {LED_YELLOW, LED_YELLOW, LED_YELLOW, LED_RED, LED_RED};

#define POTMODE false
#define STICKMODE true

bool mode = STICKMODE;

void setup() {
  matrix.begin(0x70);
  display_begin();

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
      send_state_update(buttons[i].id);
      update_button_display(buttons[i]);
    }
  }
  for (uint8_t i = 0; i < NUMBER_OF_SWITCHES; i++) {
    if (bossy.hasChangedState(switches[i].id)) {
      send_state_update(switches[i].id);
      update_switch_display(switches[i]);
    }
  }

  for (uint8_t i = 0; i < NUMBER_OF_STICKS; i++) {
    if (bossy.hasChangedState(sticks[i].id)) {
      send_state_update(sticks[i].id);
      if (mode == STICKMODE) {
        update_stick_display(sticks[i]);
      }
    }
  }

  for (uint8_t i = 0; i < NUMBER_OF_POTENTIOMETERS; i++) {
    if (bossy.hasChangedReading(potentiometers[i])) {
      send_reading_update(potentiometers[i]);
      if (mode == POTMODE) {
        update_pot_display(i, potentiometers[i]);
      }
    }
  }

  toggle_mode_if_commanded();
  matrix.writeDisplay();
}

void send_state_update(uint8_t input_id) {
  const uint8_t value = bossy.savedState(input_id);
  message_to_send[0] = input_id;
  message_to_send[1] = value;
  radio.write(&message_to_send, sizeof(message_to_send));
}

void send_reading_update(uint8_t input_id) {
  const uint8_t value = bossy.savedReadingLowRes(input_id);
  message_to_send[0] = input_id;
  message_to_send[1] = value;
  radio.write(&message_to_send, sizeof(message_to_send));
}


void update_button_display(const struct Button button) {
  const uint8_t state = bossy.savedState(button.id);
  const uint8_t color = button_colors[state];
  const uint8_t x = button.pixel[Xi];
  const uint8_t y = button.pixel[Yi];
  matrix.drawPixel(x, y, color);

  matrix.writeDisplay();
}

void update_stick_display(const struct Stick stick) {
  const uint8_t state = bossy.savedState(stick.id);

  const uint8_t color1 = stick_first_colors[state];
  const uint8_t color2 = stick_second_colors[state];

  const uint8_t x1 = stick.first_pixel[Xi];
  const uint8_t y1 = stick.first_pixel[Yi];

  const uint8_t x2 = stick.second_pixel[Xi];
  const uint8_t y2 = stick.second_pixel[Yi];

  matrix.drawPixel(x1, y1, color1);
  matrix.drawPixel(x2, y2, color2);

  matrix.writeDisplay();
}

void update_switch_display(const struct SwitchSPDT sw) {
  const uint8_t state = bossy.savedState(sw.id);

  const uint8_t color[3] = {sw_first_colors[state], sw_second_colors[state], sw_third_colors[state]};
  const uint8_t x[3] = {sw.first_pixel[Xi], sw.second_pixel[Xi], sw.third_pixel[Xi]};
  const uint8_t y[3] = {sw.first_pixel[Yi], sw.second_pixel[Yi], sw.third_pixel[Yi]};

  for (uint8_t i = 0; i < 3; i++) {
    matrix.drawPixel(x[i], y[i], color[i]);
  }

  matrix.writeDisplay();
}

void update_pot_display(uint8_t pot_id, uint8_t input_id) {
  const uint16_t reading = bossy.savedReading(input_id);
  const uint16_t blocks = min((reading - 100) / 100, 8);
  const uint8_t NUMBER_OF_BLOCKS = 8;

  for (uint8_t i = 0; i < NUMBER_OF_BLOCKS; i++) {
    matrix.drawPixel(i, pot_id + 1, LED_GREEN);
  }

  if (blocks == 0) {
    matrix.writeDisplay();
    return;
  }

  for (uint8_t i = 0; i <= blocks; i++) {
    matrix.drawPixel(i, pot_id + 1, LED_RED);
  }

  matrix.writeDisplay();
}

void display_begin() {
  matrix.clear();
  matrix.drawPixel(0, 0, LED_GREEN);
  matrix.drawPixel(0, 7, LED_GREEN);
  matrix.drawPixel(7, 0, LED_GREEN);
  matrix.drawPixel(7, 7, LED_GREEN);

  for (uint8_t i = 1; i <=6; i++) {
    matrix.drawPixel(i, 0, LED_YELLOW);
    matrix.drawPixel(i, 7, LED_YELLOW);

  }

  for (uint8_t i = 0; i < NUMBER_OF_BUTTONS; i++) {
    update_button_display(buttons[i]);
  }

  for (uint8_t i = 0; i < NUMBER_OF_SWITCHES; i++) {
    update_switch_display(switches[i]);
  }

  matrix.writeDisplay();
}

void toggle_mode_if_commanded() {

  const bool is_stick_mode = bossy.savedState(LEFT_SWITCH_UPPER) == LEFT;
  bool toggled = false;

  if (is_stick_mode && mode != STICKMODE) {
    toggled = true;
    mode = STICKMODE;
  }

  if (!is_stick_mode && mode == STICKMODE) {
    toggled = true;
    mode = POTMODE;
  }

  if (toggled) {

    matrix.setTextWrap(false);
    matrix.setTextSize(1);
    matrix.setTextColor(LED_RED);

    for (uint8_t i = 0; i < 4; i++) {
      matrix.clear();
      matrix.setCursor(1, 0);
      mode == STICKMODE ? matrix.print("1") : matrix.print("2");
      matrix.writeDisplay();
      delay(100);
      matrix.clear();
      matrix.writeDisplay();
      delay(100);
    }

    matrix.clear();
    display_begin();
  }

  if (mode == POTMODE) {
    for (uint8_t i = 1; i < NUMBER_OF_POTENTIOMETERS; i++) {
      update_pot_display(i, potentiometers[i]);
    }
  }

  if (mode == STICKMODE) {
    for (uint8_t i = 0; i < NUMBER_OF_STICKS; i++) {
      update_stick_display(sticks[i]);
    }
  }
}
