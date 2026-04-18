#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"
#include <chrono>

//reflect blindcode
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
    chassis.turnToHeading(-30, 1000, {.minSpeed = 100, .earlyExitRange = 15});
    chassis.moveToPoint(39, -30, 1000, {.forwards = false, .minSpeed = 80});

    //swing into goal
    leftMotors.move(-127);
    rightMotors.move(10); //TODO: tune

    while(chassis.getPose().theta > -160) {
        pros::delay(10);
    } //start scoring early within 20deg of target
    trapdoorState = 1;
    intakeState = 1;

    while(std::fabs(chassis.getPose().theta + 180) > 12) { //exit when close
        pros::delay(10);
    }

    //reverse into long
    rightMotors.move(-127);
    leftMotors.move(-60); //prev 80
    pros::delay(700);

    //dsr in long
    chassis.turnToHeading(180, 1000);
    chassis.setPose(1, -1, 180);
    chassis.distanceReset('L', 'F');
    scraperState = 0;

    //wing
    chassis.moveDistance(4, 1000, {.minSpeed = 100});
    chassis.swingToHeading(310, lemlib::DriveSide::RIGHT, 1000, {.direction = lemlib::AngularDirection::CW_CLOCKWISE, .minSpeed = 100, .earlyExitRange = 10, .coast = false});
    chassis.turnToHeading(360, 1000, {.minSpeed = 30, .earlyExitRange = 6}); //prev 4
    chassis.moveToPoint(32.5, -15.5, 1000, {.minSpeed = 100}); //TODO: tune
    intakeState = 0;

    //move to ml
    pros::delay(3000);
    wingState = 1;
    trapdoorState = 0;
    intakeState = 1;
    chassis.turnToHeading(0, 1000, {.minSpeed = 60, .earlyExitRange = 2});
    chassis.distanceReset('R', 'B');
    chassis.moveToPoint(33.6, -35, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 4});
    chassis.swingToPoint(48, -54, lemlib::DriveSide::RIGHT, 1000, {.minSpeed = 60, .earlyExitRange = 5});
    chassis.distanceReset('L', 'F');
    scraperState = 1;
    chassis.moveToPose(47, -58, 180, 1000, {.minSpeed = 80, .earlyExitRange = 5});
    chassis.moveDistance(9, 500, {.minSpeed = 127 * 0.7});
    pros::delay(25);
    chassis.distanceReset('L', 'F');

    //go to low goal
    chassis.moveToPose(19, -18, 140, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 4});
    scraperState = 0;
    chassis.turnToHeading(315, 1000, {.earlyExitRange = 2});
    return;
    chassis.moveToPoint(19.4, -19.8, 1000, {.minSpeed = 80}, true);
    chassis.waitUntil(5);
    intakeState = 2;

    return;

    // //dsr
    // chassis.setPose(1, -1, 90);
    // chassis.distanceReset('F', 'R');
    // intakeState = 1;
    // wingState = 1;

    // //move to and do ml
    // scraperState = 1;
    // chassis.moveToPoint(46, chassis.getPose().y, 1000, {.minSpeed = 100, .earlyExitRange = 5});
    // chassis.moveToPoint(46, chassis.getPose().y, 1000, {.maxSpeed = 60});
    // wingState = 0;
    // chassis.turnToHeading(182, 1000);
    // chassis.moveDistance(10, 1000, {.minSpeed = 127 * 0.5});
    // chassis.sendVoltage(6000, 400); //prev 350
    // chassis.turnToHeading(180, 1000);
    // chassis.distanceReset('L', 'F');

    // //score long
    // chassis.moveToPoint(48, -25, 1000, {.forwards = false, .minSpeed = 80}); //prev minspeed 100
    // intakeState = 3;
    // trapdoorState = 1;
    // chassis.sendVoltage(-12000 * 0.3, 700); //prev voltage 50%
    // chassis.setPose(1, -1, chassis.getPose().theta);

    //code for starting in long
    //  chassis.setPose(1, -1, 180);
    //  chassis.distanceReset('L', 'F');
    //  scraperState = 0;


    // //old wing
    // chassis.sendVoltage(12000, 150);
    // chassis.moveToPoint(35.25, -40, 1000, {.minSpeed = 60, .earlyExitRange = 4});
    // chassis.turnToHeading(-10, 500, {.minSpeed = 60, .earlyExitRange = 2});
    // chassis.moveToPoint(33.5, -13, 1000);
    // chassis.turnToHeading(-15, 1000, {.minSpeed = 110});
    // chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

    // //delay and exit long
    // pros::delay(3000);
    // intakeState = 1;
    // wingState = 1;
    // chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    // chassis.moveDistance(-5, 1000, {.forwards = false});
    // chassis.turnToPoint(21, -24, 1000);

    // //block grab
    // chassis.moveToPoint(21, -24, 1000, {}, true);
    // chassis.waitUntil(4); //tune
    // scraperState = 1;
    // chassis.waitUntilDone();

    // //score mid
    // chassis.turnToHeading(-45, 1000);
    // scraperState = 0;
    // chassis.moveToPoint(2, -7, 1000, {.maxSpeed = 60});
    // intakeState = 2;
}