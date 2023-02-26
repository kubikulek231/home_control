#include "LightSource.h"

LightSource::LightSource()
{
    trig_pin = new unsigned char[1];
    led_pin = new unsigned char[1];
}

LightSource::LightSource(unsigned char *t, unsigned char *p)
{
    trig_pin = new unsigned char[sizeof(t) / sizeof(unsigned char)];
    led_pin = new unsigned char[sizeof(p) / sizeof(unsigned char)];
}

// getters
unsigned char *LightSource::getPinTrig()
{
    return trig_pin;
}
unsigned char *LightSource::getPinLed()
{
    return led_pin;
}
unsigned char LightSource::getState()
{
    return state;
}
unsigned char LightSource::getBrightness()
{
    return brightness;
}
unsigned char LightSource::getBrightnessMax()
{
    return brightness_max;
}
int LightSource::getDuration()
{
    return duration;
}
int LightSource::getDurationMax()
{
    return duration_max;
}
int LightSource::getDurationMult()
{
    return duration_mult;
}
int LightSource::getDurationMultMax()
{
    return duration_mult_max;
}

// setters
void LightSource::setPinTrig(unsigned char *t)
{
    unsigned char length = sizeof(t) / sizeof(unsigned char);
    trig_pin = new unsigned char[length];
    trig_pin = t;
}
void LightSource::setPinTrig(unsigned char t)
{
    trig_pin = new unsigned char[1];
    trig_pin[0] = t;
}
void LightSource::setPinLed(unsigned char *p)
{
    unsigned char length = sizeof(p) / sizeof(unsigned char);
    led_pin = new unsigned char[length];
    led_pin = p;
}
void LightSource::setPinLed(unsigned char p)
{
    led_pin = new unsigned char[1];
    led_pin[0] = p;
}
void LightSource::setState(unsigned char s)
{
    state = s;
}
void LightSource::setBrightness(unsigned char b)
{
    brightness = b;
}
void LightSource::setBrightnessMax(unsigned char bm)
{
    brightness_max = bm;
}
void LightSource::setDuration(int d)
{
    duration = d;
}
void LightSource::setDurationMax(int dm)
{
    duration_max = dm;
}
void LightSource::setDurationMult(int dmp) {
    duration_mult = dmp;
}
void LightSource::setDurationMultMax(int dmpm) {
    duration_mult = dmpm;
}