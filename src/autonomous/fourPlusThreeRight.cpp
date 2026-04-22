#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void fourPlusThreeRight() {
    //dist reset
    chassis.setPose(1, -1, 0);
    chassis.distanceReset('R', 'B');

    //block grab 3
    intakeState = 3;
    wingState = 1;
    chassis.moveToPoint(22.5, -26.5, 1000, {.minSpeed = 80}, true);
    chassis.waitUntil(16.5);
    scraperState = 1;
    wingState = 0;
    chassis.turnToHeading(-65, 1000, {.minSpeed = 60});
    //chassis.turnToPoint(39, -32.5, 1000, {.forwards = false, .minSpeed = 60}); //prev 60
    chassis.moveToPoint(39, -29, 500, {.forwards = false, .minSpeed = 80, .earlyExitRange = 2.5}); //prev y=-34 for both

    //swing into goal
    leftMotors.move(-127);
    rightMotors.move(30); //prev 40

    while(chassis.getPose().theta > -160) {
        pros::delay(10);
    } 
    
    //start scoring early within 40deg of target
    trapdoorState = 1;
    intakeState = 1;

    while(chassis.getPose().theta > -175) {
        pros::delay(10);
    }

    //start reversing angular dir and reverse into long within 20 deg
    rightMotors.move(-127);
    leftMotors.move(-127); //prev 80
    pros::delay(500);

    //dsr in long
    chassis.turnToHeading(180, 1000);
    chassis.setPose(1, -1, 180);
    chassis.distanceReset('L', 'F');
    scraperState = 0;

    //wing
    chassis.moveDistance(2, 1000, {.minSpeed = 100});
    chassis.swingToHeading(320, lemlib::DriveSide::RIGHT, 1000, {.direction = lemlib::AngularDirection::CW_CLOCKWISE, .minSpeed = 100, .earlyExitRange = 10, .coast = false});
    chassis.turnToHeading(5, 1000, {.direction = lemlib::AngularDirection::CW_CLOCKWISE, .minSpeed = 30, .earlyExitRange = 6}); //prev 4
    chassis.moveToPoint(34, -18, 1000, {.minSpeed = 100});
    chassis.turnToHeading(-15, 1000, {.minSpeed = 100});
    intakeState = 0;

    //move to ml
    pros::delay(2500); //very important delay
    wingState = 1;
    trapdoorState = 0;
    intakeState = 1;
    chassis.turnToHeading(0, 1000);
    chassis.moveDistance(-24, 1000, {.forwards = false, .minSpeed = 60});
    chassis.moveToPoint(44, -48, 1000, {.forwards = false, .maxSpeed = 60}); //blindcode
    chassis.turnToHeading(180, 1000);
    chassis.setPose(1, -1, chassis.getPose().theta);
    chassis.distanceReset('L', 'F');
    scraperState = 1;
    chassis.moveToPoint(47, -56, 1000, {.minSpeed = 127 * 0.4});
    chassis.sendVoltage(12000 * 0.4, 650);

    //go to low goal
    chassis.moveDistance(-8, 1000);
    chassis.distanceReset('L', 'F');
    scraperState = 0;
    chassis.turnToPoint(10, -14, 1000);
    chassis.moveToPose(10, -14, 315, 2000, {.maxSpeed = 80, .earlyExitRange = 2}, true);
    chassis.waitUntil(45);
    intakeState = 2;

    return;
}