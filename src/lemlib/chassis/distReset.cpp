#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"

void lemlib::Chassis::distanceReset(int q) {
    float heading = sanitizeAngle(this->getPose(true).theta, true);

    switch(q) {

    case 1: { //quadrant 1

        if ((heading > 0 && heading < M_PI_4) || (heading > 3*M_PI_4)) { //angle range 315 to 360 and 0 to 45 deg
        }

        if (heading > M_PI_4 && heading < 2*M_PI_4) { //angle range 45 to 135 deg
        }

        if (heading > 2*M_PI_4 && heading < 3*M_PI_4) { //angle range 135 to 225 deg
        }

        if (heading > 3*M_PI_4 && heading < 4*M_PI_4) { //angle range 225 to 315 deg
        }
    }
    default: return;
    }
}