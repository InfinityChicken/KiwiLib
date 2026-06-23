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

    //if using front or back as x direction, need to switch axes so x measures left and right
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
        
    //if using left or right as y direction, need to rotate axes so y measures fwd and back
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

    // switch makes sure axes for reference angle are correct

    //invalidate sensors that return readings out of range
    if(xDist != nullptr && mmToIn(xDist->distance.get())>300) {
        xDist = nullptr;
    }

    if(yDist != nullptr && mmToIn(yDist->distance.get())>300) {
        yDist = nullptr;
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

    
    // GETTING CORRECTED ANGLE: 

    //we need to reformat our heading into a reference angle to deal with simpler trig values
    //subtracting rotated re-zeros the angle to the wall direction, making our ref angle based off where we face
    //then we sanitize the given angle, making our ref angle easier to deal with during trig


    const float correctedAngle = lemlib::refAngle(true, 
        lemlib::sanitizeAngle(currentPose.theta-rotated, true));
    
    
    // DERIVING OFFSET MULTIPLIER: 

    //since our distance sensors are offset from the center, their distance will either be closer or farther to the wall
    // than center, makingraw reading longer/shorter than what we need
    // if sin(α) > 0, dist sensor ray = longer than central, multiplier = -1, and vice versa    

    const int offsetMultiplier = (std::sin(currentPose.theta-rotated) >= 0) ? -1 : 1;

    std::cout<<"offsetMultiplier: "<<offsetMultiplier<<"        rotated: "<<rotated<<"\n";
    std::cout<<"correctedAngle: "<<correctedAngle<<"\n";
    std::cout<<"sanitized angle: "<<lemlib::sanitizeAngle(currentPose.theta-rotated)*180/M_PI<<"\n";


    // ACTUAL DISTANCE CALCULATION

    // now we need to find acc perpendicular distance

    // we need: 
    // - sensorRay = rawRay + tan(α) * offsetX * multiplier  (this is all lateral correction): 
    // - - tan(α) = opp/adj, adj = offsetX, opp = difference in ray length
    // - - tan(α) * adjacent = opposite
    // - - tan(α) * offsetX =  difference in ray length
    // - - we also add offsetY (vertical correction)

    // - to get perp distance, we take this sensorRay and our heading
    // - - sensorRay = hypotenuse, perpDistance = adj
    // - - cos(α) = adj/hypotenuse, cos(α) * sensorRay = perpDistance
    


    //x perpDistance 
    float xSensorRay = mmToIn(xDist->distance.get());
    float xLatCorr = tan(correctedAngle) * xDist->offsetX * offsetMultiplier;
    float xVertCorr = xDist ->offsetY;
    float xPerpDistance = 0;
    
    if(xDist != nullptr){
        xPerpDistance = cos(correctedAngle) * (xSensorRay + xLatCorr + xVertCorr);
    }


    //y perpDistance 
    float ySensorRay = mmToIn(yDist->distance.get());
    float yLatCorr = tan(correctedAngle) * yDist->offsetY * offsetMultiplier;
    float yVertCorr = yDist ->offsetY;
    float yPerpDistance = 0;

    if(yDist != nullptr){
        yPerpDistance = cos(correctedAngle) * (ySensorRay + yLatCorr + yVertCorr);
    }
   
   

    // FINAL RESETS:
        //x reset
    if(currentPose.x > 0){ // if on east half of coord plane, +x coord for pose
        pose.x = lemlib::halfWidth - xPerpDistance;
    } else if(currentPose.x < 0) { //else, -x coord, so subtract width from perpdistance
        pose.x = xPerpDistance - lemlib::halfWidth;
    }
    std::cout<<"x position reset\n";

    //y reset
    if(currentPose.y > 0){ //if on north half of coord plane, +y coord for pose
        pose.y = lemlib::halfWidth - yPerpDistance;
    } else if(currentPose.y < 0){ //else, -y coord, so subtract width from perpdistance
        pose.y = yPerpDistance - lemlib::halfWidth;
    }
    std::cout<<"y position reset\n";


    std::cout<<"distance reset finished\n\n";

    this->setPose(pose);
    // this->endMotion();
    return;
}
