#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/timer.hpp"
#include "pros/distance.hpp"
#include "main.h"
#include "drivecode/util.hpp"

void fourBlockPushLeft() {
    chassis.setPose(-1,-1,0);
    chassis.distanceReset('L','B'); //dist reset to begin

    //go to 3 blocks
    wingState = 1;
    intakeState = 3;
    chassis.moveToPoint(-24, -24, 1000, {.earlyExitRange = 6}, true);
    chassis.waitUntil(12);
    scraperState = 1;

    //go in front of long goal
    chassis.moveToPose(-43.5, -46.5, 180, 1500, {.lead = 0.2});
    chassis.distanceReset('R', 'F');

    //back into long goal and score
    chassis.moveToPoint(-48, -25, 1000, {.forwards = false, .minSpeed = 70});
    chassis.moveToPoint(-48, -20, 1000, {.forwards = false, .maxSpeed = 80}, true);
    intakeState = 1;
    intakeState = 3;
    pros::delay(1600);

    //curve out and push
    wingState = 0;
    scraperState = 0;
    //chassis.sendVoltage(6000, 100);
    chassis.moveToPoint(-38.15, -36, 1000);
    chassis.turnToHeading(180, 1000);
    intakeState = 3;
    chassis.moveToPoint(-35, -6, 1000, {.forwards = false, .maxSpeed = 100});
    // chassis.moveDistance(33, 1000, {.forwards = false});
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}
