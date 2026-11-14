#include "autonomous/autonomous.hpp"

void preloadAuto() {
    leftMotors.move_voltage(4000);
    rightMotors.move_voltage(4000);
    manualLiftState = 1;
    pros::delay(500);
    leftMotors.move_voltage(0);
    rightMotors.move_voltage(0);
    pros::delay(800);
    manualLiftState = 3;
    pros::delay(1500);
    clawState = 2;

    chassis.turnToHeading(130, 1000);
    leftMotors.move_voltage(4000);
    rightMotors.move_voltage(4000);
    pros::delay(500);
    toggleState = 1;
    pros::delay(1000);
    toggleState = 0;
    leftMotors.move_voltage(0);
    rightMotors.move_voltage(0);
}