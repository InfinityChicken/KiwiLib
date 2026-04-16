#include "autonomous/autonomous.hpp"
#include "pros/motors.h"

//og
void fourPlusThreeLeft() {
    //dsr
    chassis.setPose(-1, -1, 270);
    chassis.distanceReset('F', 'L');
    intakeState = 1;
    wingState = 1;

    //move to and do ml
    scraperState = 1;
    chassis.moveToPoint(-46, chassis.getPose().y, 1000, {.minSpeed = 100, .earlyExitRange = 5});
    chassis.moveToPoint(-46, chassis.getPose().y, 1000, {.maxSpeed = 60});
    wingState = 0;
    chassis.turnToHeading(178, 1000);
    chassis.moveDistance(10, 1000, {.minSpeed = 127 * 0.5});
    chassis.sendVoltage(6000, 300);
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('R', 'F');

    //score long
    chassis.moveToPoint(-46, -27, 1000, {.forwards = false, .minSpeed = 100, .earlyExitRange = 8});
    chassis.moveToPoint(-46, -27, 1000, {.forwards = false, .maxSpeed = 80}, true);
    chassis.waitUntil(5);
    intakeState = 3;
    trapdoorState = 1;
    chassis.waitUntilDone();
    chassis.sendVoltage(-12000 * 0.5, 500);
    chassis.distanceReset('R', 'F');
    scraperState = 0;

    //wing
    chassis.moveToPoint(-36, -36, 1000, {.minSpeed = 80});
    trapdoorState = 0;
    chassis.turnToHeading(180, 1000, {.minSpeed = 80});
    chassis.moveToPoint(-36, -11, 1000, {.forwards = false, .minSpeed = 60});

    //delay and exit long
    pros::delay(3000);
    intakeState = 1;
    wingState = 1;
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    chassis.turnToPoint(-21, -24, 1000);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

    //block grab
    chassis.moveToPoint(-21, -24, 1000, {}, true);
    chassis.waitUntil(4);
    scraperState = 1;
    chassis.waitUntilDone();

    //score mid
    chassis.turnToHeading(215, 1000);
    scraperState = 0;
    chassis.moveToPoint(-2, -7, 1000, {.forwards = false, .maxSpeed = 60});
    intakeState = 4;
}