#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void skills() {
    //beginning dist reset
    chassis.setPose(-1, -1, 0);
    chassis.distanceReset('L', 'B');

    //curve to four blocks + intake
    intakeState = 1;
    chassis.moveToPoint(-24, -24, 1500, {}, true);
    chassis.waitUntil(12);
    scraperState = 1;
    chassis.waitUntilDone();

    //turn + move toward mid goal
    chassis.turnToPoint(-9, -9, 1000, {.forwards = false});
    chassis.moveToPoint(-9, -9, 1000, {.forwards = false});
    
    //score mid goal
    midGoalState = 1;
    trapdoorState = 1;
    pros::delay(1250); //tune
    midGoalState = 0;
    trapdoorState = 0;
    scraperState = 1;
    
    //move to and do first  ml (copy from sawp)
    chassis.moveToPose(-45.5, -46.5, 225, 2000);
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('R', 'F');
    chassis.moveDistance(13, 1000);
    pros::delay(500);

    //go thru alley
    chassis.moveDistance(-6, 1000);
    chassis.moveToPose(-60, 0, 0, 1000, {.forwards = false}); //minspeed
    chassis.moveToPose(-48, 36, 0, 1000, {.forwards = false});

    return;

    //score long
    chassis.turnToHeading(180, 1000);
    chassis.moveToPoint(-48, 25, 1000, {.forwards = false});

    //move to and do second ml
    chassis.moveToPose(-46, 46, 180, 1000, {.lead = 0.8, .minSpeed = 20});
    chassis.moveToPoint(-46, 60, 1000);
    

}

void sevenBlockPushRight() {
    chassis.setPose(1,-1,0);
    chassis.distanceReset('R', 'B'); //dist reset to begin

    //go to 3 blocks (tuned)
    intakeState = 1;
    chassis.moveToPoint(24, -24, 1000, {.earlyExitRange = 6}, true);
    chassis.waitUntil(12);
    scraperState = 1;

    //go to and into matchloader (tuned)
    chassis.moveToPose(46.5, -46.5, 180, 1500, {.lead = 0.3});
    chassis.distanceReset('L', 'F');
    //chassis.moveToPoint(47, -57, 1000);
    chassis.moveDistance(13, 1000);
    pros::delay(250);

    //back into long goal and score (tuned)
    chassis.moveToPoint(48, -25, 1000, {.forwards = false, .minSpeed = 70});
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(100); //antijam
    intakeState = 1;
    pros::delay(1150); //lower if deadzones are gone

    //curve out and push (tuned)
    scraperState = 0;
    chassis.moveToPoint(38, -36, 775, {});
    chassis.turnToHeading(0, 650, {.earlyExitRange = 10});
    chassis.moveDistance(33, 1000);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.turnToHeading(-23, 1000, {.minSpeed = 40});
    
};

void sevenBlockPushLeft(){
    chassis.setPose(-1,-1,0);
    chassis.distanceReset('L','B'); //dist reset to begin

    //go to 3 blocks
    wingState = 1;
    intakeState = 1;
    chassis.moveToPoint(-24, -24, 1000, {.earlyExitRange = 6}, true);
    chassis.waitUntil(12);
    scraperState = 1;

    //go to and into matchloader
    chassis.moveToPose(-42.5, -46.5, 180, 1500, {.lead = 0.2});
    chassis.distanceReset('R', 'F');
    chassis.moveDistance(14, 1000, {.maxSpeed = 50});
    pros::delay(250);

    //back into long goal and score
    chassis.moveToPoint(-48, -25, 1000, {.forwards = false, .minSpeed = 70});
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(100); //antijam
    intakeState = 1;
    pros::delay(1150); //lower if deadzones are gone

    //curve out and push
    wingState = 0;
    scraperState = 0;
    chassis.moveToPoint(-38.5, -36, 1000);
    chassis.turnToHeading(180, 1000, {.earlyExitRange = 10});
    chassis.moveToPoint(-35, -6, 1000, {.forwards = false, .minSpeed = 10});
    // chassis.moveDistance(33, 1000, {.forwards = false});
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}

void SAWP() {
    // intakeState = 2;
    // pros::delay(100); //antijam
    // intakeState = 1;
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
    pros::delay(900); //prev 750
    scraperState = 0;
    intakeState = 0;

    //swing out right
    chassis.sendVoltage(4000, 250);
    chassis.swingToPoint(22.5, -24, lemlib::DriveSide::RIGHT, 1000);
    trapdoorState = 0;

    //move to first mid blocks
    intakeState = 1;
    chassis.moveToPoint(22.5, -24, 1250, {}, true);
    chassis.waitUntil(8);
    scraperState = 1;

    //turn and get second blocks
    chassis.turnToPoint(-24, -24, 1000); //TODO: this shouldn't work but it does so wtv
    scraperState = 0;
    chassis.moveToPoint(-19, -22, 1500, {}, true);
    chassis.waitUntil(37);
    scraperState = 1;

    // score mid goal
    chassis.waitUntilDone();
    chassis.turnToHeading(225,1000);
    chassis.moveToPoint(-12, -12, 1000, {.forwards = false, .minSpeed = 60});
    midGoalState = 1;
    trapdoorState = 1;
    midGoalSpeed = 12000;
    pros::delay(500);
    intakeState = 2; //outtake to bring blocks farther down intake
    pros::delay(150);
    intakeState = 0;
    midGoalSpeed = 12000 * 0.6;
    trapdoorState = 0;
    midGoalState = 0;

    // move to ml and reset
    chassis.moveToPoint(-46.5, -46.5, 2000);
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('R', 'F');

    //do ml
    intakeState = 1;
    chassis.moveDistance(13, 1000);
    pros::delay(200);

    //score long goal
    chassis.moveToPoint(-48, -25, 1000, {.forwards = false});
    trapdoorState = 1;
}