#ifndef BossyConstants_h
#define BossyConstants_h

/**********************
  MULTIPLEXER PINS
*************************/
#define PIN_ENABLE_LEFT_MUX 11
#define PIN_ENABLE_RIGHT_MUX 12

#define s0 5
#define s1 6
#define s2 7
#define s3 8
#define PIN_SIGNAL A1

/**********************
 CHANNELS
*************************/
#define NUMBER_OF_CHANNELS 25

// map of input id to channel in the multiplexer
const uint8_t INPUT_CHANNEL[NUMBER_OF_CHANNELS] = {

  11, // LEFT_SWITCH_UPPER
  10, // LEFT_SWITCH_LOWER

   8, // LEFT_JOYSTICK_UPPER_Y
   7, // LEFT_JOYSTICK_UPPER_X
   9, // LEFT_JOYSTICK_UPPER_BUTTON

   5, // LEFT_JOYSTICK_LOWER_Y
   6, // LEFT_JOYSTICK_LOWER_X
   4, // LEFT_JOYSTICK_LOWER_BUTTON

   0, // LEFT_BUTTON_UPPER
   3, // LEFT_BUTTON_LOWER

  14, // POT_LEFT
  12, // POT_LEFT_CENTER
  13, // POT_CENTER

  4, // RIGHT_SWITCH_UPPER
  5, // RIGHT_SWITCH_LOWER

  7, // RIGHT_JOYSTICK_UPPER_Y
  6, // RIGHT_JOYSTICK_UPPER_X
  8, // RIGHT_JOYSTICK_UPPER_BUTTON

  11, // RIGHT_JOYSTICK_LOWER_Y
  9, // RIGHT_JOYSTICK_LOWER_X
  10, // RIGHT_JOYSTICK_LOWER_BUTTON

  13, // RIGHT_BUTTON_UPPER
  12, // RIGHT_BUTTON_LOWER

   3, // POT_RIGHT_CENTER
   2  // POT_RIGHT
};

/**********************
 INPUT TYPE (normal or inverted)
*************************/
// The input type is normal when:
// button: pressed is HIGH
// joystick y axis: UP is HIGH
// joystick x axis: RIGHT is HIGH
// switch: RIGHT is HIGH
// it is inverted if otherwise
#define NORMAL true
#define INVERTED false

// map of input id to its input type (
const bool INPUT_TYPE[NUMBER_OF_CHANNELS] = {
  NORMAL, // LEFT_SWITCH_UPPER
  NORMAL, // LEFT_SWITCH_LOWER

  INVERTED, // LEFT_JOYSTICK_UPPER_Y
  INVERTED, // LEFT_JOYSTICK_UPPER_X
  INVERTED, // LEFT_JOYSTICK_UPPER_BUTTON

  INVERTED, // LEFT_JOYSTICK_LOWER_Y
  INVERTED, // LEFT_JOYSTICK_LOWER_X
  INVERTED, // LEFT_JOYSTICK_LOWER_BUTTON

  INVERTED, // LEFT_BUTTON_UPPER
  INVERTED, // LEFT_BUTTON_LOWER

  NORMAL, // POT_LEFT
  NORMAL, // POT_LEFT_CENTER
  NORMAL, // POT_CENTER

  INVERTED, // RIGHT_SWITCH_UPPER
  INVERTED, // RIGHT_SWITCH_LOWER

  NORMAL, // RIGHT_JOYSTICK_UPPER_Y
  NORMAL, // RIGHT_JOYSTICK_UPPER_X
  INVERTED, // RIGHT_JOYSTICK_UPPER_BUTTON

  NORMAL, // RIGHT_JOYSTICK_LOWER_Y
  NORMAL, // RIGHT_JOYSTICK_LOWER_X
  INVERTED, // RIGHT_JOYSTICK_LOWER_BUTTON

  NORMAL, // RIGHT_BUTTON_UPPER
  NORMAL, // RIGHT_BUTTON_LOWER

  NORMAL, // POT_RIGHT_CENTER
  NORMAL // POT_RIGHT
};


/**********************
 INPUT IDs
*************************/

// left inputs

#define LEFT_SWITCH_UPPER 0
#define LEFT_SWITCH_LOWER 1

#define LEFT_JOYSTICK_UPPER_Y 2
#define LEFT_JOYSTICK_UPPER_X 3
#define LEFT_JOYSTICK_UPPER_BUTTON 4

#define LEFT_JOYSTICK_LOWER_Y 5
#define LEFT_JOYSTICK_LOWER_X 6
#define LEFT_JOYSTICK_LOWER_BUTTON 7

#define LEFT_BUTTON_UPPER 8
#define LEFT_BUTTON_LOWER 9

#define POT_LEFT 10
#define POT_LEFT_CENTER 11
#define POT_CENTER 12

// right inputs

#define RIGHT_SWITCH_UPPER 13
#define RIGHT_SWITCH_LOWER 14

#define RIGHT_JOYSTICK_UPPER_Y 15
#define RIGHT_JOYSTICK_UPPER_X 16
#define RIGHT_JOYSTICK_UPPER_BUTTON 17

#define RIGHT_JOYSTICK_LOWER_Y 18
#define RIGHT_JOYSTICK_LOWER_X 19
#define RIGHT_JOYSTICK_LOWER_BUTTON 20

#define RIGHT_BUTTON_UPPER 21
#define RIGHT_BUTTON_LOWER 22

#define POT_RIGHT_CENTER 23
#define POT_RIGHT 24

/**********************
 MAP input id to multiplexer id (left or right)
*************************/

// the ids for the left multiplexer is 0 to 12
// the ids for the right multiplexer is 13 to 24
#define MUX_LEFT_MIN 0
#define MUX_LEFT_MAX 12

#define MULTIPLEXER_RIGHT_MIN 13
#define MULTIPLEXER_RIGHT_MAX 24

/**********************
  AGGREGATED BUTTONS
*************************/

#define NUMBER_OF_BOOLEAN_INPUTS 8

// which channels are boolean inputs/ie buttons
const uint8_t BOOLEAN_INPUTS[NUMBER_OF_BOOLEAN_INPUTS] = {
  LEFT_BUTTON_LOWER,
  LEFT_BUTTON_UPPER,
  LEFT_JOYSTICK_LOWER_BUTTON,
  LEFT_JOYSTICK_UPPER_BUTTON,
  RIGHT_BUTTON_LOWER,
  RIGHT_BUTTON_UPPER,
  RIGHT_JOYSTICK_LOWER_BUTTON,
  RIGHT_JOYSTICK_UPPER_BUTTON
};

// which buttons are not pulled up to 5v
// temporary software hack
const uint8_t BROKEN_BUTTONS[NUMBER_OF_BOOLEAN_INPUTS] = {
  LEFT_JOYSTICK_LOWER_BUTTON,
  LEFT_JOYSTICK_UPPER_BUTTON,
  RIGHT_JOYSTICK_LOWER_BUTTON,
  RIGHT_JOYSTICK_UPPER_BUTTON
};

/**********************
  POSSIBLE STATES
*************************/
/*
The possible states are just
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


// these are the possible states
#define PUSHED 4
#define NOT_PUSHED 0

#define NEUTRAL 2

#define DOWN 0
#define DOWN_CENTER 1
#define UP_CENTER 3
#define UP 4

#define LEFT 0
#define LEFT_CENTER 1
#define RIGHT_CENTER 3
#define RIGHT 4

#define SCALE_0 0
#define SCALE_1 1
#define SCALE_2 2
#define SCALE_3 3
#define SCALE_4 4

#endif
