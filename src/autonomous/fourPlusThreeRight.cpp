#include "autonomous/autonomous.hpp"
#include "pros/motors.h"

//reflect blindcode
void fourPlusThreeRight() {
    //dsr
    chassis.setPose(1, -1, 90);
    chassis.distanceReset('F', 'R');
    intakeState = 1;
    wingState = 1;

    //move to and do ml
    scraperState = 1;
    chassis.moveToPoint(46, chassis.getPose().y, 1000, {.minSpeed = 100, .earlyExitRange = 5});
    chassis.moveToPoint(46, chassis.getPose().y, 1000, {.maxSpeed = 60});
    wingState = 0;
    chassis.turnToHeading(182, 1000);
    chassis.moveDistance(10, 1000, {.minSpeed = 127 * 0.5});
    chassis.sendVoltage(6000, 350);
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('L', 'F');

    //score long
    chassis.moveToPoint(48, -25, 1000, {.forwards = false, .minSpeed = 100});
    intakeState = 3;
    trapdoorState = 1;
    chassis.sendVoltage(-12000 * 0.5, 1350);
    chassis.setPose(1, -1, chassis.getPose().theta);
    chassis.distanceReset('L', 'F');
    scraperState = 0;

    //wing copied from 7right
    chassis.sendVoltage(12000, 150);
    chassis.moveToPoint(35.25, -40, 1000, {.minSpeed = 60, .earlyExitRange = 4});
    chassis.turnToHeading(-10, 500, {.minSpeed = 60, .earlyExitRange = 2});
    chassis.moveToPoint(33.5, -13, 1000);
    chassis.turnToHeading(-15, 1000, {.minSpeed = 110});
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

    //delay and exit long
    pros::delay(3000);
    intakeState = 1;
    wingState = 1;
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    chassis.moveDistance(5, 1000);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    chassis.turnToPoint(21, -24, 1000);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

    //block grab
    chassis.moveToPoint(21, -24, 1000, {}, true);
    chassis.waitUntil(4); //tune
    scraperState = 1;
    chassis.waitUntilDone();

    //score mid
    chassis.turnToHeading(-45, 1000);
    scraperState = 0;
    chassis.moveToPoint(2, -7, 1000, {.maxSpeed = 60});
    intakeState = 2;
}