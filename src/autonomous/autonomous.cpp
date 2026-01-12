#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void sevenBlockLow() {
    chassis.setPose(-1,-1,0);
    chassis.distanceReset('B','R'); //dist reset to begin
    
    //go to 3 blocks
    intakeState = 1;
    chassis.turnToPoint(21.6, -24, 1000);
    chassis.moveToPoint(21.6, -24, 1000);

    //go to low goal and score
    chassis.turnToPoint(12,-12, 1000);
    chassis.moveToPoint(12, -12, 1000);
    lowGoalVel = true;
    intakeState = 2;
    pros::delay(500);
    lowGoalVel = false;
    intakeState = 1;

    //go to matchloader
    chassis.moveToPoint(45, -43, 1000);
    chassis.turnToHeading(180, 1000);
    chassis.moveDistance(15, 1000);
    pros::delay(250);

    //score long goal
    chassis.moveToPoint(48, -25, 1000, {.forwards = false});
    trapdoorState = 1;

    //wing
    chassis.sendVoltage(6000,250);
    wingState = 1;
    chassis.moveToPose(60,-16,0,1000);
    wingState = 0;
    chassis.moveDistance(10, 1000);
}

void SAWP() {
    chassis.setPose(0,0,90);

    //go to matchloader 
    scraperState = 1;
    chassis.moveDistance(30.5, 1000); //changed from 30
    chassis.turnToHeading(180, 1000);

    //reset pose
    chassis.setPose(10, -10, chassis.getPose().theta); //set quadrant and angle
    chassis.waitUntilDone();
    chassis.distanceReset('L', 'F');
    //if(chassis.getPose().y <= -60) chassis.setPose(46, -46, chassis.getPose().theta);

    //go into matchloader
    intakeState = 1;
    chassis.moveDistance(11.25, 1000);
    pros::delay(125);
    
    //move to long goal and reset
    chassis.moveToPoint(48, -25, 1000, {.forwards = false}); //max speed 80 then 100 prev
    trapdoorState = 1;
    intakeState = 1;
    // float tempY = chassis.getPose().y;
    // chassis.distanceReset('L', 'F'); //* test without this reset
    // if(chassis.getPose().y<=-32) chassis.setPose(chassis.getPose().x, tempY, chassis.getPose().theta);

    //score long goal
    pros::delay(900); //TODO: decrease
    scraperState = 0;
    //intakeState = 0;
    trapdoorState = 0;

    //swing out right
    chassis.sendVoltage(4000, 250);
    chassis.swingToPoint(21.6, -24, lemlib::DriveSide::RIGHT, 1000);

    //move to first mid blocks
    intakeState = 1;
    chassis.moveToPoint(21.6, -24, 1250, {}, true);
    //chassis.waitUntil(4);
    //scraperState = 1;

    //turn and get second blocks
    //chassis.waitUntilDone();
    chassis.turnToPoint(-24, -24, 1000);
    // float tempX = chassis.getPose().x;
    // chassis.distanceReset('B', 'L'); //probably hits long goal
    // chassis.setPose(tempX, chassis.getPose().y, chassis.getPose().theta);
    // chassis.waitUntilDone();
    //scraperState = 0;
    chassis.moveToPoint(-20, -24, 1500, {}, true);
    chassis.waitUntil(38);
    scraperState = 1;

    // score mid goal
    chassis.turnToPoint(-12, -12, 1000, {.forwards = false});
    chassis.moveToPoint(-12, -12, 1000, {.forwards = false, .minSpeed = 60});
    midGoalState = 1;
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(100); //antijam
    intakeState = 1;
    pros::delay(700);
    intakeState = 2; //outtake to avoid spewing balls

    // go to match loader
    chassis.moveToPoint(-46, -43, 2000, {}, true);
    pros::delay(250);
    intakeState = 0;
    trapdoorState = 0;
    midGoalState = 0;
    chassis.turnToHeading(180, 1000);
    intakeState = 1;
    //chassis.distanceReset('R', 'F');

    chassis.moveDistance(15.5, 1000);
    pros::delay(250);

    //score long goal
    chassis.moveToPoint(-48, -25, 1000, {.forwards = false, .maxSpeed = 80});
    trapdoorState = 1;
    // intakeState = 2;
    // pros::delay(100); //antijam
    // intakeState = 1;
}