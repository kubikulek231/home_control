#include "func.h"


void muxSwitch(uint8_t channel){
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << channel);      // send byte to select bus
  Wire.endTransmission();
}