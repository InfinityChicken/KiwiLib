#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include <cmath>
#include <iostream>
#include "main.h"
#include <string>

float mmToIn(float mm) {
    return mm / 25.4;
}

void lemlib::Chassis::distanceReset(char xDirection, char yDirection) { //original reset code
    std::cout<<"distance reset started\n";
    //treat as lemlib motion so doesnt interfere with motions in progress
    this->requestMotionStart();

    float rotated = 0;

    //pick active dist sensor for side
    DistResetSensors* side;
    DistResetSensors* front;

    if(xDirection == 'F') {
        side = &distSensors.front;
        rotated = M_PI_2;
    } else if(xDirection == 'B') {
        side = &distSensors.back;
        rotated = M_PI_2;
    } else if(xDirection == 'R') {
        side = &distSensors.right;
    } else if(xDirection == 'L') {
        side = &distSensors.left;
    }
        

    if(yDirection == 'F') {
        front = &distSensors.front;
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

    lemlib::Pose currentPose = this->getPose(true);
    lemlib::Pose pose(0, 0, this->getPose(false).theta);

    //acute angle from axis
    const float correctedAngle = lemlib::refAngle(true, lemlib::sanitizeAngle(currentPose.theta-rotated, true)); 
    const int offsetMultiplier = (std::sin(currentPose.theta-rotated) >= 0) ? -1 : 1;

    std::cout<<"offsetMultiplier: "<<offsetMultiplier<<"        rotated: "<<rotated<<"\n";
    std::cout<<"correctedAngle: "<<correctedAngle<<"\n";
    std::cout<<"sanitized angle: "<<lemlib::sanitizeAngle(currentPose.theta-rotated)*180/M_PI<<"\n";
    
    pros::screen::print(pros::E_TEXT_MEDIUM, 150, 10, "correctedAngle: %.3f", correctedAngle);
    char buf[64];
    snprintf(buf, sizeof(buf), "%.3f, %.3f, %.3f",
            currentPose.x, currentPose.y, currentPose.theta);
    std::string printPos(buf);
    pros::screen::print(pros::E_TEXT_MEDIUM, 150, 30, "Position: %s", printPos.c_str());

    //calculate perpendicular distance from center to perimeter
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
        pose.y = lemlib::halfWidth - yPerpDistance; //TODO: part with tanget should have sign changes based on angle
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

// void lemlib::Chassis::distanceReset(char xWall, char yWall) { //new reset code
//     std::cout << "distance reset started\n";

//     this->requestMotionStart();

//     // Get current pose
//     lemlib::Pose currentPose = this->getPose(true);

//     // Initialize pose reset
//     lemlib::Pose newPose = currentPose;

//     // Helper lambda: wall normal angles (pointing *into* the field)
//     auto wallNormalAngle = [](char wall) -> float {
//         switch (wall) {
//             case 'F': return M_PI;       // Front wall inward normal (-Y)
//             case 'B': return 0.0f;       // Back wall inward normal (+Y)
//             case 'R': return -M_PI_2;    // Right wall inward normal (-X)
//             case 'L': return M_PI_2;     // Left wall inward normal (+X)
//             default: return 0.0f;
//         }
//     };

//     // List of all sensors and their robot-frame mounting angles
//     struct SensorInfo {
//         DistResetSensors* sensor;
//         float angleRobot; // radians relative to robot forward
//     };
//     std::vector<SensorInfo> allSensors = {
//         { &distSensors.front, 0.0f },
//         { &distSensors.back,  M_PI },
//         { &distSensors.right, M_PI_2 },
//         { &distSensors.left, -M_PI_2 }
//     };

//     // Helper: pick the sensor closest to pointing at the wall
//     auto pickSensor = [&](char wall) -> DistResetSensors* {
//         float wallAngle = wallNormalAngle(wall);
//         float minAngleDiff = 1e6;
//         DistResetSensors* best = nullptr;

//         for (auto& s : allSensors) {
//             float sensorWorldAngle = currentPose.theta + s.angleRobot;
//             float diff = fabs(lemlib::sanitizeAngle(sensorWorldAngle - wallAngle, true));
//             if (diff < minAngleDiff) {
//                 minAngleDiff = diff;
//                 best = s.sensor;
//             }
//         }
//         return best;
//     };

//     // Pick sensors for X and Y axes
//     DistResetSensors* xSensor = nullptr;
//     DistResetSensors* ySensor = nullptr;

//     if (xWall == 'L' || xWall == 'R') xSensor = pickSensor(xWall);
//     if (yWall == 'F' || yWall == 'B') ySensor = pickSensor(yWall);

//     // Helper to compute perpendicular distance from sensor to wall
//     auto perpDistance = [&](DistResetSensors* s, char wall) -> float {
//         if (!s) return 0.0f;
//         float wallAngle = wallNormalAngle(wall);
//         float sensorWorldAngle = currentPose.theta + s->angleRobot; // theta + sensor mounting
//         float relAngle = lemlib::sanitizeAngle(sensorWorldAngle - wallAngle, true);

//         float d = mmToIn(s->distance.get());
//         float perp = d * cos(relAngle) + s->offsetX * sin(relAngle) + s->offsetY * cos(relAngle);
//         return perp;
//     };

//     // Reset X
//     if (xSensor) {
//         float perp = perpDistance(xSensor, xWall);
//         if (xWall == 'R') newPose.x = lemlib::halfWidth - perp;
//         else if (xWall == 'L') newPose.x = -lemlib::halfWidth + perp;
//     }

//     // Reset Y
//     if (ySensor) {
//         float perp = perpDistance(ySensor, yWall);
//         if (yWall == 'F') newPose.y = lemlib::halfWidth - perp;
//         else if (yWall == 'B') newPose.y = -lemlib::halfWidth + perp;
//     }

//     std::cout << "Distance reset finished: "
//               << "x=" << newPose.x << ", y=" << newPose.y 
//               << ", theta=" << newPose.theta << "\n";

//     // Apply pose and finish
//     this->setPose(newPose);
//     this->endMotion();
// }