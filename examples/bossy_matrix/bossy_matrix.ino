#include <Bossy.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// IMPORTANT! Use upperleft switch to toggle between joystick mode and potentiometer mode

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
}

void loop() {

  for (uint8_t i = 0; i < NUMBER_OF_BUTTONS; i++) {
    if (bossy.hasChangedState(buttons[i].id)) {
      update_button_display(buttons[i]);
    }
  }

  for (uint8_t i = 0; i < NUMBER_OF_SWITCHES; i++) {
    if (bossy.hasChangedState(switches[i].id)) {
      update_switch_display(switches[i]);
    }
  }

  for (uint8_t i = 0; i < NUMBER_OF_STICKS; i++) {
    if (bossy.hasChangedState(sticks[i].id)) {
      if ( mode == STICKMODE) {
        update_stick_display(sticks[i]);
      }
    }
  }

  for (uint8_t i = 0; i < NUMBER_OF_POTENTIOMETERS; i++) {
    if (bossy.hasChangedState(potentiometers[i])) {
      if (mode == POTMODE) {
        update_pot_display(i, potentiometers[i]);
      }
    }
  }

  toggle_mode_if_commanded();
  matrix.writeDisplay();
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

  for (int i=1; i <=6; i++) {
    matrix.drawPixel(i, 0, LED_YELLOW);
    matrix.drawPixel(i, 7, LED_YELLOW);

  }

  for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
    update_button_display(buttons[i]);
  }

  for (int i = 0; i < NUMBER_OF_SWITCHES; i++) {
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
