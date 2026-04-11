#include "autonomous/autonomous.hpp"

void sevenRight() {
    //dist reset
    chassis.setPose(1, -1, 0);
    chassis.distanceReset('R', 'B');
    wingState = 1;

    //block grab
    intakeState = 1;
    chassis.moveToPoint(24, -24, 1000, {}, true);
    wingState = 0;
    chassis.waitUntil(14);
    scraperState = 1;
    chassis.waitUntilDone();
    chassis.turnToHeading(145, 1000);

    //go to ml
    chassis.moveToPose(48.5, -58, 180, 1000, {.horizontalDrift = 30, .lead = 0.3, .earlyExitRange = 5});
    chassis.sendVoltage(12000 * 0.3, 800);
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('L', 'F');

    //score long
    chassis.moveToPoint(48.5, -26, 1000, {.forwards = false});
    trapdoorState = 1;
    chassis.sendVoltage(-12000 * 0.5, 1000);
    chassis.distanceReset('L', 'F');
    scraperState = 0;

    //wing
    chassis.moveToPoint(33.5, -40, 1000);
    chassis.turnToHeading(0, 1000);
    chassis.moveToPoint(32, -11, 1000);
    chassis.turnToHeading(-15, 1000, {.minSpeed = 110});

    return;
}