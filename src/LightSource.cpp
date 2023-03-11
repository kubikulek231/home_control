#include <Arduino.h>
#include "LightSource.h"

LightSource::LightSource()
{
    // allocate memory dynamically
    trig_pin = new unsigned char[1];
    led_pin = new unsigned char[1];
    trig_pin_size = 1;
    led_pin_size = 1;
}

LightSource::LightSource(unsigned char t, unsigned char p)
{
    trig_pin = new unsigned char[1];
    led_pin = new unsigned char[1];
    trig_pin[0] = t;
    trig_pin[0] = p;
    trig_pin_size = 1;
    led_pin_size = 1;
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
        for (int i = 0; i < led_pin_size; i++)
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
        for (int i = 0; i < led_pin_size; i++)
        {
            analogWrite(led_pin[i], brightness);
        }
    }

    // if at full brightness and static
    if (brightness == brightness_max and state == 0)
    {
        if (duration == duration_max + duration_mult * 3)
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
        for (int i = 0; i < trig_pin_size; i++)
        {
            if (digitalRead(trig_pin[i]) == 1)
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

void LightSource::debug()
{
    Serial.println("----------- debug start -----------");
    Serial.print("trigger pins: ");
    for (int i = 0; i < trig_pin_size; i++)
    {
        Serial.print(trig_pin[i]);
        Serial.print(", ");
    }
    Serial.print(" size: ");
    Serial.print(trig_pin_size);
    Serial.print("\nled pins: ");
    for (int i = 0; i < led_pin_size; i++)
    {
        Serial.print(led_pin[i]);
        Serial.print(", ");
    }
    Serial.print(" size: ");
    Serial.print(led_pin_size);
    Serial.print("\nstate: ");
    Serial.println(state);
    Serial.print("brightness: ");
    Serial.println(brightness);
    Serial.print("brightness_max: ");
    Serial.println(brightness_max);
    Serial.print("duration: ");
    Serial.println(duration);
    Serial.print("duration_max: ");
    Serial.println(duration_max);
    Serial.print("duration_mult: ");
    Serial.println(duration_mult);
    Serial.print("duration_mult_max: ");
    Serial.println(duration_mult_max);
    Serial.print("en: ");
    Serial.println(en);
    Serial.println("------------ debug end ------------");
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
unsigned char LightSource::getPinTrigSize()
{
    return trig_pin_size;
}
unsigned char LightSource::getPinLedSize()
{
    return led_pin_size;
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
    if (bm >= 0) {
        brightness_max = bm;
    }
    
}
void LightSource::setDurationMax(int dm)
{
    if (dm >= 0) {
    duration_max = dm;
    }
}

void LightSource::setDurationMultMax(int dmpm)
{
    if (dmpm >= 0) {
    duration_mult = dmpm;
    }
}
