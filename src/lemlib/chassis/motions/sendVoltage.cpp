#include <cmath>
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/timer.hpp"

void lemlib::Chassis::sendVoltage(float voltage, int time) {
    this->requestMotionStart();

    if(!this->motionRunning) return;
    
    Timer timer(time);

    while(!timer.isDone()) {
        this->drivetrain.leftMotors->move_voltage(voltage);
        this->drivetrain.rightMotors->move_voltage(voltage);

        pros::delay(10);
    }

    this->drivetrain.leftMotors->move_voltage(0);
    this->drivetrain.rightMotors->move_voltage(0);

    this->endMotion();
}