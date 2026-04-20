#include "autonomous/autonomous.hpp"
#include "pros/motors.h"

//TUNED
void fourPlusThreeLeft() {
    //dist reset
    chassis.setPose(-1, -1, 0);
    chassis.distanceReset('L', 'B');

    //block grab 3
    intakeState = 3;
    wingState = 1;
    chassis.moveToPoint(-22.5, -26.5, 1000, {.minSpeed = 127, .earlyExitRange = 2}, true);
    chassis.waitUntil(17);
    scraperState = 1;
    wingState = 0;
    chassis.waitUntilDone();
    chassis.turnToPoint(-35, -27, 1000, {.forwards = false, .minSpeed = 100, .earlyExitRange = 15}); //eer prev 20
    chassis.moveToPoint(-39, -25.5, 1000, {.forwards = false, .minSpeed = 80, .earlyExitRange = 4});

    //swing into goal
    rightMotors.move(-127);
    leftMotors.move(10);

    while(chassis.getPose().theta < 160) { //+180 because robot is at negative 180 when sitting in long
        pros::delay(10);
    } 
    
    //start scoring early within 22deg of target
    trapdoorState = 1;
    intakeState = 1;

    //reverse into long
    leftMotors.move(-127);
    rightMotors.move(-60); //prev 80
    pros::delay(700);

    //dsr in long
    chassis.setPose(-1, -1, chassis.getPose().theta);
    //chassis.setPose(-1, -1, 180);
    chassis.distanceReset('R', 'F');
    scraperState = 0;

    //left wing
    chassis.turnToHeading(135, 350, {.minSpeed = 60, .earlyExitRange = 4});
    trapdoorState = 0;
    chassis.moveToPoint(-41.5, -33.75, 1000, {.minSpeed = 100, .earlyExitRange = 4});
    chassis.turnToHeading(178, 500, {.minSpeed = 60});
    chassis.moveToPoint(-38.5, -12, 1000, {.forwards = false, .minSpeed = 80});
    chassis.turnToHeading(180, 1000);

    //move to ml
    pros::delay(3000);
    wingState = 1;
    trapdoorState = 0;
    intakeState = 1;
    //chassis.turnToHeading(180, 1000, {.minSpeed = 60, .earlyExitRange = 2});
    //chassis.distanceReset('R', 'F');

    //chassis.moveToPoint(-33.6, -35, 1000, {.minSpeed = 60, .earlyExitRange = 4});
    //chassis.swingToPoint(48, -54, lemlib::DriveSide::RIGHT, 1000, {.minSpeed = 60, .earlyExitRange = 5});
    //chassis.moveToPoint(48, -40, 1000, {.forwards = false, .minSpeed = 60});
    //chassis.turnToHeading(180, 1000);
    //chassis.distanceReset('R', 'F');
    chassis.moveDistance(14, 1000, {.minSpeed = 100, .earlyExitRange = 4});
    scraperState = 1;
    chassis.moveToPose(-43, -61, 180, 1000, {.lead = 0.4});
    chassis.moveDistance(15, 500, {.minSpeed = 127 * 0.7});
    pros::delay(50);
    chassis.distanceReset('R', 'F');

    //go to mid goal
    //chassis.moveDistance(-7, 500, {.forwards = false, .minSpeed = 80, .earlyExitRange = 3});
    chassis.moveToPose(-12, -10, 225, 2000, {.forwards = false, .minSpeed = 60}); //prev -10, -13
    chassis.moveDistance(-8, 500, {.forwards = false});
    chassis.turnToHeading(225, 500, {}, true);
    scraperState = 0;
    //chassis.turnToHeading(320, 1000, {.earlyExitRange = 2});
    //chassis.moveToPoint(19, -19, 1000, {.minSpeed = 80}, true);
    //chassis.waitUntil(5);
    intakeState = 4; //TODO: lower mid goal speed

    return;
}