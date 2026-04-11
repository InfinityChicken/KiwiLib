#include "autonomous/autonomous.hpp"

void fourPlusThreeRight() {
    //dsr
    chassis.setPose(1, -1, 90);
    chassis.distanceReset('F', 'R');
    intakeState = 1;
    wingState = 1;

    //move to and do ml
    scraperState = 1;
    chassis.moveToPoint(47, -47, 1000);
    wingState = 0;
    chassis.turnToHeading(180, 1000);
    chassis.moveDistance(10, 1000, {.minSpeed = 63.5});
    chassis.sendVoltage(6000, 600);
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
    chassis.moveToPoint(33.5, -11, 1000);
    chassis.turnToHeading(-15, 1000, {.minSpeed = 110});

    //delay and exit long
    pros::delay(2000);
    chassis.turnToHeading(0, 1000);
    chassis.moveToPoint(32.5, -36, 1000, {.forwards = false});

    //block grab
    chassis.turnToPoint(24, -24, 1000);
    chassis.moveToPoint(24, -24, 1000);
    chassis.waitUntil(14); //TODO: tune
    scraperState = 1;

    //score low
    chassis.turnToPoint(0, 0, 1000);
    scraperState = 0;
    chassis.moveToPose(15, -15, -45, 1000);
    intakeState = 2;
}