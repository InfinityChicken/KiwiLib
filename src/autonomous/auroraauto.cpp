#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"

//hi this is aakanksh im doing it this is left im silly
void auroraAuto() {
    
    //dist reset
    chassis.setPose(-1, -1, 0);
    chassis.distanceReset('L', 'B');

    //block grab
    intakeState = 3;
    wingState = 1;
    chassis.moveToPoint(-24, -23, 1000, {.minSpeed = 90, .earlyExitRange = 9}, true);
    chassis.waitUntil(14);
    scraperState = 1;
    chassis.waitUntilDone();
    chassis.turnToHeading(-120, 500, {.minSpeed = 70});

    //go to ml
    chassis.moveToPose(-47, -58, 180, 1500, {.horizontalDrift = 50, .lead = 0.32});
    chassis.turnToHeading(178, 1000, {.minSpeed = 20});
    chassis.moveDistance(8, 1000, {.minSpeed = 127 * 0.6});
    chassis.sendVoltage(12000 * 0.6, 300);
    pros::delay(300);

    //dsr
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('R', 'F');
        
    //go to mid goal
    chassis.moveDistance(-7, 500, {.forwards = false, .minSpeed = 80, .earlyExitRange = 3});
    chassis.distanceReset('R', 'F');
    //chassis.turnToHeading(218, 500, {.minSpeed = 80, .earlyExitRange = 3});
    chassis.moveToPose(-9, -12 , 220, 2000, {.forwards = false, .lead = 0.45, .minSpeed = 80});
    chassis.moveDistance(-6, 500, {.forwards = false});
    chassis.turnToHeading(225, 500, {}, true);
    scraperState = 0;
    intakeState = 4;
    pros::delay(800);
    intakeState = 1;

    //wing out long
    chassis.moveToPoint(-26, -40, 1000, {.minSpeed = 60, .earlyExitRange = 4});
    chassis.turnToHeading(178, 1000, {.minSpeed = 30, .earlyExitRange = 2});
    chassis.distanceReset('R', 'F');
    chassis.moveToPoint(-32, -13, 1000, {.forwards = false});
    chassis.turnToHeading(180, 1000);
    wingState = 0;
    chassis.distanceReset('R', 'F');
    chassis.moveToPoint(-36, -48, 1000, {.minSpeed = 60, .earlyExitRange = 4});

    //score long
    chassis.moveToPoint(-48, -25, 1000, {.forwards = false, .minSpeed = 60});
    trapdoorState = 1;
    rightMotors.move(-127);
    leftMotors.move(-80);
    pros::delay(500);
    intakeState = 3;
    pros::delay(500);
    chassis.setPose(-1, -1, chassis.getPose().theta);
    chassis.distanceReset('R', 'F');
    
    //descore mid
    // chassis.moveToPoint(-48, -38, 1000, {.minSpeed = 60, .earlyExitRange = 4});
    chassis.moveToPoint(-48, -49., 1000);
    chassis.distanceReset('R', 'F');
    midDescoreState = 1;
    chassis.turnToHeading(234, 1000);
    chassis.moveToPoint(-12, -10, 2000, {.forwards = false});
}