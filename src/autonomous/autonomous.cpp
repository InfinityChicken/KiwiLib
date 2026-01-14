#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void sevenBlockPushRight() {
    chassis.setPose(1,-1,0);
    chassis.distanceReset('R','B'); //dist reset to begin

    //go to 3 blocks don't touch this
    intakeState = 1;
    chassis.moveToPoint(24, -21, 1000, {.minSpeed = 50, .earlyExitRange = 6}, true);
    chassis.waitUntil(16);
    scraperState = 1;

    //go to and into matchloader don't touch this
    chassis.moveToPose(47, -46.5, 180, 1500, {.lead = 0.3});
    chassis.distanceReset('L', 'F');
    chassis.moveToPoint(47, -58, 1000);
    pros::delay(215);
    intakeState = 0;

    //back into long goal and score PLEASE don't change anything here
    trapdoorState = 1;
    chassis.moveToPoint(48, -25, 1000, {.forwards = false});
    intakeState = 2;
    pros::delay(100); //antijam
    intakeState = 1;
    pros::delay(1150); //lower if deadzones are gone

    //curve out and push
    scraperState = 0;
    chassis.moveToPoint(40.25, -35, 700, {.minSpeed = 60, .earlyExitRange = 3});
    chassis.turnToHeading(0, 825);
    chassis.moveDistance(26, 1000, {.minSpeed = 100});
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.turnToHeading(-30, 1000, {.maxSpeed = 30});
    
};

void sevenBlockPushLeft(){
    chassis.setPose(-1,-1,0);
    chassis.distanceReset('L','B'); //dist reset to begin

    //go to 3 blocks
    intakeState = 1;
    chassis.moveToPoint(-24, -21, 1000, {.earlyExitRange = 6}, true);
    chassis.waitUntil(16);
    scraperState = 1;

    //go to and into matchloader
    chassis.moveToPose(-48, -46.5, 180, 1500, {.lead = 0.05});
    chassis.distanceReset('R', 'F');
    chassis.moveToPoint(-48, -58, 1000);
    pros::delay(200);

    //back into long goal and score
    chassis.moveToPoint(-48, -25, 1000, {.forwards = false});
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(100); //antijam
    intakeState = 1;
    pros::delay(1250); //lower if deadzones are gone
    return;
    //curve out and push
    scraperState = 0;
    chassis.moveToPoint(38.25, -35, 1000);
    chassis.turnToHeading(0, 1000);
    chassis.moveDistance(22, 1000, {.minSpeed = 80});
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.turnToHeading(30, 1000, {AngularDirection::CW_CLOCKWISE});

}

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