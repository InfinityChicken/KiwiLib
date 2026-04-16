#include "autonomous/autonomous.hpp"

void fourRight() {
    //dist reset
    chassis.setPose(1, -1, 0);
    chassis.distanceReset('R', 'B');

    //block grab
    intakeState = 1;
    chassis.moveToPoint(24, -24, 1000, {}, true);
    chassis.waitUntil(14);
    scraperState = 1;
    chassis.waitUntilDone();
    chassis.turnToHeading(-90, 1000);
    return;

    //rotate into long goal
    chassis.moveToPoint(0, 0, 1000, {.minSpeed = 0}); //TODO: get coordinate
    leftMotors.move_voltage(8000);
    rightMotors.move_voltage(12000);
    while(std::fabs(chassis.getPose().theta) > 10) { //delay until you rotate in
        pros::delay(10);
    }
    
    //score long
    leftMotors.move_voltage(0);
    rightMotors.move_voltage(0);
    chassis.sendVoltage(-12000 * 0.5, 500);
    trapdoorState = 1;

    //wing
    chassis.moveToPoint(33.5, -40, 1000);
    chassis.turnToHeading(0, 1000);
    chassis.moveToPoint(32, -11, 1000);
    chassis.turnToHeading(-15, 1000, {.minSpeed = 110});
    pros::delay(80000);
}