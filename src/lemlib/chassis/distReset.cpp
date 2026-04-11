#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include <cmath>
#include <iostream>
#include "main.h"
#include <string>

float absMax(float x1, float x2) {
    if(std::fabs(x1) > std::fabs(x2)) {
        pros::screen::print(pros::E_TEXT_MEDIUM, 150, 50, "left front chosen");
        return x1;
    } else {
        pros::screen::print(pros::E_TEXT_MEDIUM, 150, 50, "right front chosen");
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

    //if using front or back as x direction, rotate angle by adding 90 degrees
    if(xDirection == 'F') {
        side1 = &distSensors.frontLeft;
        side2 = &distSensors.frontRight;
        rotated = M_PI_2;
    } else if(xDirection == 'B') {
        side1 = &distSensors.back;
        rotated = M_PI_2;
    } else if(xDirection == 'R') {
        side1 = &distSensors.right;
    } else if(xDirection == 'L') {
        side1 = &distSensors.left;
    }
        
    //if using left or right as y direction, rotate angle by adding 90 degrees
    if(yDirection == 'F') {
        front1 = &distSensors.frontLeft;
        front2 = &distSensors.frontRight;
    } else if(yDirection == 'B') {
        front1 = &distSensors.back;
    } else if(yDirection == 'R') {
        front1 = &distSensors.right;
        rotated = M_PI_2;
    } else if(yDirection == 'L') {
        front1 = &distSensors.left;
        rotated = M_PI_2;
    }

    if(side1 != nullptr && mmToIn(side1->distance.get())>300) {
        side1 = nullptr;
        std::cout<<"side1 bad\n";
    } 
    if(side2 != nullptr && mmToIn(side2->distance.get())>300) {
        side2 = nullptr;
        std::cout<<"side2 bad\n";
    }
    if(front1 != nullptr && mmToIn(front1->distance.get())>300) {
        front1 = nullptr;
        std::cout<<"front1 bad\n";
    } 
    if(front2 != nullptr && mmToIn(front2->distance.get())>300) {
        front2 = nullptr;
        std::cout<<"front2 bad\n";
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

    std::cout<<"offsetMultiplier: "<<offsetMultiplier<<"        rotated: "<<rotated<<"\n";
    std::cout<<"correctedAngle: "<<correctedAngle<<"\n";
    std::cout<<"sanitized angle: "<<lemlib::sanitizeAngle(currentPose.theta-rotated)*180/M_PI<<"\n";
    //print pose to brain screen
    pros::screen::print(pros::E_TEXT_MEDIUM, 150, 10, "correctedAngle: %.3f", correctedAngle);
    char buf[64];
    snprintf(buf, sizeof(buf), "%.3f, %.3f, %.3f",
            currentPose.x, currentPose.y, currentPose.theta);
    std::string printPos(buf);
    pros::screen::print(pros::E_TEXT_MEDIUM, 150, 30, "Position: %s", printPos.c_str());
    std::cout<<printPos<<"\n";

    //calculate perpendicular distance from center to perimeter
    //cosine of entire distance from center of bot to perimeter (not perpendicular)
    //entire distance = distance sensor in inches + discrepancy from offset distance sensor + distance from center of bot
    float xPerpDistance1 = 0;
    float yPerpDistance1 = 0;
    if(side1 != nullptr)
        xPerpDistance1 = cos(correctedAngle) * (mmToIn(side1->distance.get()) + tan(correctedAngle) * side1->offsetX * offsetMultiplier + side1->offsetY);
    if(front1 != nullptr)
        yPerpDistance1 = cos(correctedAngle) * (mmToIn(front1->distance.get()) + tan(correctedAngle) * front1->offsetX * offsetMultiplier + front1->offsetY);
    
    //back up calculations for other front dist sensor
    float xPerpDistance2 = 0;
    float yPerpDistance2 = 0;
    if(side2 != nullptr) {
        xPerpDistance2 = cos(correctedAngle) * (mmToIn(side2->distance.get()) + tan(correctedAngle) * side2->offsetX * offsetMultiplier + side2->offsetY);
    } else if (front2 != nullptr) {
        yPerpDistance2 = cos(correctedAngle) * (mmToIn(front2->distance.get()) + tan(correctedAngle) * front2->offsetX * offsetMultiplier + front2->offsetY);
    }

    //compare distances and choose further distance
    float xPerpDistance, yPerpDistance;
    if(xDirection == 'F') {
        xPerpDistance = absMax(xPerpDistance1, xPerpDistance2);
        yPerpDistance = yPerpDistance1;
    } else if (yDirection == 'F') {
        xPerpDistance = xPerpDistance1;
        yPerpDistance = absMax(yPerpDistance1, yPerpDistance2);
    }

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


    char buf1[64];
    snprintf(buf1, sizeof(buf1), "%.3f, %.3f, %.3f",
            pose.x, pose.y, pose.theta);
    std::string printPos1(buf1);
    pros::screen::print(pros::E_TEXT_MEDIUM, 150, 70, "Distance Reset: %s", printPos1.c_str());
    std::cout<<printPos1<<"\n";
    std::cout<<"distance reset finished\n\n";

    this->setPose(pose);
    // this->endMotion();
    return;
    
}