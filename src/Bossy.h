#ifndef Bossy_h
#define Bossy_h

#include "Arduino.h"
#include "BossyConstants.h"
#include "MatrixHelpers.h"

/**********************
  BOSSY CONTROLLER CLASS
*************************/
class Bossy {
public:
  Bossy(void);
  // these three function are READ-ONLY
  // reads the last saved readings & states
  // does NOT update or read new signals
  uint16_t savedReading(const uint8_t input_id);
  uint16_t savedState(const uint8_t input_id);
  uint8_t savedReadingLowRes(const uint8_t input_id);

  // these four functions has WRITE access
  // updates readings & states
  uint16_t readValue(const uint8_t input_id);
  uint8_t readState(const uint8_t input_id);
  bool hasChangedState(const uint8_t input_id);
  bool hasChangedReading(const uint8_t input_id);

private:
  uint16_t _readings[NUMBER_OF_CHANNELS];
  uint8_t _states[NUMBER_OF_CHANNELS];
  void _update(const uint8_t input_id);
  void _updateReading(const uint8_t input_id);
  void _updateState(const uint8_t input_id);
  void _enableRightMux(void);
  void _enableLeftMux(void);
  uint16_t _readMux(const uint8_t channel);
  uint8_t _constrain(const uint8_t input_id);
  void _saveDebouncedReading(const uint8_t input_id);
  bool _isButton(const uint8_t input_id);
  bool _isBrokenButton(const uint8_t input_id);
  void _updateBrokenButton(const uint8_t input_id);
};

#endif
