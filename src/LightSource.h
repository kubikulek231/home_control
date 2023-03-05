#pragma once

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_
#include <Arduino.h>

class LightSource
{
private:
    unsigned char *trig_pin = 0;
    unsigned char *led_pin = 0;
    unsigned char trig_pin_size = 1;
    unsigned char led_pin_size = 1;
    unsigned char state = 0;
    unsigned char brightness = 0;
    unsigned char brightness_max = 200;
    int duration = 0;
    int duration_max = 1000;
    int duration_mult = 0;
    int duration_mult_max = 40;
    bool en = true;

public:
    // constructors
    /**
     * default constructor
     */
    LightSource();

    /**
     * partial constructor
     * @param t array of trigger pins
     * @param p array of led pins
     */
    LightSource(unsigned char *t, unsigned char *p);

    // methods
    void update();
    void sense();
    void enable(bool e);
    void debug();

    // getters
    unsigned char *getPinTrig();
    unsigned char *getPinLed();
    unsigned char getPinTrigSize();
    unsigned char getPinLedSize();
    unsigned char getState();
    unsigned char getBrightness();
    unsigned char getBrightnessMax();
    int getDuration();
    int getDurationMax();
    int getDurationMult();
    int getDurationMultMax();
    bool getEnable();

    // setters
    /**
     * specify trigger pins
     * @tparam t1, t2 ... any number of trigger pins
     */
    template <typename... Args>
    void setPinTrig(Args... t)
    {   
        // delete dynamically allocated memory
        delete[] trig_pin;
        // get the size of the new array
        trig_pin_size = sizeof...(t);
        // allocate memory for the new array
        trig_pin = new unsigned char[trig_pin_size];
        // create a new - static array to store the args temporarily
        int temp_arr[trig_pin_size] = {t...};
        // put the temp entries to newly created array
        for (int i = 0; i < trig_pin_size; i++)
        {
            trig_pin[i] = temp_arr[i];
        }
    }

    /**
     * specify led pins
     * @tparam l1, l2 ... any number of led pins
     */
    template <typename... Args>
    void setPinLed(Args... l)
    {
        // delete dynamically allocated memory
        delete[] led_pin;
        // get the size of the new array
        led_pin_size = sizeof...(l);
        // allocate memory for the new array
        led_pin = new unsigned char[led_pin_size];
        // create a new - static array to store the args temporarily
        int temp_arr[led_pin_size] = {l...};
        // put the temp entries to newly created array
        for (int i = 0; i < led_pin_size; i++)
        {
            led_pin[i] = temp_arr[i];
        }
    }

    void setBrightnessMax(unsigned char bm);
    void setDurationMax(int dm);
    void setDurationMultMax(int dmpm);
};

#endif
