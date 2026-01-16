#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include <cmath>
#include <iostream>
#include "main.h"
#include <string>

float mmToIn(float mm) {
    return mm / 25.4;
}

void lemlib::Chassis::distanceReset(char xDirection, char yDirection, char frontSide) { //frontSide true is 
    std::cout<<"distance reset started\n";
    //treat as lemlib motion so doesnt interfere with motions in progress
    this->requestMotionStart();

    float rotated = 0;

    //pick active dist sensor for side
    DistResetSensors* side;
    DistResetSensors* front;

    //if using front or back as x direction, rotate angle by adding 90 degrees
    if(xDirection == 'F') {
        if(frontSide == 'L') {
            side = &distSensors.frontLeft;
        } else if (frontSide == 'R') {
            side = &distSensors.frontRight;
        }
        rotated = M_PI_2;
    } else if(xDirection == 'B') {
        side = &distSensors.back;
        rotated = M_PI_2;
    } else if(xDirection == 'R') {
        side = &distSensors.right;
    } else if(xDirection == 'L') {
        side = &distSensors.left;
    }
        
    //if using left or right as y direction, rotate angle by adding 90 degrees
    if(yDirection == 'F') {
        if(frontSide == 'L') {
            front = &distSensors.frontLeft;
        } else if (frontSide == 'R') {
            front = &distSensors.frontRight;
        }
    } else if(yDirection == 'B') {
        front = &distSensors.back;
    } else if(yDirection == 'R') {
        front = &distSensors.right;
        rotated = M_PI_2;
    } else if(yDirection == 'L') {
        front = &distSensors.left;
        rotated = M_PI_2;
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

    //calculate perpendicular distance from center to perimeter
    //cosine of entire distance from center of bot to perimeter (not perpendicular)
    //entire distance = distance sensor in inches + discrepancy from offset distance sensor + distance from center of bot
    float xPerpDistance = cos(correctedAngle) * (mmToIn(side->distance.get()) + tan(correctedAngle) * side->offsetX * offsetMultiplier + side->offsetY);
    float yPerpDistance = cos(correctedAngle) * (mmToIn(front->distance.get()) + tan(correctedAngle) * front->offsetX * offsetMultiplier + front->offsetY);
    

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
    pros::screen::print(pros::E_TEXT_MEDIUM, 150, 50, "Distance Reset: %s", printPos.c_str());
    std::cout<<printPos1<<"\n";
    std::cout<<"distance reset finished\n";

    this->setPose(pose);
    this->endMotion();
    return;
    
}