#include "func.h"

void lightUpdate(LightSource lsObj) {
  

    // if rising add +1 brightness
    if (lsObj.getState() == 1)
    {
      // if at full brightness change from rising to static
      if (lsObj.getBrightness() == lsObj.getBrightnessMax())
      {
        lsObj.setState(0);
      }
      else
      {
        lsObj.setBrightness(lsObj.getBrightness() + 1);
      }
      // todo: for
      //analogWrite(lsObj.getPinLed(), lsObj.getBrightness());
    }

    // if falling add -1 brightness
    if (lsObj.getState() == 2)
    {
      // if at lowest brightness change from falling to static
      if (lsObj.getBrightness() == 0)
      {
        lsObj.setState(0);
        lsObj.setDurationMult(0);
      }
      else
      {
        lsObj.setBrightness(lsObj.getBrightness() - 1);
      }
      //analogWrite(lsObj.getPinLed(), lsObj.getBrightness());
    }

    // if at full brightness and static
    if (lsObj.getBrightness() == lsObj.getBrightnessMax() and lsObj.getState() == 0)
    {
      if (lsObj.getDuration() == lsObj.getDurationMax() + lsObj.getDurationMult() * 20)
      {
        lsObj.setDuration(0);
        lsObj.setState(2);
      }
      else
      {
        lsObj.setDuration(lsObj.getDuration() + 1);
      }
    }
}