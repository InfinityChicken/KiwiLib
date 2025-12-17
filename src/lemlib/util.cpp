#include <vector>
#include "lemlib/pose.hpp"
#include "lemlib/util.hpp"

float lemlib::refAngle(bool rad, float angle) {

    angle = sanitizeAngle(angle, rad);

    if(!rad) { //degrees
        if(angle >= 0 && angle <= 90) {
            return angle;
        } else if(angle > 90 && angle <= 180) {
            return 180.0 - angle;
        } else if (angle > 180 && angle <= 270) {
            return angle - 180.0;
        } else if (angle > 270 && angle <= 360) {
            return 360.0 - angle;
        }
    } else {
        if(angle >= 0 && angle <= M_PI_2) {
            return angle;
        } else if(angle > M_PI_2 && angle <= M_PI) {
            return M_PI - angle;
        } else if (angle > M_PI && angle <= 3 * M_PI_2) {
            return angle - M_PI;
        } else if (angle > 3 * M_PI_2 && angle <= 2 * M_PI) {
            return 2 * M_PI_2 - angle;
        }
    }

    return -1;
}

float lemlib::slew(float target, float current, float maxChange) {
    float change = target - current;
    if (maxChange == 0) return target;
    if (change > maxChange) change = maxChange;
    else if (change < -maxChange) change = -maxChange;
    return current + change;
}

float lemlib::sanitizeAngle(float angle, bool radians) {
    if (radians) return std::fmod(std::fmod(angle, 2 * M_PI) + 2 * M_PI, 2 * M_PI);
    else return std::fmod(std::fmod(angle, 360) + 360, 360);
}

float lemlib::angleError(float target, float position, bool radians, AngularDirection direction) {
    // bound angles from 0 to 2pi or 0 to 360
    target = sanitizeAngle(target, radians);
    position = sanitizeAngle(position, radians);
    const float max = radians ? 2 * M_PI : 360;
    const float rawError = target - position;
    switch (direction) {
        case AngularDirection::CW_CLOCKWISE: // turn clockwise
            return rawError < 0 ? rawError + max : rawError; // add max if sign does not match
        case AngularDirection::CCW_COUNTERCLOCKWISE: // turn counter-clockwise
            return rawError > 0 ? rawError - max : rawError; // subtract max if sign does not match
        default: // choose the shortest path
            return std::remainder(rawError, max);
    }
}

float lemlib::avg(std::vector<float> values) {
    float sum = 0;
    for (float value : values) { sum += value; }
    return sum / values.size();
}

float lemlib::ema(float current, float previous, float smooth) {
    return (current * smooth) + (previous * (1 - smooth));
}

float lemlib::getCurvature(Pose pose, Pose other) {
    // calculate whether the pose is on the left or right side of the circle
    float side = lemlib::sgn(std::sin(pose.theta) * (other.x - pose.x) - std::cos(pose.theta) * (other.y - pose.y));
    // calculate center point and radius
    float a = -std::tan(pose.theta);
    float c = std::tan(pose.theta) * pose.x - pose.y;
    float x = std::fabs(a * other.x + other.y + c) / std::sqrt((a * a) + 1);
    float d = std::hypot(other.x - pose.x, other.y - pose.y);

    // return curvature
    return side * ((2 * x) / (d * d));
}
