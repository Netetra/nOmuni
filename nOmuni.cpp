#include "nOmuni.h"
#include <math.h>

nOmuni::nOmuni(double position) {
    reposition(position);
}

void nOmuni::reposition(double position) {
    this->position = position;
}

double nOmuni::rotation(double radian, uint_t power) {
    omuniPower = sin(radian - this->position) * power;
    return omuniPower;
}