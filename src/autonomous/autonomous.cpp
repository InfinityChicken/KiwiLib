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
    chassis.distanceReset('L', 'F');
    pros::delay(1000);
    scraperState = 0;

    //go back and get blocks before mid goal
    chassis.swingToPoint(23.56, -27.84, lemlib::DriveSide::RIGHT, 1500);
    trapdoorState = 0;
    chassis.moveToPoint(22.56, -26.84, 1250, {}, true);
    pros::delay(150);
    scraperState = 1;
    chassis.turnToPoint(-17, -24, 1000);
    scraperState = 0;
    chassis.moveToPoint(-17, -24, 1500, {}, true);
    pros::delay(580);
    scraperState = 1;

    // score mid goal
    chassis.turnToPoint(-8,-10, 1000, {.forwards = false});
    chassis.moveToPoint(-8, -10, 1000, {.forwards = false});
    midGoalState = 1;
    trapdoorState = 1;
    pros::delay(1000);
    trapdoorState = 0;

    // // score other long goal
    // chassis.moveToPoint(-48, -47, 2000);
    // midGoalState = 0;
    // chassis.turnToHeading(180, 1000);
    // chassis.distanceReset('R', 'F');
    // chassis.moveToPoint(-48, -25, 1000, {.forwards = false});
    // trapdoorState = 1;
    // chassis.moveToPoint(-48, -25, 1000, {.forwards = false});
    // pros::delay(2000);
}