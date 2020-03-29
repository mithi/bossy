#ifndef BossyInputSets_h
#define BossyInputSets_h

#include "BossyConstants.h"

namespace BossyInputSets {

  const uint8_t stick_ids[BossyConstants::NUMBER_OF_STICKS] = {
    BossyConstants::LEFT_JOYSTICK_UPPER_X,
    BossyConstants::LEFT_JOYSTICK_UPPER_Y,
    BossyConstants::LEFT_JOYSTICK_LOWER_X,
    BossyConstants::LEFT_JOYSTICK_LOWER_Y,

    BossyConstants::RIGHT_JOYSTICK_UPPER_X,
    BossyConstants::RIGHT_JOYSTICK_UPPER_Y,
    BossyConstants::RIGHT_JOYSTICK_LOWER_X,
    BossyConstants::RIGHT_JOYSTICK_LOWER_Y
  };

  /*****************************
  * Buttons
  ******************************/
  const uint8_t button_ids[BossyConstants::NUMBER_OF_BUTTONS] = {
    BossyConstants::LEFT_BUTTON_UPPER,
    BossyConstants::LEFT_BUTTON_LOWER,
    BossyConstants::RIGHT_BUTTON_UPPER,
    BossyConstants::RIGHT_BUTTON_LOWER,

    BossyConstants::LEFT_JOYSTICK_UPPER_BUTTON,
    BossyConstants::LEFT_JOYSTICK_LOWER_BUTTON,
    BossyConstants::RIGHT_JOYSTICK_UPPER_BUTTON,
    BossyConstants::RIGHT_JOYSTICK_LOWER_BUTTON
  };

  /*****************************
  * Switches
  ******************************/
  const uint8_t switch_ids[BossyConstants::NUMBER_OF_SWITCHES] = {
    BossyConstants::LEFT_SWITCH_UPPER,
    BossyConstants::LEFT_SWITCH_LOWER,
    BossyConstants::RIGHT_SWITCH_UPPER,
    BossyConstants::RIGHT_SWITCH_LOWER
  };

  /*****************************
  * Potentiometers
  ******************************/
  const uint8_t potentiometer_ids[BossyConstants::NUMBER_OF_POTENTIOMETERS] = {
    BossyConstants::POT_LEFT,
    BossyConstants::POT_LEFT_CENTER,
    BossyConstants::POT_CENTER,
    BossyConstants::POT_RIGHT_CENTER,
    BossyConstants::POT_RIGHT
  };
}

#endif
