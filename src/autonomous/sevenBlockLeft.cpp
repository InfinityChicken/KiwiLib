#include "autonomous/autonomous.hpp"
#include <strings.h>

//reflect blindcode
void sevenLeft() {
    //dist reset
    chassis.setPose(-1, -1, 0);
    chassis.distanceReset('L', 'B');

    //block grab
    intakeState = 3;
    wingState = 1;
    chassis.moveToPoint(-24, -24, 1000, {}, true);
    chassis.waitUntil(14);
    scraperState = 1;
    chassis.waitUntilDone();
    chassis.turnToHeading(-145, 1000);
    wingState = 0;

    //go to ml
    chassis.moveToPose(-47, -58, 180, 1000, {.horizontalDrift = 30, .lead = 0.3});
    chassis.sendVoltage(12000 * 0.5, 800);
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('R', 'F');

    //score long
    chassis.moveToPoint(-47, -12, 1500, {.forwards = false, .minSpeed = 60});
    intakeState = 1;
    trapdoorState = 1;
    chassis.sendVoltage(-12000 * 0.5, 1350);
    chassis.distanceReset('R', 'F');
    scraperState = 0;

    //wing
    chassis.moveToPoint(-36, -36, 1000, {.minSpeed = 80});
    trapdoorState = 0;
    chassis.turnToHeading(180, 1000, {.minSpeed = 80});
    chassis.moveToPoint(-36, -11, 1000, {.forwards = false, .minSpeed = 60});

    return;
}