#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"

float mmToIn(float mm) {
    return mm / 25.4;
}

void lemlib::Chassis::distanceReset(int q) {
    const float heading = sanitizeAngle(this->getPose(true).theta, true);
    const float halfWidth = DistanceSensors::width / 2;

    lemlib::Pose pose(0, 0, 0);

    switch(q) {

    case 1: { //quadrant 1

        //handle x and y
        if ((heading > 0 && heading < M_PI_4) || (heading > 3*M_PI_4)) { //angle range 315 to 360 and 0 to 45 deg
            float cos = std::cos(heading); //no transform
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.front.get()));
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.right.get()));
        }

        else if (heading > M_PI_4 && heading < 2*M_PI_4) { //angle range 45 to 135 deg
            float cos = std::cos(heading - M_PI_2); //rotate 90 deg to standard range
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.left.get()));
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.front.get()));
        }

        else if (heading > 2*M_PI_4 && heading < 3*M_PI_4) { //angle range 135 to 225 deg
            float cos = std::cos(heading - M_PI); //rotate 180 deg to standard range
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.back.get()));
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.left.get()));
        }

        else if (heading > 3*M_PI_4 && heading < 4*M_PI_4) { //angle range 225 to 315 deg
            float cos = std::cos(heading - M_PI_2 - M_PI); //rotate 270 deg to standard range
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.right.get()));
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.back.get()));
        }

        pose.theta = radToDeg(heading);

        break;
    }

    default: return; }

    if(pose.x == 0 || pose.y == 0 || pose.theta == 0) { //if anything failed and didn't move off zero, skip reset
        return;
    } else {
        this->setPose(pose); //if successful reset, reset pose
    }

    return;
}