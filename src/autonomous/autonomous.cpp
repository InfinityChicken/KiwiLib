#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void skills() {
    //beginning dist reset
    chassis.setPose(-1, -1, 0);
    chassis.distanceReset('L', 'B');

    //curve to four blocks + intake
    intakeState = 1;
    wingState = 1;
    chassis.moveToPoint(-20, -25, 1500, {}, true); //-21, -24
    chassis.waitUntil(12);
    scraperState = 1;
    chassis.waitUntilDone();
    //chassis.moveToPoint(-20, -25, 1000, {.forwards = false});

    //turn + move toward mid goal
    chassis.turnToHeading(225, 1000);
    chassis.moveToPoint(-8.5, -11.5, 1000, {.forwards = false});
    
    //score mid goal
    midGoalState = 1;
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(100);
    intakeState = 1;
    pros::delay(2000); //inconsistent deadzones rn
    
    //move to and do first  ml
    chassis.moveToPoint(-42.25, -40.5, 1000); //-43
    //chassis.moveToPose(-42.5, -40, -131, 2000);
    midGoalState = 0;
    trapdoorState = 0;
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('R', 'F');
    chassis.moveToPoint(chassis.getPose().x, -57.5, 1500); //move in straight line
    //chassis.moveDistance(16.5, 1000);
    pros::delay(1500);

    //go thru alley
    intakeState = 0;
    chassis.moveDistance(-6, 1000);
    chassis.turnToPoint(-59, -29, 1000, {.forwards = false});
    chassis.moveToPoint(-59, -29, 1000, {.forwards = false});
    chassis.turnToHeading(180, 1000);
    chassis.moveToPoint(-57.25, 26, 2000, {.forwards = false});
    
    //exit alley and score
    chassis.moveToPoint(-42.5, 45, 1000, {.forwards = false});
    chassis.turnToHeading(0, 1000, {.direction = AngularDirection::CW_CLOCKWISE});
    chassis.distanceReset('L', 'F'); //stop here next run and make sure the coords is good cuz its curving
    chassis.moveToPoint(-48, 25, 1000, {.forwards = false});
    chassis.moveToPoint(-48, 20, 1000, {.forwards = false, .maxSpeed = 60}, true);
    intakeState = 1;
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(100);
    intakeState = 1;
    pros::delay(1500);

    //move to ml
    trapdoorState = 0;
    chassis.moveToPoint(-47.5, 46, 1000);
    chassis.moveDistance(12.5, 1000);
    pros::delay(1500);

    //score long
    chassis.moveToPoint(-48, 25, 1000, {.forwards = false});
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(100);
    intakeState = 1;
    pros::delay(1500);
    
    //go to third matchloader
    chassis.moveDistance(16, 1000);
    chassis.turnToPoint(47, 43, 1000);
    chassis.moveToPoint(48, 43, 2500);
    chassis.turnToHeading(0,1000);
    trapdoorState = 0;
    chassis.distanceReset('R', 'F');
    chassis.moveDistance(12.75, 1000);
    pros::delay(1500);

    //go around long goal in alley
    intakeState = 0;
    chassis.moveToPoint(48, 45, 1000, {.forwards = false});
    chassis.turnToPoint(60, 29, 1000, {.forwards = false});
    chassis.moveToPoint(60, 29, 1000, {.forwards = false});
    chassis.turnToHeading(0, 1000);
    chassis.moveToPoint(57.5, -28, 1500, {.forwards = false});

    //score long goal after alley
    chassis.moveToPoint(43.5, -45, 1000, {.forwards = false});
    chassis.turnToHeading(180, 1000, {.direction = AngularDirection::CW_CLOCKWISE});
    chassis.distanceReset('L', 'F'); //stop here next run and make sure the coords is good cuz its curving
    chassis.moveToPoint(48, -25, 1000, {.forwards = false});
    chassis.moveToPoint(48, -20, 1000, {.forwards = false, .maxSpeed = 60}, true);
    intakeState = 1;
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(100);
    intakeState = 1;
    pros::delay(1500);

    //move to ml
    trapdoorState = 0;
    chassis.moveToPoint(47, -46, 1000);
    chassis.moveDistance(12.75, 1000);
    pros::delay(1500);

    //score long
    chassis.moveToPoint(48, -25, 1000, {.forwards = false});
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(100);
    intakeState = 1;
    pros::delay(1500);

    //park
    scraperState = 0;
    chassis.moveToPose(17, -61, 250, 2000, {.lead = 0.65}); 
    chassis.sendVoltage(2000, 1000);
    scraperState = 1;
    chassis.moveDistance(12, 1000);
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