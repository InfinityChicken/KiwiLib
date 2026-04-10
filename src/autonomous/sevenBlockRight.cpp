#include "autonomous/autonomous.hpp"

void sevenBlockRight() {
    //dist reset
    chassis.setPose(1, -1, 0);
    chassis.distanceReset('R', 'B');

    //block grab
    intakeState = 1;
    chassis.moveToPoint(32, -24, 1000, {.minSpeed = 100}, true);
    chassis.waitUntil(14);
    scraperState = 1;
    chassis.waitUntilDone();
    chassis.turnToHeading(125, 1000, {.minSpeed = 100});

    //curve to ml
    chassis.moveToPoint(52, -58, 2000, {.minSpeed = 110});
    leftMotors.move(60);
    rightMotors.move(60);
    pros::delay(600);
    leftMotors.move(0);
    rightMotors.move(0);

    //move to long goal
    chassis.moveToPoint(chassis.getPose().x, chassis.getPose().y - 8, 1000, {.forwards = false, .minSpeed = 100});
        //force movement 8 inches backward
    chassis.distanceReset('L', 'F');
    chassis.moveToPoint(47, -8, 1000, {.forwards = false, .minSpeed = 80});
    trapdoorState = 1;
}