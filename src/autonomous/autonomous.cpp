#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void sevenBlockPushRight() {
    chassis.setPose(1,-1,0);
    chassis.distanceReset('R','B'); //dist reset to begin

    //go to 3 blocks
    wingState = 1;
    intakeState = 1;
    //chassis.turnToPoint(22.1, -23, 1000);
    chassis.moveToPoint(22.1, -23, 1000, {});
    scraperState = 1; //asynch this please

    //go to matchloader
    chassis.turnToPoint(47, -45, 1000);
    chassis.moveToPoint(47, -45, 1000);
    chassis.turnToHeading(180, 1000);

    // go into matchloader
    chassis.distanceReset('L', 'F');
    chassis.moveToPoint(47, -58.5, 1000);
    pros::delay(200);

    //back into long goal and score
    chassis.moveToPoint(47, -25, 1000, {.forwards = false});
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(100); //antijam
    intakeState = 1;
    pros::delay(1250); //lower if deadzones are gone

    //curve out
    scraperState = 0;
    chassis.sendVoltage(4000, 250);
    chassis.swingToPoint(41, -17, lemlib::DriveSide::RIGHT, 1000);
    trapdoorState = 0;

    //push
    wingState = 0; //make this asynch pls
    chassis.moveDistance(30, 1000);
    chassis.turnToHeading(-25, 1000);



    




};

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
    chassis.moveDistance(31, 1000); 
    chassis.turnToHeading(180, 1000);

    //reset pose
    chassis.setPose(10, -10, chassis.getPose().theta); //set quadrant and angle
    chassis.waitUntilDone();
    chassis.distanceReset('L', 'F');

    //go into matchloader
    intakeState = 1;
    chassis.moveDistance(11.75, 1000);
    pros::delay(225);
    
    //do long goal
    chassis.moveToPoint(48, -25, 1000, {.forwards = false});
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(100); //antijam
    intakeState = 1;
    pros::delay(750);
    scraperState = 0;
    trapdoorState = 0;

    //swing out right
    chassis.sendVoltage(4000, 250);
    chassis.swingToPoint(24, -24, lemlib::DriveSide::RIGHT, 1000);

    //move to first mid blocks
    chassis.moveToPoint(24, -24, 1250, {}, true);
    chassis.waitUntil(7);
    scraperState = 1;

    //turn and get second blocks
    //chassis.waitUntilDone();
    chassis.turnToPoint(-24, -24, 1000);
    scraperState = 0;
    chassis.moveToPoint(-19, -22, 1500, {}, true);
    chassis.waitUntil(37); //TODO: tune coord
    scraperState = 1;

    // score mid goal
    chassis.waitUntilDone();
    //chassis.turnToPoint(-12, -12, 1000, {.forwards = false});
    chassis.turnToHeading(225,1000);
    chassis.moveToPoint(-12, -12, 1000, {.forwards = false, .minSpeed = 60});
    midGoalState = 1;
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(100); //antijam
    intakeState = 1;
    pros::delay(500);
    midGoalSpeed = 12000 * 0.8;
    pros::delay(100);
    intakeState = 2; //outtake to avoid spewing balls

    

    // do ml
    //chassis.moveToPoint(-45, chassis.getPose().y+(-45-chassis.getPose().x)*tan(chassis.getPose(true).theta), 2000, {}, true); //go straight back but make sure x is -45
    //chassis.moveToPoint(-45, -48, 2000, {}, true);
    chassis.moveToPose(-48, -48, 225, 2000, {.minSpeed = 72}, true);
    pros::delay(200);
    intakeState = 0;
    trapdoorState = 0;
    midGoalState = 0;
    chassis.turnToHeading(180.5, 1000);
    intakeState = 1;
    chassis.distanceReset('R', 'F');
    chassis.moveDistance(12, 1000);
    pros::delay(200);

    //score long goal
    chassis.moveToPoint(-48, -25, 1000, {.forwards = false});
    intakeState = 2;
    pros::delay(100); //antijam
    intakeState = 1;
    trapdoorState = 1;
}