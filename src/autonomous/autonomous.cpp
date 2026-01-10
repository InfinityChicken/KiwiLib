#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void sevenBlockLow() {
    chassis.setPose(-1,-1,0);
    chassis.distanceReset('B','R'); //dist reset to begin
    
}

void SAWP() {
    chassis.setPose(0,0,90);
    //go to matchloader
    scraperState = 1;
    intakeState = 1;
    chassis.moveDistance(31,1000);
    chassis.turnToHeading(180, 1250);

    //reset pose
    chassis.setPose(10,-10,chassis.getPose().theta); //set quadrant and angle
    chassis.waitUntilDone();
    chassis.distanceReset('L','F');
    //if(chassis.getPose().y <= -60) chassis.setPose(46, -46, chassis.getPose().theta);

    //go into matchloader
    //chassis.moveToPose(47, -58, 180, 1000);
    chassis.moveDistance(12, 1000);
    pros::delay(250);
    
    //score long goal
    chassis.moveToPoint(48, -25, 1000, {.forwards = false, .maxSpeed = 80});
    trapdoorState = 1;
    //chassis.moveToPoint(48, -25, 250, {.forwards = false, .maxSpeed = 60});
    float tempY = chassis.getPose().y;
    chassis.distanceReset('L', 'F');
    if(chassis.getPose().y<=-32)
        chassis.setPose(chassis.getPose().x, tempY, chassis.getPose().theta);
    pros::delay(1200);
    scraperState = 0;
    intakeState = 0;

    //go back and get first blocks before mid goal
    chassis.sendVoltage(4000, 250);
    chassis.swingToPoint(23.56, -27.84, lemlib::DriveSide::RIGHT, 1500);
    intakeState = 1;
    trapdoorState = 0;
    chassis.moveToPoint(21.56, -24, 1250, {}, true);
    chassis.waitUntil(2);
    scraperState = 1;

    //turn and get second blocks
    chassis.turnToPoint(-17, -21.5, 1000);
    float tempX = chassis.getPose().x;
    chassis.distanceReset('B', 'L');
    chassis.setPose(tempX, chassis.getPose().y, chassis.getPose().theta);
    chassis.waitUntilDone();
    scraperState = 0;
    chassis.moveToPoint(-17, -20.5, 1500, {}, true);
    chassis.waitUntil(38);
    scraperState = 1;

    // score mid goal
    chassis.turnToPoint(-12,-9.3, 1000, {.forwards = false});
    chassis.moveToPoint(-12, -9.3, 1000, {.forwards = false});
    midGoalState = 1;
    trapdoorState = 1;
    pros::delay(1000);
    trapdoorState = 0;

    // go to match loader
    chassis.moveToPoint(-47, -47, 2000);
    midGoalState = 0;
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('R', 'F');
    chassis.moveDistance(12, 1000);
    pros::delay(250);

    //score long goal
    chassis.moveToPoint(-48, -25, 1000, {.forwards = false, .maxSpeed = 80});
    trapdoorState = 1;
    chassis.moveToPoint(-48, -25, 1000, {.forwards = false});
    pros::delay(2000);
}