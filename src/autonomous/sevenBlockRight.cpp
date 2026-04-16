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
    chassis.moveToPoint(24, -24, 1000, {}, true);
    chassis.waitUntil(14);
    scraperState = 1;
    chassis.waitUntilDone();
    chassis.turnToHeading(145, 1000, {.minSpeed = 60});
    wingState = 0;

    //go to ml
    chassis.moveToPose(48, -58, 179, 1000, {.lead = 0.4});
    chassis.sendVoltage(12000 * 0.5, 500);
    pros::delay(400);
    chassis.turnToHeading(181, 1000);
    chassis.distanceReset('L', 'F');

    //score long
    chassis.moveToPoint(49, -25, 1500, {.forwards = false, .minSpeed = 80});
    intakeState = 1;
    trapdoorState = 1;
    chassis.sendVoltage(-12000 * 0.5, 1350);
    chassis.setPose(1, -1, chassis.getPose().theta);
    chassis.distanceReset('L', 'F');
    scraperState = 0;

    //wing
    chassis.sendVoltage(12000 * 0.5, 100);
    chassis.moveToPoint(36, -40, 1000);
    chassis.turnToHeading(0, 1000, {.minSpeed = 60});
    chassis.moveToPoint(33.5, -13, 1000);
    chassis.turnToHeading(-15, 1000, {.minSpeed = 110});

    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    return;
}