
#pragma once

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_

class LightSource
{
private:

    unsigned char * trig_pin = 0;
    unsigned char * led_pin = 0;
    unsigned char state = 0;
    unsigned char brightness = 0;
    unsigned char brightness_max = 255;
    int duration = 0;
    int duration_max = 2000;
    int duration_mult = 0;
    int duration_mult_max = 40;

public:

    /** 
     * default constructor
     */
    LightSource();

    /** 
     * partial constructor
     * @tparam t array of trigger pins
     * @tparam p array of led pins
     */
    LightSource(unsigned char * t, unsigned char * p);

    // getters
    unsigned char * getPinTrig();
    unsigned char * getPinLed();
    unsigned char getState();
    unsigned char getBrightness();
    unsigned char getBrightnessMax();
    int getDuration();
    int getDurationMax();
    int getDurationMult();
    int getDurationMultMax();
    // setters
    void setPinTrig(unsigned char * t);
    void setPinTrig(unsigned char t);
    void setPinLed(unsigned char * p);
    void setPinLed(unsigned char p);
    void setState(unsigned char s);
    void setBrightness(unsigned char b);
    void setBrightnessMax(unsigned char bm);
    void setDuration(int d);
    void setDurationMax(int dm);
    void setDurationMult(int dmp);
    void setDurationMultMax(int dmpm);
};

#endif
