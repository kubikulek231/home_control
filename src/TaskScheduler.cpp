#include "TaskScheduler.h"

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
    bool trigger(bool s)
    {
        // if disabled
        if (!en)
        {
            return false;
        }
        // if triggered
        if (s)
        {
            if (threshold != threshold_max)
            {
                threshold++;
                return false;
            }
            if (duration != duration_max)
            {
                duration++;
                return false;
            }
            else
            {
                threshold = 0;
                duration = 0;
                return true;
            }
        }
        else
        {
            if (threshold != threshold_max)
            {
                threshold--;
                return false;
            }
        }
    }
    void debug()
    {
    }

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