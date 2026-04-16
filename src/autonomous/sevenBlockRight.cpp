#include "autonomous/autonomous.hpp"
#include <strings.h>

//og
void sevenRight() {
    //dist reset
    chassis.setPose(1, -1, 0);
    chassis.distanceReset('R', 'B');

    //block grab
    intakeState = 3;
    wingState = 1;
    chassis.moveToPoint(24, -24, 1000, {.minSpeed = 90, .earlyExitRange = 9}, true);
    chassis.waitUntil(14);
    scraperState = 1;
    chassis.waitUntilDone();
    chassis.turnToHeading(130, 500, {.minSpeed = 70});
    wingState = 0;

    //go to ml
    chassis.moveToPose(44, -55.5, 179, 1000, {.lead = 0.5, .minSpeed = 80});
    chassis.sendVoltage(12000 * 0.7, 500);
    pros::delay(400);
    chassis.turnToHeading(181, 1000);
    chassis.distanceReset('L', 'F');

    //score long
    chassis.moveToPoint(49, -25, 1500, {.forwards = false, .minSpeed = 100});
    intakeState = 1;
    trapdoorState = 1;
    chassis.sendVoltage(-12000 * 0.5, 1350);
    chassis.setPose(1, -1, chassis.getPose().theta);
    chassis.distanceReset('L', 'F');
    scraperState = 0;

    //wing
    chassis.sendVoltage(12000, 120);
    chassis.moveToPoint(35.25, -40, 1000, {.minSpeed = 60, .earlyExitRange = 4});
    chassis.turnToHeading(-10, 500, {.minSpeed = 60, .earlyExitRange = 2});
    chassis.moveToPoint(33.5, -13, 1000);
    chassis.turnToHeading(-15, 1000, {.minSpeed = 110});

    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    return;
}