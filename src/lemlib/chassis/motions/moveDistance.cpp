#include <cmath>
#include "lemlib/chassis/chassis.hpp"

void lemlib::Chassis::moveDistance(float dist, int timeout, MoveToPointParams params, bool async) {
    //find current pose
    Pose current = getPose(true);

    //calcuate target position
    float x = current.x + (dist * sin(current.theta));
    float y = current.y + (dist * cos(current.theta));

    this->moveToPoint(x, y, timeout, params, async);
}