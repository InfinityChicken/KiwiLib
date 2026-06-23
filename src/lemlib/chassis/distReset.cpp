#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include <cmath>
#include <iostream>
#include "main.h"
#include <string>

float absMax(float x1, float x2) {
    if(std::fabs(x1) > std::fabs(x2)) {
        return x1;
    } else {
        return x2;
    }
}

void lemlib::Chassis::distanceReset(char xDirection, char yDirection) {
    std::cout<<"distance reset started\n";
    //treat as lemlib motion so doesnt interfere with motions in progress
    // this->requestMotionStart();

    float rotated = 0;

    //pick active dist sensor for side
    DistResetSensors* side1 = nullptr;
    DistResetSensors* side2 = nullptr;
    DistResetSensors* front1 = nullptr;
    DistResetSensors* front2 = nullptr;

    DistResetSensors* xDist = nullptr;
    DistResetSensors* yDist = nullptr;

    //if using front or back as x direction, rotate angle by adding 90 degrees
    if(xDirection == 'F') {
        side1 = &distSensors.frontLeft;
        side2 = &distSensors.frontRight;
        rotated = M_PI_2;

        xDist = side1;
    } else if(xDirection == 'B') {
        side1 = &distSensors.back;
        rotated = M_PI_2;

        xDist = side1;
    } else if(xDirection == 'R') {
        side1 = &distSensors.right;

        xDist = side1;
    } else if(xDirection == 'L') {
        side1 = &distSensors.left;

        xDist = side1;
    }
        
    //if using left or right as y direction, rotate angle by adding 90 degrees
    if(yDirection == 'F') {
        front1 = &distSensors.frontLeft;
        front2 = &distSensors.frontRight;
        rotated = M_PI_2;
        yDist = front1;
    } else if(yDirection == 'B') {
        front1 = &distSensors.back;
        yDist = front1;
    } else if(yDirection == 'R') {
        front1 = &distSensors.right;
        rotated = M_PI_2;
        yDist = front1;
    } else if(yDirection == 'L') {
        front1 = &distSensors.left;
        rotated = M_PI_2;
        yDist = front1;
    }

    if(xDist != nullptr && mmToIn(xDist->distance.get())>300) {
        xDist = nullptr;
    }

    if(yDist != nullptr && mmToIn(yDist->distance.get()) > 300) {
        yDist = nullptr;
    }

    if (xDist == nullptr || yDist == nullptr) {
        this->endMotion();
        return;
    }

    //if both/essential distance sensors are bad, don't reset
    if(side1 == nullptr && side2 == nullptr || front1 == nullptr && front2 == nullptr) {
        this->endMotion();
        return;
    }

    std::cout<<"distance sensors chosen\n";

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
    std::cout<<"x position reset\n";

    //y reset
    if(currentPose.y > 0){ //pos
        pose.y = lemlib::halfWidth - yPerpDistance;
    } else if(currentPose.y < 0){ //neg
        pose.y = yPerpDistance - lemlib::halfWidth;
    }
    std::cout<<"y position reset\n";


    std::cout<<"distance reset finished\n\n";

    this->setPose(pose);
    // this->endMotion();
    return;
}
