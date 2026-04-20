#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"

//hi this is aakanksh im doing it
void nineBallRight() {
    
    //dist reset
    chassis.setPose(1, -1, 0);
    chassis.distanceReset('R', 'B');

    //block grab 3
    intakeState = 3;
    wingState = 1;
    chassis.moveToPoint(22.5, -26.5, 1000, {.minSpeed = 127, .earlyExitRange = 7}, true);
    chassis.waitUntil(17);
    scraperState = 1;
    chassis.waitUntilDone();

    //block grab 2
    chassis.turnToHeading(15, 1000, {.minSpeed = 30, .earlyExitRange = 2}); //20
    chassis.moveToPose(38.5, -6.5, -284, 1000, {.lead = 0.32, .maxSpeed = 60}, true);
    chassis.waitUntil(5);
    scraperState = 0;
    chassis.waitUntilDone();
    chassis.moveDistance(4, 500, {.minSpeed = 60});
    scraperState = 1;
    pros::delay(200);
    chassis.moveDistance(-4, 500, {.forwards = false});
    chassis.moveDistance(5, 500, {.forwards = false});
    //chassis.turnToHeading(95, 500);

    //go to long
    chassis.swingToHeading(0, lemlib::DriveSide::RIGHT, 1000, {});
    chassis.distanceReset('R', 'B');
    chassis.moveToPoint(37, -21, 1000, {.forwards = false, .minSpeed = 80, .earlyExitRange = 4});
    chassis.swingToHeading(180, lemlib::DriveSide::RIGHT, 1000, {.minSpeed = 80});
    leftMotors.move_voltage(-6000);
    rightMotors.move_voltage(-6000);
    intakeState = 1;
    trapdoorState = 1;
    pros::delay(1100);
    chassis.setPose(1,-1,chassis.getPose().theta);
    chassis.distanceReset('L', 'F');

    //go to ml
    trapdoorState = 0;
    chassis.moveToPoint(46, -48, 1000, {.minSpeed = 60, .earlyExitRange = 4});
    chassis.turnToHeading(180, 1000);
    chassis.moveDistance(4, 1000, {.minSpeed = 127 * 0.5});
    chassis.sendVoltage(4000, 700);
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('R', 'F');

    //go to low goal
    chassis.moveDistance(-6.5, 1000);
    chassis.distanceReset('L', 'F');
    scraperState = 0;
    chassis.turnToPoint(11, -16.5, 1000);
    //chassis.turnToHeading(-48, 1000);
    chassis.moveToPose(11, -16.5, 312, 2000, {.minSpeed = 80, .earlyExitRange = 4});
    //chassis.moveToPose(10, -14, 315, 1000, {.maxSpeed = 30, .earlyExitRange = 4});
    chassis.turnToHeading(-48, 1000);
    intakeState = 2;

}   