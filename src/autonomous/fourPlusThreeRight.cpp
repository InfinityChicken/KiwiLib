#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void fourPlusThreeRight() {
    //dist reset
    chassis.setPose(1, -1, 0);
    chassis.distanceReset('R', 'B');

    //block grab 3
    intakeState = 3;
    wingState = 1;
    chassis.moveToPoint(22.5, -26.5, 1000, {.minSpeed = 127, .earlyExitRange = 2}, true);
    chassis.waitUntil(16.5);
    scraperState = 1;
    wingState = 0;
    chassis.turnToHeading(-33, 1000, {.minSpeed = 60, .earlyExitRange = 5});
    chassis.moveToPoint(39, -30, 1000, {.forwards = false, .minSpeed = 80, .earlyExitRange = 1.5});

    //swing into goal
    leftMotors.move(-127);
    rightMotors.move(40); //TODO: tune

    while(chassis.getPose().theta > -150) {
        pros::delay(10);
    } 
    
    //start scoring early within 40deg of target
    trapdoorState = 1;
    intakeState = 1;

    while(chassis.getPose().theta > -160) {
        pros::delay(10);
    }

    //start reversing angular dir and reverse into long within 20 deg
    rightMotors.move(-127);
    leftMotors.move(-60); //prev 80
    pros::delay(500);

    //dsr in long
    chassis.turnToHeading(180, 1000);
    chassis.setPose(1, -1, 180);
    chassis.distanceReset('L', 'F');
    scraperState = 0;

    //wing
    chassis.moveDistance(4, 1000, {.minSpeed = 100});
    chassis.swingToHeading(310, lemlib::DriveSide::RIGHT, 1000, {.direction = lemlib::AngularDirection::CW_CLOCKWISE, .minSpeed = 100, .earlyExitRange = 10, .coast = false});
    chassis.turnToHeading(360, 1000, {.minSpeed = 30, .earlyExitRange = 6}); //prev 4
    chassis.moveToPoint(33, -17, 1000, {.minSpeed = 100});
    intakeState = 0;

    //move to ml
    pros::delay(3000);
    wingState = 1;
    trapdoorState = 0;
    intakeState = 1;
    chassis.turnToHeading(0, 1000);
    chassis.moveDistance(-24, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 4});
    chassis.setPose(1, -1, chassis.getPose().theta);
    chassis.swingToHeading(180, lemlib::DriveSide::RIGHT, 1000, {.direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE, .coast = false});
    chassis.distanceReset('L', 'F');
    scraperState = 1;
    chassis.moveToPose(47.5, -57, 180, 1000, {.minSpeed = 127 * 0.8});
    chassis.sendVoltage(12000 * 0.8, 500);

    //go to low goal
    chassis.moveDistance(-6, 1000);
    chassis.distanceReset('L', 'F');
    scraperState = 0;
    chassis.turnToHeading(315, 1000);
    chassis.moveToPoint(8, -14, 2000, {.minSpeed = 100, .earlyExitRange = 20});
    chassis.moveToPose(8, -14, 315, 2000, {.maxSpeed = 30, .earlyExitRange = 2}, true);
    intakeState = 2;

    return;
}