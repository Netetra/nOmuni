#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

class nOmuni {
    public:
        nOmuni(double position);
        void RePosition(double position);
        double OmuniPower(double radian, uint_t power);
    private:
        double position;
};