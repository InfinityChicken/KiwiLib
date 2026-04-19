#include "autonomous/autonomous.hpp"
#include <strings.h>

void sevenRight() {
    //dist reset
    chassis.setPose(1, -1, 0);
    chassis.distanceReset('R', 'B');

    //block grab
    intakeState = 3;
    wingState = 1;
    chassis.moveToPoint(24, -23, 1000, {.minSpeed = 90, .earlyExitRange = 9}, true);
    chassis.waitUntil(14);
    scraperState = 1;
    chassis.waitUntilDone();
    chassis.turnToHeading(115, 500, {.minSpeed = 70});
    wingState = 0;

    //go to ml
    chassis.moveToPose(48, -58, 180, 1500, {.horizontalDrift = 40, .earlyExitRange = 1.5}); //TODO
    chassis.turnToHeading(180, 1000, {.minSpeed = 10}); //TODO
    chassis.moveDistance(8, 1000, {.minSpeed = 127 * 0.6});
    chassis.sendVoltage(12000 * 0.6, 500);

    //dsr
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('L', 'F');

    //get to long
    chassis.moveToPoint(47, -27, 1000, {.forwards = false, .minSpeed = 110, .earlyExitRange = 20});
    chassis.moveToPoint(47, -27, 1000, {.forwards = false, .maxSpeed = 80, .minSpeed = 127 * 0.4}, true);
    chassis.waitUntil(17);
    trapdoorState = 1;
    intakeState = 1;
    chassis.waitUntilDone();

    leftMotors.move(-127 * 0.4);
    rightMotors.move(-127 * 0.4);
    pros::delay(750);

    //dsr in long
    chassis.turnToHeading(180, 1000);
    chassis.setPose(1, -1, 180);
    chassis.distanceReset('L', 'F');
    scraperState = 0;

    //wing
    chassis.moveDistance(4, 1000, {.minSpeed = 100});
    chassis.swingToHeading(340, lemlib::DriveSide::RIGHT, 1000, {.direction = lemlib::AngularDirection::CW_CLOCKWISE, .minSpeed = 100, .earlyExitRange = 10, .coast = false});
    chassis.turnToHeading(5, 1000, {.direction = lemlib::AngularDirection::CW_CLOCKWISE, .minSpeed = 30, .earlyExitRange = 6}); //prev 4
    chassis.moveToPoint(34, -17, 1000, {.minSpeed = 100});
    chassis.turnToHeading(-10, 1000);
    intakeState = 0;
}