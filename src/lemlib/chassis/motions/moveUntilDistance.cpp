#include <cmath>
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"

//TODO: test
void lemlib::Chassis::moveUntilDistance(char dir, float exitDist, float x, float y, float timeout, MoveToPointParams params) {
    //start movement async
    this->moveToPoint(x, y, timeout, params, true); 

    //pick active dist sensor for side
    DistResetSensors* distSensor = nullptr;
    if(dir == 'L') {
        distSensor = &distSensors.frontLeft;
    } else if(dir == 'R') {
        distSensor = &distSensors.right;
    }

    //TODO: adds distance sensor offset Y
    //delay until distance sensor detects exitDist inches or motion is complete
    while(mmToIn(distSensor->distance.get()) + distSensor->offsetY > exitDist && this->isInMotion()) {
        pros::delay(10);
    }

    this->endMotion();
    this->drivetrain.leftMotors->move_velocity(0);
    this->drivetrain.rightMotors->move_velocity(0);
}