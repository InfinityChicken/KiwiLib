#include "autonomous/autonomous.hpp"
#include <strings.h>

void sevenLeft() {
    //dist reset
    chassis.setPose(-1, -1, 0);
    chassis.distanceReset('L', 'B');

    //block grab
    intakeState = 3;
    wingState = 1;
    chassis.moveToPoint(-24, -23, 1000, {.minSpeed = 90, .earlyExitRange = 9}, true);
    chassis.waitUntil(14);
    scraperState = 1;
    chassis.waitUntilDone();
    chassis.turnToHeading(-120, 500, {.minSpeed = 70});

    //go to ml
    chassis.moveToPose(-47, -58, 180, 1500, {.horizontalDrift = 50, .lead = 0.32});
    chassis.turnToHeading(180, 1000, {.minSpeed = 20});
    chassis.moveDistance(8, 1000, {.minSpeed = 127 * 0.6});
    chassis.sendVoltage(12000 * 0.6, 500);

    //dsr
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('R', 'F');
    wingState = 0;

    //get to long
    chassis.moveToPoint(-47.5, -27, 1000, {.forwards = false, .minSpeed = 110, .earlyExitRange = 20});
    chassis.moveToPoint(-47.5, -27, 1000, {.forwards = false, .maxSpeed = 80, .minSpeed = 127 * 0.4}, true);
    chassis.waitUntil(17);
    trapdoorState = 1;
    intakeState = 1;
    chassis.waitUntilDone();
    leftMotors.move(-127 * 0.4);
    rightMotors.move(-127 * 0.4);
    pros::delay(750);

    //dsr
    chassis.turnToHeading(180, 1000);
    chassis.setPose(-1, -1, chassis.getPose().theta);
    chassis.distanceReset('R', 'F');
    wingState = 0;

    //left wing
    chassis.turnToHeading(135, 1000, {.minSpeed = 60, .earlyExitRange = 4});
    trapdoorState = 0;
    chassis.moveToPoint(-39, -33.75, 1000, {.minSpeed = 100, .earlyExitRange = 4});
    chassis.turnToHeading(178, 500, {.minSpeed = 60});
    chassis.moveToPoint(-38.5, -12, 1000, {.forwards = false, .minSpeed = 80});
    chassis.turnToHeading(180, 1000);

    return;
}