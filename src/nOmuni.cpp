#include "nOmuni.h"
#include <math.h>

nOmuni::nOmuni(double position) {
    RePosition(position);
}

void nOmuni::RePosition(double position) {
    this->xPower = cos(position);
    this->yPower = sin(position);
}

double nOmuni::OmuniPower(int x, int y) {
    double omuniPower = this->xPower*x + this->yPower*y;
    return omuniPower;
}