#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"

//hi this is aakanksh im doing it
void auroraAuto() {
    
    //dist reset
    chassis.setPose(-1, -1, 0);
    chassis.distanceReset('L', 'B');

    //block grab 3
    intakeState = 3;
    wingState = 1;
    chassis.moveToPoint(-22.5, -26.5, 1000, {.minSpeed = 127, .earlyExitRange = 2}, true);
    chassis.waitUntil(17);
    scraperState = 1;
    chassis.waitUntilDone();

    //go to ml
    chassis.moveToPose(-48, -60, 180, 1500, {.minSpeed = 60, .earlyExitRange = 4});
    chassis.sendVoltage(6000, 400);
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('R', 'F');
    
    //go to mid goal
    // chassis.moveDistance(-10, 1000, {.minSpeed = 60, .earlyExitRange = 4});
    // chassis.turnToPoint(0, 0, 1000, {.minSpeed = 30, .earlyExitRange = 4});
    // chassis.moveToPoint(-12, -12, 1000, {.minSpeed = 60, .earlyExitRange = 4});
    chassis.moveToPose(-12, -12, 220, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 4});
    chassis.turnToHeading(225, 1000, {.minSpeed = 30, .earlyExitRange = 4});
    intakeState = 4;
    pros::delay(400);

    //wing out long
    intakeState = 1;
    chassis.moveToPoint(-36, -36, 1000, {.minSpeed = 60, .earlyExitRange = 4});
    chassis.turnToHeading(178, 1000, {.minSpeed = 30, .earlyExitRange = 2});
    chassis.moveToPoint(-36, -12, 1000, {.forwards = false, .minSpeed = 80, .earlyExitRange = 4});
    wingState = 0;
    chassis.moveToPoint(-36, -48, 1000, {.minSpeed = 60, .earlyExitRange = 4});

    //score long
    chassis.moveToPose(-48, -25, 180, 1000, {.minSpeed = 60, .earlyExitRange = 4});
    trapdoorState = 0;
    rightMotors.move(-127);
    leftMotors.move(-60); //prev 80
    pros::delay(500);
    chassis.setPose(-1, -1, chassis.getPose().theta);
    chassis.distanceReset('R', 'F');
    
    //descore mid
    chassis.moveToPoint(-48, -36, 1000);
    chassis.turnToPoint(0, 0, 1000);
    midDescoreState = 1;


}   