#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"

//TODO: don't forget the freaking 

void fourPlusThreeLeftReflected() {
    // //dist reset
    // chassis.setPose(-1, -1, 0);
    // chassis.distanceReset('L', 'B');

    // //block grab 3
    // intakeState = 3;
    // wingState = 1;
    // chassis.moveToPoint(-23.5, -25.5, 1000, {.minSpeed = 50}, true);
    // chassis.waitUntil(17);
    // scraperState = 1;
    // wingState = 0;

    // //go to long goal
    // chassis.turnToPoint(-48, -38, 1000, {.minSpeed = 60});
    // chassis.moveToPoint(-48, -38, 1000);
    // chassis.turnToHeading(180, 1000, {.minSpeed = 60});
    // chassis.distanceReset('R', 'F');
    // chassis.moveToPoint(-47.5, -26, 1000, {.forwards = false, .minSpeed = 100});

    // //score
    // trapdoorState = 1;
    // intakeState = 1;
    // rightMotors.move(-60);
    // leftMotors.move(-60); //prev 80
    // pros::delay(600);

    //dsr in long
    // chassis.setPose(-1, -1, chassis.getPose().theta);
    chassis.setPose(-1, -1, 180);
    chassis.distanceReset('R', 'F');
    scraperState = 0;

    //left wing
    chassis.moveDistance(4, 1000, {.minSpeed = 60});
    chassis.swingToHeading(90, lemlib::DriveSide::LEFT, 1000, {.direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE, .coast = false});
    chassis.moveDistance(5, 1000);
    chassis.turnToHeading(180, 500, {.minSpeed = 60});
    // chassis.moveToPoint(-41.5, -36, 1000, {.minSpeed = 60});
    // chassis.turnToHeading(178, 500, {.minSpeed = 60});
    // chassis.moveToPoint(-38.5, -12, 1000, {.forwards = false, .minSpeed = 80});
    // chassis.turnToHeading(180, 1000);

    return;

    //move to ml
    pros::delay(1000); //very important delay //2500 before
    wingState = 1;
    trapdoorState = 0;
    intakeState = 1;
    chassis.turnToHeading(0, 1000);
    chassis.moveDistance(-24, 1000, {.forwards = false, .minSpeed = 80}); //TODO: prev 60
    chassis.moveToPoint(-44.5, -48, 1000, {.forwards = false, .maxSpeed = 80}); //blindcode
    chassis.turnToHeading(-182, 1000);
    chassis.setPose(-1, -1, chassis.getPose().theta); 
    chassis.distanceReset('R', 'F');
    scraperState = 1;
    chassis.moveToPoint(-47, -56, 1000, {.minSpeed = 127 * 0.6});
    chassis.turnToHeading(180, 1000); //TODO: consider
    chassis.sendVoltage(12000 * 0.6, 600);

    return;

    //go to low goal
    chassis.moveDistance(-7, 1000, {.forwards = false});
    chassis.distanceReset('R', 'F');
    scraperState = 0;
    chassis.turnToPoint(-10, 12, 1000);
    chassis.moveToPoint(-10, -12, 2000, {.maxSpeed = 80, .earlyExitRange = 3}, true);
    chassis.waitUntil(45);
    intakeState = 2;

    return;
}

//TUNED
void fourPlusThreeLeft() {
    //dist reset
    chassis.setPose(-1, -1, 0);
    chassis.distanceReset('L', 'B');

    //block grab 3
    intakeState = 3;
    wingState = 1;
    chassis.moveToPoint(-23.5, -25.5, 1000, {.minSpeed = 50}, true);
    chassis.waitUntil(17);
    scraperState = 1;
    wingState = 0;

    //go to long goal
    chassis.turnToPoint(-48, -38, 1000, {.minSpeed = 60});
    chassis.moveToPoint(-48, -38, 1000);
    chassis.turnToHeading(180, 1000, {.minSpeed = 60});
    chassis.distanceReset('R', 'F');
    chassis.moveToPoint(-47.5, -26, 1000, {.forwards = false, .minSpeed = 100});

    //score
    trapdoorState = 1;
    intakeState = 1;
    rightMotors.move(-60);
    leftMotors.move(-60); //prev 80
    pros::delay(600);

    //dsr in long
    chassis.setPose(-1, -1, chassis.getPose().theta);
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
    pros::delay(2000);
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