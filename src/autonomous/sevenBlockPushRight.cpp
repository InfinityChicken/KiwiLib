#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/timer.hpp"
#include "pros/distance.hpp"
#include "main.h"
#include "drivecode/util.hpp"

void sevenBlockPushRight() {
    chassis.setPose(1,-1,0);
    chassis.distanceReset('R', 'B'); //dist reset to begin

    //go to 3 blocks (tuned)
    intakeState = 3;
    wingState = 1;
    chassis.moveToPoint(24, -24, 1000, {.earlyExitRange = 6}, true);
    chassis.waitUntil(12);
    scraperState = 1;

    //go to and into matchloader (tuned)
    chassis.moveToPose(49.5, -46.5, 180, 1875, {.horizontalDrift = 60, .lead = 0.3});
    chassis.distanceReset('L', 'F');
    //chassis.moveToPoint(47, -57, 1000);
    chassis.moveDistance(13, 1000);
    pros::delay(25);
    intakeState = 0;
    pros::delay(25);
    intakeState = 3;
    pros::delay(75);
    intakeState = 0;

    //back into long goal and score (tuned)
    chassis.moveToPoint(48, -25, 1000, {.forwards = false, .minSpeed = 60});
    chassis.moveToPoint(48, -20, 1000, {.forwards = false, .maxSpeed = 80}, true);
    intakeState = 1;
    chassis.distanceReset('L', 'F');
    pros::delay(1500); //prev 1500

    //curve out and push (tuned)
    intakeState = 0;
    scraperState = 0;
    wingState = 0;
    chassis.sendVoltage(6000, 200);
    chassis.moveToPoint(37.75, -38, 1000, {});
    chassis.turnToHeading(0, 1000);
    chassis.moveDistance(28, 1000);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.turnToHeading(-17, 1000, {.minSpeed = 40});

}
