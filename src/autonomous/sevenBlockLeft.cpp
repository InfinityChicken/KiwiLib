#include "autonomous/autonomous.hpp"

void sevenLeft() { //TODO: blindcoded
    //dist reset
    chassis.setPose(-1, -1, 0);
    chassis.distanceReset('L', 'B');

    //block grab
    intakeState = 1;
    chassis.moveToPoint(-24, -24, 1000, {}, true);
    chassis.waitUntil(14);
    scraperState = 1;
    chassis.waitUntilDone();
    chassis.turnToHeading(-145, 1000);

    //go to ml
    chassis.moveToPose(-48, -58, 180, 1000, {.horizontalDrift = 30, .lead = 0.3});
    chassis.sendVoltage(12000 * 0.3, 800);
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('R', 'F');

    //score long
    chassis.moveToPoint(-48.5, -26, 1000, {.forwards = false});
    trapdoorState = 1;
    chassis.sendVoltage(-12000 * 0.5, 1000);
    chassis.distanceReset('R', 'F');
    scraperState = 0;

    //wing
    chassis.moveToPoint(-34, -36, 1000, {.minSpeed = 80});
    trapdoorState = 0;
    chassis.turnToHeading(180, 1000, {.minSpeed = 80});
    chassis.moveToPoint(-34, -11, 1000, {.forwards = false, .minSpeed = 60});

    return;
}