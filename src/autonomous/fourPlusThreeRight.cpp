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
    chassis.turnToPoint(39, -33, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 5}); //prev 60
    chassis.moveToPoint(39, -29, 1000, {.forwards = false, .minSpeed = 80, .earlyExitRange = 1.5});

    //swing into goal
    leftMotors.move(-127);
    rightMotors.move(10); //prev 40

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
    chassis.swingToHeading(340, lemlib::DriveSide::RIGHT, 1000, {.direction = lemlib::AngularDirection::CW_CLOCKWISE, .minSpeed = 100, .earlyExitRange = 10, .coast = false});
    chassis.turnToHeading(5, 1000, {.direction = lemlib::AngularDirection::CW_CLOCKWISE, .minSpeed = 30, .earlyExitRange = 6}); //prev 4
    chassis.moveToPoint(34, -17, 1000, {.minSpeed = 100});
    chassis.turnToHeading(-15, 1000, {.minSpeed = 100});
    intakeState = 0;

    //move to ml
    pros::delay(2500); //very important delay
    wingState = 1;
    trapdoorState = 0;
    intakeState = 1;
    chassis.turnToPoint(27.5, -31, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 5});
    chassis.moveToPoint(27.5, -31, 1000, {.forwards = false, .minSpeed =  80}); //blindcode
    chassis.moveToPoint(46.5, -48, 1000, {.forwards = false}); //blindcode
    chassis.turnToHeading(180, 1000);
    chassis.setPose(1, -1, chassis.getPose().theta);
    chassis.distanceReset('L', 'F');
    scraperState = 1;
    chassis.moveToPoint(46.5, -56, 1000, {.minSpeed = 127 * 0.4});
    chassis.sendVoltage(12000 * 0.4, 700);

    //go to low goal
    chassis.moveDistance(-7, 1000);
    chassis.distanceReset('L', 'F');
    scraperState = 0;
    chassis.turnToPoint(10, -14, 1000);
    chassis.moveToPose(10, -14, 315, 2000, {.maxSpeed = 80, .earlyExitRange = 2});
    intakeState = 2;

    return;
}