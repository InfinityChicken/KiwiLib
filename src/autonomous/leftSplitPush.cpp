#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/timer.hpp"
#include "pros/distance.hpp"
#include "main.h"
#include "drivecode/util.hpp"

void leftSplitPush() {
    chassis.setPose(-1, -1,270);
    chassis.distanceReset('F', 'L');

    //go to matchloader
    scraperState = 1;
    wingState = 1;
    chassis.moveToPoint(-46, chassis.getPose().y, 1000);
    //chassis.moveDistance(29, 1000); //prev 31.25

    chassis.turnToHeading(180, 1000);

    //reset pose
    chassis.setPose(-10, -10, chassis.getPose().theta); //set quadrant and angle
    chassis.waitUntilDone();
    chassis.distanceReset('R', 'F');

    //go into matchloader
    intakeState = 3;
    chassis.moveDistance(13.5, 1000);
    pros::delay(15);

    //do long goal
    chassis.turnToHeading(180, 250);
    chassis.moveToPoint(-47, -25, 1000, {.forwards = false});
    intakeState = 1;
    pros::delay(750);
    chassis.distanceReset('R', 'F');

    //swing out left
    scraperState = 0;
    //chassis.sendVoltage(4000, 250);
    chassis.moveDistance(3, 1000);
    chassis.swingToPoint(-20.75, -21.75, lemlib::DriveSide::LEFT, 1000);
    chassis.distanceReset('L', 'B');
    intakeState = 3;

    //move to first mid blocks
    intakeState = 3;
    chassis.moveToPoint(-20.75, -21.75, 1500, {}, true);
    chassis.waitUntil(10.5);
    scraperState = 1;
    chassis.waitUntilDone();
    scraperState = 0;

    //score mid
    midGoalState = 1;
    chassis.moveDistance(2, 500);
    chassis.turnToHeading(225, 1000);
    //chassis.turnToPoint(-8, -10, 1000, {.forwards = false});
    chassis.moveDistance(-15.5, 1000, {.forwards = false});
    //chassis.turnToHeading(225, 500, {}, true);
    intakeState = 1;
    intakeState = 2; //antijam
    pros::delay(50);
    intakeState = 1;
    pros::delay(950);

    //push mid with descore
    chassis.moveDistance(11, 1000);
    //chassis.waitUntil(4);
    midDescoreState = 1;
    chassis.moveDistance(-7, 1000, {.forwards = false});

    // //go to wing position and wing
    // chassis.moveToPoint(-33.5, -36, 1000, {}, true);
    // midDescoreState = 0;
    // intakeState = 2;
    // wingState = 0;
    // pros::delay(40);
    // intakeState = 0;
    // //chassis.turnToHeading(180, 1000);
    // chassis.turnToPoint(-36.5, -13.7, 1000, {.forwards = false});
    // chassis.moveToPoint(-36.5, -13.7, 1000, {.forwards = false, .maxSpeed = 80});
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}
