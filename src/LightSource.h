#pragma once

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_


class LightSource
{
private:
    unsigned char *trig_pin = 0;
    unsigned char *led_pin = 0;
    unsigned char state = 0;
    unsigned char brightness = 0;
    unsigned char brightness_max = 255;
    int duration = 0;
    int duration_max = 2000;
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

    // getters
    unsigned char *getPinTrig();
    unsigned char *getPinLed();
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
        int arg_size = sizeof...(t);
        int temp_int_arr[arg_size] = {t...};
        trig_pin = new unsigned char[arg_size];
        for (int i = 0; i < arg_size; i++)
        {
            trig_pin[i] = temp_int_arr[i];
        }
    }

    /**
     * specify led pins
     * @tparam l1, l2 ... any number of led pins
     */
    template <typename... Args>
    void setPinLed(Args... l)
    {
        int arg_size = sizeof...(l);
        int temp_int_arr[arg_size] = {l...};
        led_pin = new unsigned char[arg_size];
        for (int i = 0; i < arg_size; i++)
        {
            led_pin[i] = temp_int_arr[i];
        }
    }

    void setBrightnessMax(unsigned char bm);
    void setDurationMax(int dm);
    void setDurationMultMax(int dmpm);
};

#endif
