#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"

float mmToIn(float mm) {
    return mm / 25.4;
}

void lemlib::Chassis::distanceReset(pros::Distance xSensor, pros::Distance ySensor, float xOffset, float yOffset) {
    const float refAngle = lemlib::refAngle(true, this->getPose(true).theta);

    lemlib::Pose currentPose = this->getPose(true);
    lemlib::Pose pose(0, 0);

    // x reset
    // 
    if(currentPose.x > 0) {
        pose.x = lemlib::halfWidth - (cos(refAngle) * (mmToIn(xSensor.get()) + xOffset));
    }
}

/*
void lemlib::Chassis::distanceReset(int q) {
    const float heading = sanitizeAngle(this->getPose(true).theta, true);
    const float halfWidth = DistanceSensors::width / 2;

    lemlib::Pose pose(0, 0, 0);

    switch(q) {

    case 1: { //quadrant 1

        //handle x and y
        if ((heading > 0 && heading < M_PI_4) || (heading > 7*M_PI_4)) { //angle range 315 to 360 and 0 to 45 deg
            float cos = std::cos(heading); //no transform
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.front.get()));
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.right.get()));
        }

        else if (heading > M_PI_4 && heading < 3*M_PI_4) { //angle range 45 to 135 deg
            float cos = std::cos(heading - M_PI_2); //rotate 90 deg to standard range
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.left.get()));
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.front.get()));
        }

        else if (heading > 3*M_PI_4 && heading < 5*M_PI_4) { //angle range 135 to 225 deg
            float cos = std::cos(heading - M_PI); //rotate 180 deg to standard range
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.back.get()));
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.left.get()));
        }

        else if (heading > 5*M_PI_4 && heading < 7*M_PI_4) { //angle range 225 to 315 deg
            float cos = std::cos(heading - M_PI_2 - M_PI); //rotate 270 deg to standard range
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.right.get()));
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.back.get()));
        }

        pose.theta = radToDeg(heading);
        break;
    }

    case 2: { //quadrant 2
        if ((heading > 0 && heading < M_PI_4) || (heading > 7*M_PI_4)) {
            float cos = std::cos(heading - M_PI_2);
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.left.get()) + this->distanceSensors.leftOffset);
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.back.get()) + this->distanceSensors.backOffset);
        }

        else if (heading > 3*M_PI_4 && heading < 5*M_PI_4) { 
            float cos = std::cos(heading - M_PI); 
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.back.get())+  this->distanceSensors.backOffset);
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.left.get())+  this->distanceSensors.leftOffset);
        }

        else if (heading > 5*M_PI_4 && heading < 7*M_PI_4) { 
            float cos = std::cos(heading - (3*M_PI_2));
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.right.get())+  this->distanceSensors.rightOffset);
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.back.get())+  this->distanceSensors.backOffset);
        }

        else if (heading > 7*M_PI_4 && heading < 2*M_PI) {
            float cos = std::cos(heading);
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.front.get())+  this->distanceSensors.frontOffset);
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.right.get()) + this->distanceSensors.rightOffset);
        }

        pose.theta = radToDeg(heading);
        break;
    }

    case 3: { //quadrant 3

        if ((heading > 0 && heading < M_PI_4) || (heading > 3*M_PI_4)) {
            float cos = std::cos(heading);
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.back.get()) + this->distanceSensors.backOffset);
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.left.get()) + this->distanceSensors.leftOffset);
        }
        else if (heading > M_PI_4 && heading < 2*M_PI_4) {
            float cos = std::cos(heading - M_PI_2);
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.right.get()) + this->distanceSensors.rightOffset);
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.back.get()) + this->distanceSensors.backOffset);
        }
        else if (heading > 2*M_PI_4 && heading < 3*M_PI_4) {
            float cos = std::cos(heading - M_PI);
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.front.get()) + this->distanceSensors.leftOffset);
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.right.get()) + this->distanceSensors.rightOffset);
        }
        else if (heading > 3*M_PI_4 && heading < M_PI) {
            float cos = std::cos(heading - (3*M_PI_2));
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.left.get()) + this->distanceSensors.leftOffset);
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.front.get()) + this->distanceSensors.frontOffset); 
        }
        }

    case 4: { //quadrant 4

        // slice 1 (0–45° and 315–360°)
        if ((heading > 0 && heading < M_PI_4) || (heading > 3*M_PI_4)) {
            float cos = std::cos(heading);
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.right.get())+ this->distanceSensors.rightOffset); 
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.front.get())+ this->distanceSensors.frontOffset);
        }

        // slice 2 (45–135°)
        else if (heading > M_PI_4 && heading < 2*M_PI_4) {
            float cos = std::cos(heading - M_PI_2);
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.back.get()) + this->distanceSensors.backOffset);
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.right.get())+ this->distanceSensors.rightOffset); 
        }

        // slice 3 (135–225°)
        else if (heading > 2*M_PI_4 && heading < 3*M_PI_4) {
            float cos = std::cos(heading - M_PI);
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.left.get())+ this->distanceSensors.leftOffset);
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.back.get()) + this->distanceSensors.backOffset); 
        }

        // slice 4 (225–315°)
        else if (heading > 3*M_PI_4 && heading < 4*M_PI_4) {
            float cos = std::cos(heading - (M_PI + M_PI_2));
            pose.y = halfWidth - (cos * mmToIn(this->distanceSensors.front.get())+ this->distanceSensors.frontOffset);
            pose.x = halfWidth - (cos * mmToIn(this->distanceSensors.left.get())+ this->distanceSensors.leftOffset); 
        }

        pose.theta = radToDeg(heading);
        break;

    default: return; 
    }

    if(pose.x == 0 || pose.y == 0 || pose.theta == 0) { //if anything failed and didn't move off zero, skip reset
        return;
    } else {
        this->setPose(pose); //if successful reset, reset pose
    }

    return;

    }
}
*/