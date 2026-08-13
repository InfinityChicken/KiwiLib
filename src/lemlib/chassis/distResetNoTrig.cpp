#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"

void lemlib::Chassis::distanceResetNoTrig(char xDirection, char yDirection) {
    //treat as lemlib motion so doesnt interfere with motions in progress
    this->requestMotionStart();

    //pick active dist sensor for side
    DistResetSensors* xDist = nullptr;
    DistResetSensors* yDist = nullptr;

    //if using front or back as x direction, need to switch axes so x measures left and right
    if(xDirection == 'F') {
        xDist = &distSensors.front;
    } else if(xDirection == 'B') {
        xDist = &distSensors.back;
    } else if(xDirection == 'R') {
        xDist = &distSensors.right;
    } else if(xDirection == 'L') {
        xDist = &distSensors.left;
    }
        
    //if using left or right as y direction, need to rotate axes so y measures fwd and back
    if(yDirection == 'F') {
        yDist = &distSensors.front;
    } else if(yDirection == 'B') {
        yDist = &distSensors.back;
    } else if(yDirection == 'R') {
        yDist = &distSensors.right;
    } else if(yDirection == 'L') {
        yDist = &distSensors.left;
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
    if(xDist == nullptr || yDist == nullptr) {
        this->endMotion();
        return;
    }

    //get current position
    lemlib::Pose currentPose = this->getPose(true);

    //this is going to be the reset pose with theta in degrees
    lemlib::Pose pose(0, 0, this->getPose(false).theta);

    //x perpDistance 
    float xSensorRay = mmToIn(xDist->distance.get());
    float xVertCorr = xDist ->offsetY;
    float xPerpDistance = 0;
    
    xPerpDistance = (xSensorRay + xVertCorr);

    //y perpDistance
    float ySensorRay = mmToIn(yDist->distance.get());
    float yVertCorr = yDist ->offsetY;
    float yPerpDistance = 0;

    yPerpDistance = (ySensorRay + yVertCorr);

    // FINAL RESETS:
        //x reset
    if(currentPose.x > 0){ // if on east half of coord plane, +x coord for pose
        pose.x = lemlib::halfWidth - xPerpDistance;
    } else if(currentPose.x < 0) { //else, -x coord, so subtract width from perpdistance
        pose.x = xPerpDistance - lemlib::halfWidth;
    } else {
        pose.x = 0;
    }

    //y reset
    if(currentPose.y > 0){ //if on north half of coord plane, +y coord for pose
        pose.y = lemlib::halfWidth - yPerpDistance;
    } else if(currentPose.y < 0){ //else, -y coord, so subtract width from perpdistance
        pose.y = yPerpDistance - lemlib::halfWidth;
    } else {
        pose.y = 0;
    }

    this->setPose(pose);
    this->endMotion();
    return;
}