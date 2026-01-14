#include <cmath>
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include "pros/misc.hpp"

float mmToIn2(float mm) {
    return mm / 25.4;
}

void lemlib::Chassis::moveUntilDistance(float exitDist, float x, float y, float timeout, MoveToPointParams params) {
    this->moveToPoint(x, y, timeout, params, true); 

    while(mmToIn2(this->distSensors.front.distance.get()) > exitDist && this->isInMotion()) {
        pros::delay(10);
    }

    this->endMotion();
}