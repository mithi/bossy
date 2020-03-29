#ifndef MatrixHelpers_h
#define MatrixHelpers_h

#include "BossyConstants.h"

namespace BossyMatrixHelpers {

  /**********************
    LED MATRIX DISPLAY HELPERS
  *************************/
  // these structs are used for displaying state changes in the led matrix
  // the pixels are the locations in the matrix that would change
  // depending on the state of the joystick

  const bool Xi = 0;
  const bool Yi = 1;

  /*****************************
  * X and Y axis of joysticks
  ******************************/
  struct Stick {
    uint8_t id;
    uint8_t first_pixel[2];
    uint8_t second_pixel[2];
  };

  const struct Stick jxupleft = {BossyConstants::LEFT_JOYSTICK_UPPER_X, {1, 2}, {3, 2}};
  const struct Stick jyupleft = {BossyConstants::LEFT_JOYSTICK_UPPER_Y, {2, 3}, {2, 1}};

  const struct Stick jxdownleft = {BossyConstants::LEFT_JOYSTICK_LOWER_X, {1, 5}, {3, 5}};
  const struct Stick jydownleft = {BossyConstants::LEFT_JOYSTICK_LOWER_Y, {2, 6}, {2, 4}};

  const struct Stick jxupright = {BossyConstants::RIGHT_JOYSTICK_UPPER_X, {4, 2}, {6, 2}};
  const struct Stick jyupright = {BossyConstants::RIGHT_JOYSTICK_UPPER_Y, {5, 3}, {5, 1}};

  const struct Stick jxdownright = {BossyConstants::RIGHT_JOYSTICK_LOWER_X, {4, 5}, {6, 5}};
  const struct Stick jydownright = {BossyConstants::RIGHT_JOYSTICK_LOWER_Y, {5, 6}, {5, 4}};

  const struct Stick sticks[BossyConstants::NUMBER_OF_STICKS] = {
    jxupleft,
    jyupleft,
    jxdownleft,
    jydownleft,

    jxupright,
    jyupright,
    jxdownright,
    jydownright
  };

  /*****************************
  * Buttons
  ******************************/
  struct Button {
    uint8_t id;
    uint8_t pixel[2];
  };

  const struct Button bupleft = {BossyConstants::LEFT_BUTTON_UPPER, {0, 0}};
  const struct Button bdownleft = {BossyConstants::LEFT_BUTTON_LOWER, {0, 7}};
  const struct Button bupright = {BossyConstants::RIGHT_BUTTON_UPPER, {7 , 0}};
  const struct Button bdownright = {BossyConstants::RIGHT_BUTTON_LOWER, {7 , 7}};

  // joystick buttons
  const struct Button jupleft = {BossyConstants::LEFT_JOYSTICK_UPPER_BUTTON, {2 , 2}};
  const struct Button jdownleft = {BossyConstants::LEFT_JOYSTICK_LOWER_BUTTON, {2 , 5}};
  const struct Button jupright = {BossyConstants::RIGHT_JOYSTICK_UPPER_BUTTON, {5 , 2}};
  const struct Button jdownright = {BossyConstants::RIGHT_JOYSTICK_LOWER_BUTTON, {5 , 5}};

  const struct Button buttons[BossyConstants::NUMBER_OF_BUTTONS] = {
    bupleft,
    bdownleft,
    bupright,
    bdownright,

    jupleft,
    jdownleft,
    jupright,
    jdownright,
  };

  /*****************************
  * Switches
  ******************************/
  struct SwitchSPDT {
    uint8_t id;
    uint8_t first_pixel[2];
    uint8_t second_pixel[2];
    uint8_t third_pixel[2];
  };

  const struct SwitchSPDT swupleft {BossyConstants::LEFT_SWITCH_UPPER, {1, 0}, {2, 0}, {3, 0}};
  const struct SwitchSPDT swdownleft {BossyConstants::LEFT_SWITCH_LOWER, {1, 7}, {2, 7}, {3, 7}};
  const struct SwitchSPDT swupright {BossyConstants::RIGHT_SWITCH_UPPER, {4, 0}, {5, 0}, {6, 0}};
  const struct SwitchSPDT swdownright {BossyConstants::RIGHT_SWITCH_LOWER, {4, 7}, {5, 7}, {6, 7}};

  const struct SwitchSPDT switches[BossyConstants::NUMBER_OF_SWITCHES] = {swupleft, swdownleft, swupright, swdownright};

  /*****************************
  * Potentiometers
  ******************************/
  const uint8_t potentiometers[BossyConstants::NUMBER_OF_POTENTIOMETERS] = {
    BossyConstants::POT_LEFT,
    BossyConstants::POT_LEFT_CENTER,
    BossyConstants::POT_CENTER,
    BossyConstants::POT_RIGHT_CENTER,
    BossyConstants::POT_RIGHT
  };
}

#endif
