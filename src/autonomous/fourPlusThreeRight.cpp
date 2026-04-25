#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void fourPlusThreeRight() {
    //dist reset
    chassis.setPose(1, -1, 0);
    chassis.distanceReset('R', 'B');

    //block grab 3
    intakeState = 3;
    wingState = 1;
    chassis.moveToPoint(23.5, -25.5, 1000, {.minSpeed = 50}, true);
    chassis.waitUntil(16);
    scraperState = 1;
    wingState = 0;

    //go to long goal
    chassis.turnToPoint(48, -38, 1000, {.minSpeed = 60});
    chassis.moveToPoint(48, -38, 1000);
    chassis.turnToHeading(180, 1000, {.minSpeed = 60});
    chassis.distanceReset('L', 'F');
    chassis.moveToPoint(47.5, -26, 1000, {.forwards = false, .minSpeed = 100});

    //score
    trapdoorState = 1;
    intakeState = 1;
    rightMotors.move(-60);
    leftMotors.move(-60); //prev 80
    pros::delay(600);

    //dsr in long
    chassis.setPose(1, -1, chassis.getPose().theta);
    chassis.distanceReset('L', 'F');
    scraperState = 0;

    //wing
    chassis.moveDistance(2, 1000, {.minSpeed = 100});
    chassis.swingToHeading(330, lemlib::DriveSide::RIGHT, 1000, {.direction = lemlib::AngularDirection::CW_CLOCKWISE, .minSpeed = 100, .earlyExitRange = 10, .coast = false});
    chassis.turnToHeading(7, 1000, {.direction = lemlib::AngularDirection::CW_CLOCKWISE, .minSpeed = 30, .earlyExitRange = 6}); //prev 4
    chassis.moveToPoint(34, -18, 1000, {.minSpeed = 100});
    chassis.turnToHeading(-15, 1000, {.minSpeed = 100});
    intakeState = 0;

    //move to ml
    pros::delay(1000); //very important delay //2500 before
    wingState = 1;
    trapdoorState = 0;
    intakeState = 1;
    chassis.turnToHeading(0, 1000);
    chassis.moveDistance(-18, 1000, {.forwards = false, .minSpeed = 80});
    chassis.moveToPoint(44.5, -44, 1000, {.forwards = false, .maxSpeed = 80}); //blindcode
    chassis.turnToHeading(-178, 1000);
    chassis.setPose(1, -1, chassis.getPose().theta); 
    chassis.distanceReset('L', 'F'); //TODO: make sure ml works
    scraperState = 1;
    chassis.moveToPoint(47, -56, 1000, {.minSpeed = 127 * 0.6});
    chassis.turnToHeading(180, 1000);
    chassis.sendVoltage(12000 * 0.6, 600);

    //go to low goal
    chassis.moveDistance(-7, 1000, {.forwards = false}); //TODO: CHANGE.
    chassis.distanceReset('L', 'F');
    scraperState = 0;
    chassis.turnToPoint(10, 12, 1000);
    chassis.moveToPoint(10, -12, 2000, {.maxSpeed = 80, .earlyExitRange = 3}, true);
    chassis.waitUntil(45);
    intakeState = 2;

    return;
}