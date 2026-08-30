#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include <cmath>

void lemlib::Chassis::distanceReset(char xDirection, char yDirection) {
    //treat as lemlib motion so doesnt interfere with motions in progress
    // this->requestMotionStart();

    float rotated = 0;

    //pick active dist sensor for side
    DistResetSensors* xDist = nullptr;
    DistResetSensors* yDist = nullptr;

    //if using front or back as x direction, rotate angle by adding 90 degrees
    if(xDirection == 'F') {
        xDist = &distSensors.front;
        rotated = M_PI_2;
    } else if(xDirection == 'B') {
        xDist = &distSensors.back;
        rotated = M_PI_2;
    } else if(xDirection == 'R') {
        xDist = &distSensors.right;
    } else if(xDirection == 'L') {
        xDist = &distSensors.left;
    }
        
    //if using left or right as y direction, rotate angle by adding 90 degrees
    if(yDirection == 'F') {
        yDist = &distSensors.front;
    } else if(yDirection == 'B') {
        yDist = &distSensors.back;
    } else if(yDirection == 'R') {
        yDist = &distSensors.right;
        rotated = M_PI_2;
    } else if(yDirection == 'L') {
        yDist = &distSensors.left;
        rotated = M_PI_2;
    }

    if(xDist != nullptr && mmToIn(xDist->distance.get())>300) {
        xDist = nullptr;
    }

    if(yDist != nullptr && mmToIn(yDist->distance.get())>300) {
        yDist = nullptr;
    }

    //if both/essential distance sensors are bad, don't reset
    if(xDist == nullptr || yDist == nullptr) {
        this->endMotion();
        return;
    }

    //get current position
    lemlib::Pose currentPose = this->getPose(true);
    //this is going to be the reset pose with theta in degrees
    lemlib::Pose pose(0, 0, this->getPose(false).theta);

    //gets acute angle from axis
    //subtract rotated to either keep same angle or rotate by 90 degrees
    //sanitizes rotated angle (if it ends up being rotated)
    //gets reference angle from x axis (y axis becomes x axis if rotated)
    const float correctedAngle = lemlib::refAngle(true, lemlib::sanitizeAngle(currentPose.theta-rotated, true)); 
    //determine if robot is to the left or right of closest axis (determines if you add or subtract offset distance calculated with tangent term)
    //if to the left, subtract, if to the right, add
    const int offsetMultiplier = (std::sin(currentPose.theta-rotated) >= 0) ? -1 : 1;

    //calculate perpendicular distance from center to perimeter
    //cosine of entire distance from center of bot to perimeter (not perpendicular)
    //entire distance = distance sensor in inches + discrepancy from offset distance sensor + distance from center of bot
    float xPerpDistance = 0;
    float yPerpDistance = 0;
    if(xDist != nullptr)
        xPerpDistance = cos(correctedAngle) * (mmToIn(xDist->distance.get()) + tan(correctedAngle) * xDist->offsetX * offsetMultiplier + xDist->offsetY);
    if(yDist != nullptr)
        yPerpDistance = cos(correctedAngle) * (mmToIn(yDist->distance.get()) + tan(correctedAngle) * yDist->offsetX * offsetMultiplier + yDist->offsetY);

    //x reset
    if(currentPose.x > 0){ //pos
        pose.x = lemlib::halfWidth - xPerpDistance;
    } else if(currentPose.x < 0) { //neg
        pose.x = xPerpDistance - lemlib::halfWidth;
    }

    //y reset
    if(currentPose.y > 0){ //pos
        pose.y = lemlib::halfWidth - yPerpDistance;
    } else if(currentPose.y < 0){ //neg
        pose.y = yPerpDistance - lemlib::halfWidth;
    }

    this->setPose(pose);
    this->endMotion();
    return;
}

void lemlib::Chassis::distResetX(char xDirection) {
    float rotated = 0;

    //pick active dist sensor for side
    DistResetSensors* xDist = nullptr;

        //if using front or back as x direction, rotate angle by adding 90 degrees
        if(xDirection == 'F') {
            xDist = &distSensors.front;
            rotated = M_PI_2;
        } else if(xDirection == 'B') {
            xDist = &distSensors.back;
            rotated = M_PI_2;
        } else if(xDirection == 'R') {
            xDist = &distSensors.right;
        } else if(xDirection == 'L') {
            xDist = &distSensors.left;
        }

        if(xDist != nullptr && mmToIn(xDist->distance.get())>300) {
            xDist = nullptr;
        }

        if(xDist == nullptr) {
            this->endMotion();
            return;
        }

        lemlib::Pose currentPose = this->getPose(true);
    //this is going to be the reset pose with theta in degrees
        lemlib::Pose pose(0, this->getPose(false).y, this->getPose(false).theta);

        const float correctedAngle = lemlib::refAngle(true, lemlib::sanitizeAngle(currentPose.theta-rotated, true)); 
        //determine if robot is to the left or right of closest axis (determines if you add or subtract offset distance calculated with tangent term)
        //if to the left, subtract, if to the right, add
        const int offsetMultiplier = (std::sin(currentPose.theta-rotated) >= 0) ? -1 : 1;
    
        //calculate perpendicular distance from center to perimeter
        //cosine of entire distance from center of bot to perimeter (not perpendicular)
        //entire distance = distance sensor in inches + discrepancy from offset distance sensor + distance from center of bot
        float xPerpDistance = 0;

        if(xDist != nullptr)
        xPerpDistance = cos(correctedAngle) * (mmToIn(xDist->distance.get()) + tan(correctedAngle) * xDist->offsetX * offsetMultiplier + xDist->offsetY);

            //x reset
        if(currentPose.x > 0){ //pos
            pose.x = lemlib::halfWidth - xPerpDistance;
        } else if(currentPose.x < 0) { //neg
            pose.x = xPerpDistance - lemlib::halfWidth;
        }

        this->setPose(pose);
        this->endMotion();
        return;
}

void lemlib::Chassis::distResetY(char yDirection) {
    float rotated = 0;

    //pick active dist sensor for side
    DistResetSensors* yDist = nullptr;

        //if using left or right as y direction, rotate angle by adding 90 degrees
        if(yDirection == 'F') {
            yDist = &distSensors.front;
        } else if(yDirection == 'B') {
            yDist = &distSensors.back;
        } else if(yDirection == 'R') {
            yDist = &distSensors.right;
            rotated = M_PI_2;
        } else if(yDirection == 'L') {
            yDist = &distSensors.left;
            rotated = M_PI_2;
        }

        if(yDist != nullptr && mmToIn(yDist->distance.get())>300) {
            yDist = nullptr;
        }

        if(yDist == nullptr) {
            this->endMotion();
            return;
        }

        // set motion to end if Ydist reads no ptr

        lemlib::Pose currentPose = this->getPose(true);
    //this is going to be the reset pose with theta in degrees
        lemlib::Pose pose(this->getPose(false).x, 0, this->getPose(false).theta);

        const float correctedAngle = lemlib::refAngle(true, lemlib::sanitizeAngle(currentPose.theta-rotated, true)); 
        //determine if robot is to the left or right of closest axis (determines if you add or subtract offset distance calculated with tangent term)
        //if to the left, subtract, if to the right, add
        const int offsetMultiplier = (std::sin(currentPose.theta-rotated) >= 0) ? -1 : 1;
    
        //calculate perpendicular distance from center to perimeter
        //cosine of entire distance from center of bot to perimeter (not perpendicular)
        //entire distance = distance sensor in inches + discrepancy from offset distance sensor + distance from center of bot
        float yPerpDistance = 0;

        if(yDist != nullptr)
        yPerpDistance = cos(correctedAngle) * (mmToIn(yDist->distance.get()) + tan(correctedAngle) * yDist->offsetX * offsetMultiplier + yDist->offsetY);

            //y reset
        if(currentPose.y > 0){ //pos
            pose.y = lemlib::halfWidth - yPerpDistance;
        } else if(currentPose.y < 0){ //neg
            pose.y = yPerpDistance - lemlib::halfWidth;
        }

        this->setPose(pose);
        this->endMotion();
        return;
}