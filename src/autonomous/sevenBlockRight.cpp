#include "autonomous/autonomous.hpp"

void sevenBlockRight() {
    //dist reset
    chassis.setPose(1, -1, 0);
    chassis.distanceReset('R', 'B');

    //block grab
    intakeState = 1;
    chassis.moveToPoint(31, -22, 1000, {}, true);
    chassis.waitUntil(14);
    scraperState = 1;
    chassis.waitUntilDone();
    chassis.turnToHeading(135, 1000);

    //move to ml
    chassis.moveToPoint(56, -41, 1000);
    chassis.turnToHeading(180, 1000);
    chassis.moveDistance(19, 1000);

    //do ml
    pros::delay(100);
    chassis.distanceReset('L', 'F');

    //exit ml
    chassis.moveToPoint(51, -30, 1000, {.forwards = false}); //prev -15
    return;
    trapdoorState = 1;
    pros::delay(500);
    chassis.distanceReset('L', 'F');

    //position for wing
    chassis.moveToPoint(39, -35, 1000);
    chassis.turnToHeading(0, 1000);
    chassis.moveDistance(24, 1000);
    chassis.turnToHeading(-20, 1000, {.minSpeed = 100});
    return;
}