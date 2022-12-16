#ifndef _nOmuni_HEAD_
#define _nOmuni_HEAD_

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <math.h>

class nOmuni {
    public:
        nOmuni(double position);
        void RePosition(double position);
        double OmuniPower(int x, int y);
    private:
        double xPower;
        double yPower;
};

#endif