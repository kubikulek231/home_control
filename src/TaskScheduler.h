#pragma once

#ifndef TASKSCHEDULER_H_
#define TASKSCHEDULER_H_
#include <Arduino.h>

class TaskScheduler
{
private:
    int threshold = 0;
    int threshold_max = 0;
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
    TaskScheduler();

    // methods
    void trigger(bool s);
    void debug();

    // getters
    int getTreshold();
    int getTresholdMax();
    int getDuraion();
    int getDurationMax();
    int getDuraionMult();
    int getDuraionMultMax();
    bool getEnable();

    // setters
    void setTresHoldMax(int tm);
    void setDurationMax(int dm);
    void setDurationMultMax(int dmm);
    void setEnable(bool en);
};

#endif