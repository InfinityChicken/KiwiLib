#include "autonomous/autonomous.hpp"
#include "pros/motors.h"

//og
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
    //chassis.turnToHeading(-40, 1000, {.minSpeed = 100, .earlyExitRange = 5});
    chassis.turnToPoint(-35, -27, 1000, {.forwards = false, .minSpeed = 100, .earlyExitRange = 15}); //eer prev 20
    //chassis.turnToHeading(-75, 1000, {.minSpeed = 100, .earlyExitRange = 50}); //TODO: tune prev 45
    //chassis.turnToHeading(-75, 1000, {.maxSpeed = 40, .minSpeed = 10, .earlyExitRange = 4}); //TODO: tune
    chassis.moveToPoint(-39, -25.5, 1000, {.forwards = false, .minSpeed = 80, .earlyExitRange = 4});
    // intakeState = 0;
    // trapdoorState = 1;

    //swing into goal
    rightMotors.move_voltage(-12000);
    leftMotors.move(-20); //TODO: tune
    //pros::delay(700);
    //leftMotors.move(20);

    while(std::fabs(chassis.getPose().theta - 180) > 22) { //+180 because robot is at negative 180 when sitting in long
        if(std::fabs(chassis.getPose().theta - 180) > 55)
            leftMotors.move(20);
        pros::delay(10);
    } //start scoring early within 20deg of target
    trapdoorState = 1;
    intakeState = 1;

    while(std::fabs(chassis.getPose().theta - 180) > 40) { //exit when close
        pros::delay(10);
    }
    //chassis.turnToHeading(180, 250);
    leftMotors.move(-127);
    rightMotors.move(-127);
    pros::delay(300);
    // chassis.moveDistance(-10, 300, {.forwards = false, .minSpeed = 100});

    //dsr in long
    chassis.turnToHeading(180, 250);
    chassis.setPose(-1, -1, chassis.getPose().theta);
    chassis.distanceReset('R', 'F');
    scraperState = 0;

   //left wing
    chassis.turnToHeading(135, 500, {.minSpeed = 60, .earlyExitRange = 4});
    chassis.moveToPoint(-41.5, -36, 1000, {.minSpeed = 100, .earlyExitRange = 4});
    //chassis.moveDistance(7.5, 1000, {.minSpeed = 100, .earlyExitRange = 4});
    chassis.turnToHeading(178, 500, {.minSpeed = 60});
    chassis.moveToPoint(-38.5, -12, 1000, {.forwards = false, .minSpeed = 80});
    //chassis.moveDistance(-22, 1000, {.forwards = false, .minSpeed = 60});
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
    chassis.moveToPose(-41.5, -61, 180, 1000, {.lead = 0.4});
    chassis.moveDistance(15, 500, {.minSpeed = 127 * 0.7});
    pros::delay(50);
    chassis.distanceReset('R', 'F');

    //go to mid goal
    chassis.moveDistance(-7, 500, {.forwards = false, .minSpeed = 80, .earlyExitRange = 3});
    chassis.moveToPose(-12, -7, 220, 2000, {.forwards = false, .lead = 0.5, .minSpeed = 80});
    chassis.moveDistance(-8, 500, {.forwards = false});
    chassis.turnToHeading(225, 500, {}, true);
    scraperState = 0;
    //chassis.turnToHeading(320, 1000, {.earlyExitRange = 2});
    //chassis.moveToPoint(19, -19, 1000, {.minSpeed = 80}, true);
    //chassis.waitUntil(5);
    intakeState = 4;

    return;
   
    // //dsr
    // chassis.setPose(-1, -1, 270);
    // chassis.distanceReset('F', 'L');
    // intakeState = 1;
    // wingState = 1;

    // //move to and do ml
    // scraperState = 1;
    // chassis.moveToPoint(-46, chassis.getPose().y, 1000, {.minSpeed = 100, .earlyExitRange = 5});
    // chassis.moveToPoint(-46, chassis.getPose().y, 1000, {.maxSpeed = 60});
    // wingState = 0;
    // chassis.turnToHeading(178, 1000);
    // chassis.moveDistance(10, 1000, {.minSpeed = 127 * 0.5});
    // chassis.sendVoltage(6000, 300);
    // chassis.turnToHeading(180, 1000);
    // chassis.distanceReset('R', 'F');

    // //score long
    // chassis.moveToPoint(-46, -27, 1000, {.forwards = false, .minSpeed = 100, .earlyExitRange = 8});
    // chassis.moveToPoint(-46, -27, 1000, {.forwards = false, .maxSpeed = 80}, true);
    // chassis.waitUntil(5);
    // intakeState = 3;
    // trapdoorState = 1;
    // chassis.waitUntilDone();
    // chassis.sendVoltage(-12000 * 0.5, 500);
    // chassis.distanceReset('R', 'F');
    // scraperState = 0;

    // //wing
    // chassis.moveToPoint(-36, -36, 1000, {.minSpeed = 80});
    // trapdoorState = 0;
    // chassis.turnToHeading(180, 1000, {.minSpeed = 80});
    // chassis.moveToPoint(-36, -11, 1000, {.forwards = false, .minSpeed = 60});

    // //delay and exit long
    // pros::delay(3000);
    // intakeState = 1;
    // wingState = 1;
    // chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    // chassis.turnToPoint(-21, -24, 1000);
    // chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

    // //block grab
    // chassis.moveToPoint(-21, -24, 1000, {}, true);
    // chassis.waitUntil(4);
    // scraperState = 1;
    // chassis.waitUntilDone();

    // //score mid
    // chassis.turnToHeading(215, 1000);
    // scraperState = 0;
    // chassis.moveToPoint(-2, -7, 1000, {.forwards = false, .maxSpeed = 60});
    // intakeState = 4;
}