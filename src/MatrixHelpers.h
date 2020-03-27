#ifndef MatrixHelpers_h
#define MatrixHelpers_h

#include "BossyConstants.h"

/**********************
  LED MATRIX DISPLAY HELPERS
*************************/
// these structs are used for displaying state changes in the led matrix
// the pixels are the locations in the matrix that would change
// depending on the state of the joystick
#define Xi 0
#define Yi 1

#define NUMBER_OF_STICKS 8

struct Stick {
  uint8_t id;
  uint8_t first_pixel[2];
  uint8_t second_pixel[2];
};

const struct Stick jxupleft = {LEFT_JOYSTICK_UPPER_X, {1, 2}, {3, 2}};
const struct Stick jyupleft = {LEFT_JOYSTICK_UPPER_Y, {2, 3}, {2, 1}};

const struct Stick jxdownleft = {LEFT_JOYSTICK_LOWER_X, {1, 5}, {3, 5}};
const struct Stick jydownleft = {LEFT_JOYSTICK_LOWER_Y, {2, 6}, {2, 4}};

const struct Stick jxupright = {RIGHT_JOYSTICK_UPPER_X, {4, 2}, {6, 2}};
const struct Stick jyupright = {RIGHT_JOYSTICK_UPPER_Y, {5, 3}, {5, 1}};

const struct Stick jxdownright = {RIGHT_JOYSTICK_LOWER_X, {4, 5}, {6, 5}};
const struct Stick jydownright = {RIGHT_JOYSTICK_LOWER_Y, {5, 6}, {5, 4}};

const struct Stick sticks[NUMBER_OF_STICKS] = {
  jxupleft,
  jyupleft,
  jxdownleft,
  jydownleft,

  jxupright,
  jyupright,
  jxdownright,
  jydownright
};


#define NUMBER_OF_BUTTONS 8

struct Button {
  uint8_t id;
  uint8_t pixel[2];
};

const struct Button bupleft = {LEFT_BUTTON_UPPER, {0, 0}};
const struct Button bdownleft = {LEFT_BUTTON_LOWER, {0, 7}};
const struct Button bupright = {RIGHT_BUTTON_UPPER, {7 , 0}};
const struct Button bdownright = {RIGHT_BUTTON_LOWER, {7 , 7}};

// joystick buttons
const struct Button jupleft = {LEFT_JOYSTICK_UPPER_BUTTON, {2 , 2}};
const struct Button jdownleft = {LEFT_JOYSTICK_LOWER_BUTTON, {2 , 5}};
const struct Button jupright = {RIGHT_JOYSTICK_UPPER_BUTTON, {5 , 2}};
const struct Button jdownright = {RIGHT_JOYSTICK_LOWER_BUTTON, {5 , 5}};

const struct Button buttons[NUMBER_OF_BUTTONS] = {
  bupleft,
  bdownleft,
  bupright,
  bdownright,

  jupleft,
  jdownleft,
  jupright,
  jdownright,
};

#define NUMBER_OF_SWITCHES 4

struct SwitchSPDT {
  uint8_t id;
  uint8_t first_pixel[2];
  uint8_t second_pixel[2];
  uint8_t third_pixel[2];
};

const struct SwitchSPDT swupleft {LEFT_SWITCH_UPPER, {1, 0}, {2, 0}, {3, 0}};
const struct SwitchSPDT swdownleft {LEFT_SWITCH_LOWER, {1, 7}, {2, 7}, {3, 7}};
const struct SwitchSPDT swupright {RIGHT_SWITCH_UPPER, {4, 0}, {5, 0}, {6, 0}};
const struct SwitchSPDT swdownright {RIGHT_SWITCH_LOWER, {4, 7}, {5, 7}, {6, 7}};

const struct SwitchSPDT switches[NUMBER_OF_SWITCHES] = {swupleft, swdownleft, swupright, swdownright};

#define NUMBER_OF_POTENTIOMETERS 5
const uint8_t potentiometers[NUMBER_OF_POTENTIOMETERS] = {POT_LEFT, POT_LEFT_CENTER, POT_CENTER, POT_RIGHT_CENTER, POT_RIGHT};

#endif
