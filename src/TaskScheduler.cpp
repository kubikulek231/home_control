#include "TaskScheduler.h"

bool TaskScheduler::trigger(bool is_triggered)
{
    if (!en)
    {
        threshold = 0;
        duration = 0;
        duration_mult = 0;
        return false;
    }

    if (is_triggered)
    {
        if (threshold != threshold_max)
        {
            threshold++;
            return false;
        }
        duration_mult++;
        duration = 0;
        return true;
    }
    else
    {
        if ((duration != duration_max + duration_mult * 3) and (threshold == threshold_max))
        {
            duration++;
            return true;
        }
        else
        {
            threshold = 0;
            duration = 0;
            duration_mult = 0;
            return false;
        }
    }
}

void TaskScheduler::debug()
{
    Serial.println("----------- debug start -----------");
    Serial.print("threshold: ");
    Serial.println(threshold);
    Serial.print("threshold_max: ");
    Serial.println(threshold_max);
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

void TaskScheduler::enable(bool e)
{
    en = e;
}

// getters
int TaskScheduler::getTreshold()
{
    return threshold;
}
int TaskScheduler::getTresholdMax()
{
    return threshold_max;
}
int TaskScheduler::getDuraion()
{
    return duration;
}
int TaskScheduler::getDurationMax()
{
    return duration_max;
}
int TaskScheduler::getDuraionMult()
{
    return duration_mult;
}
int TaskScheduler::getDuraionMultMax()
{
    return duration_mult_max;
}
bool TaskScheduler::getEnable()
{
    return en;
}

// setters
void TaskScheduler::setTresHoldMax(int tm)
{
    if (tm >= 0)
    {
        threshold_max = tm;
    }
}

void TaskScheduler::setDurationMax(int dm)
{
    if (dm >= 0)
    {
        duration_max = dm;
    }
}

void TaskScheduler::setDurationMultMax(int dmm)
{
    if (dmm >= 0)
    {
        threshold_max = dmm;
    }
}