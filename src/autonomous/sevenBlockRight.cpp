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
    chassis.moveToPose(45, -57.25, 179, 1000, {.lead = 0.5, .minSpeed = 60});
    chassis.sendVoltage(12000 * 0.5, 500);
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
    chassis.moveDistance(4, 1000, {.minSpeed = 100});
    chassis.swingToHeading(310, lemlib::DriveSide::RIGHT, 1000, {.direction = lemlib::AngularDirection::CW_CLOCKWISE, .minSpeed = 100, .earlyExitRange = 10, .coast = false});
    chassis.turnToHeading(360, 1000, {.minSpeed = 30, .earlyExitRange = 6}); //prev 4
    chassis.moveToPoint(32.5, -15.5, 1000, {.minSpeed = 100}); //TODO: tune
    intakeState = 0;
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}