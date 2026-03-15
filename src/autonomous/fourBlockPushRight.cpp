#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/timer.hpp"
#include "pros/distance.hpp"
#include "main.h"
#include "drivecode/util.hpp"

void fourBlockPushRight() {
    chassis.setPose(1,-1,0);
    chassis.distanceReset('R', 'B'); //dist reset to begin

    //go to 3 blocks
    intakeState = 3;
    chassis.moveToPoint(24, -24, 1000, {.earlyExitRange = 6}, true);
    chassis.waitUntil(12);
    scraperState = 1;

    //go in front of goal
    chassis.moveToPose(47.5, -46.5, 180, 1875, {.lead = 0.3});
    chassis.distanceReset('L', 'F');

    //back into long goal and score
    chassis.moveToPoint(48, -25, 1000, {.forwards = false, .minSpeed = 70});
    chassis.moveToPoint(48, -20, 1000, {.forwards = false, .maxSpeed = 80}, true);
    intakeState = 1;
    intakeState = 3;
    pros::delay(1500);

    //curve out and push (tuned)
    scraperState = 0;
    chassis.sendVoltage(6000, 100);
    chassis.moveToPoint(38.75, -38, 1000, {});
    chassis.turnToHeading(0, 1000);
    chassis.moveDistance(31.75, 1000);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.turnToHeading(-17, 1000, {.minSpeed = 40});

}
