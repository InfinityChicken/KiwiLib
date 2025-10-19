#include <cmath>
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/logger/logger.hpp"
#include "lemlib/timer.hpp"
#include "lemlib/util.hpp"
#include "pros/misc.hpp"

void lemlib::Chassis::moveDistance(float dist, int timeout, MoveToPointParams params, bool async) {
    Pose current = getPose(true);

    float targetX = current.x + (dist * sin(current.theta));
    float targetY = current.y + (dist * cos(current.theta));

    this->moveToPoint(targetX, targetY, timeout, params, async);
}