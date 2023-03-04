#include <Arduino.h>
#include "LightSource.h"

LightSource::LightSource()
{
    trig_pin = new unsigned char[1];
    led_pin = new unsigned char[1];
}

void LightSource::update()
{
    // if rising add +1 brightness
    if (state == 1)
    {
        // if at full brightness change from rising to static
        if (brightness == brightness_max)
        {
            state = 0;
        }
        else
        {
            brightness++;
        }
        for (int i = 0; i < sizeof(led_pin) / sizeof(unsigned char); i++)
        {
            analogWrite(led_pin[i], brightness);
        }
    }

    // if falling add -1 brightness
    if (state == 2)
    {
        // if at lowest brightness change from falling to static
        if (brightness == 0)
        {
            state = 0;
            duration_mult = 0;
        }
        else
        {
            brightness--;
        }
        for (int i = 0; i < sizeof(led_pin) / sizeof(unsigned char); i++)
        {
            analogWrite(led_pin[i], brightness);
        }
    }

    // if at full brightness and static
    if (brightness == brightness_max and state == 0)
    {
        if (duration == duration_max + duration_mult * 20)
        {
            duration = 0;
            state = 2;
        }
        else
        {
            duration++;
        }
    }
}

void LightSource::sense()
{
    if (en)
    {
        for (int i; i < sizeof(trig_pin) / sizeof(unsigned char); i++)
        {
            if (digitalRead(trig_pin[i]))
            {
                state = 1;
                duration = 0;
                if (duration_mult < duration_mult_max)
                {
                    duration_mult_max++;
                }
                break;
            }
        }
    }
}

void LightSource::enable(bool e)
{
    en = e;
    if (!en)
    {
        state = 2;
        duration = 0;
    }
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
bool LightSource::getEnable()
{
    return en;
}

// setters

void LightSource::setBrightnessMax(unsigned char bm)
{
    brightness_max = bm;
}
void LightSource::setDurationMax(int dm)
{
    duration_max = dm;
}

void LightSource::setDurationMultMax(int dmpm)
{
    duration_mult = dmpm;
}
