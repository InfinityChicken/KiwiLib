#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/distance.hpp"
#include "main.h"



void skills() {
    //beginning dist reset
    chassis.setPose(-1, -1, 0);
    chassis.distanceReset('L', 'B');

    //intake first four blocks
    intakeState = 1;
    //wingState = 1;
    // chassis.moveToPoint(-20, -25, 1500, {.maxSpeed = 40});
    chassis.moveToPoint(-20, -25, 1500, {.maxSpeed = 60}, true); //-21, -24
    chassis.waitUntil(13.5); //prev 14.25
    scraperState = 1;
    chassis.waitUntilDone();

    //turn and move toward mid goal
    chassis.turnToHeading(-135, 1000);
    chassis.moveToPoint(-8.5, -11.5, 1000, {.forwards = false}); //prev -8.5 -11.5
    scraperState = 1;
    
    //score mid goal
    midGoalState = 1;
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(100);
    intakeState = 1;
    pros::delay(2000);
    
    //first ml
    // velValue = 12000*80;
    //chassis.moveToPose(-48, chassis.getPose().y+(-48-chassis.getPose().x)*tan(chassis.getPose(true).theta), chassis.getPose().theta, 2000);
    //chassis.moveToPoint(-43.5, -39.5, 2000); //move in front of ml
    chassis.moveDistance(40, 1000);
    chassis.turnToHeading(-90, 1000);
    chassis.waitUntilDone();
    chassis.distanceReset('F', 'L');
    chassis.moveToPoint(-44, chassis.getPose().y, 1000);
    midGoalState = 0;
    trapdoorState = 0;
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('R', 'F');
    // chassis.moveToPoint(chassis.getPose().x, -57.5, 1500); //move in straight line
    chassis.moveDistance(19.75, 1000); //move into ml
    pros::delay(1250);
    intakeState = 2;
    pros::delay(100);
    intakeState = 1;
    chassis.moveDistance(-6, 100);
    chassis.moveDistance(7.5, 750);
    pros::delay(400);
    // velValue = 12000;

    //go thru alley
    intakeState = 0;
    chassis.moveDistance(-6, 1000);
    chassis.turnToPoint(-59, -29, 1000, {.forwards = false});
    chassis.moveToPoint(-59, -29, 1000, {.forwards = false});
    chassis.turnToHeading(180, 1000);
    chassis.moveToPoint(-58.25, 26, 2000, {.forwards = false});
    
    //exit alley and score
    chassis.moveToPoint(-44, 45, 1000, {.forwards = false});
    chassis.turnToHeading(0, 1000, {.direction = AngularDirection::CW_CLOCKWISE});
    chassis.distanceReset('L', 'F'); //stop here next run and make sure the coords is good cuz its curving
    chassis.moveToPoint(-48, 25, 1000, {.forwards = false});
    chassis.moveToPoint(-48, 20, 1000, {.forwards = false, .maxSpeed = 60}, true); //make sure the bot keeps pushing forward to actually align
    intakeState = 1;
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(200);
    intakeState = 1;
    pros::delay(2500);

    //second ml
    // velValue = 12000*80;
    trapdoorState = 0;
    chassis.moveToPoint(-46.5, 46, 1000);
    chassis.turnToHeading(0, 1000); 
    chassis.moveDistance(13, 1000);
    pros::delay(1250);
    intakeState = 2;
    pros::delay(100);
    intakeState = 1;
    //pros::delay(650);
    chassis.moveDistance(-6, 100);
    chassis.moveDistance(7.5, 750);
    pros::delay(400);
    // velValue = 12000;
    intakeState = 0;


    //score long
    chassis.moveToPoint(-47, 25, 1000, {.forwards = false});
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(200);
    intakeState = 1;
    pros::delay(2000);

    //third ml
    // velValue = 12000*80;
    chassis.moveDistance(16, 1000);
    chassis.turnToPoint(48, 43, 1000);
    chassis.moveToPoint(48, 43, 3000);
    chassis.turnToHeading(0, 1000);
    trapdoorState = 0;
    chassis.distanceReset('R', 'F');
    chassis.moveDistance(14.5, 1000);
    pros::delay(1250);
    intakeState = 2;
    pros::delay(100);
    intakeState = 1;
    chassis.moveDistance(-6, 100);
    chassis.moveDistance(7.5, 750);
    pros::delay(400);
    // velValue = 12000;


    //go around long goal in alley
    intakeState = 0;
    chassis.moveToPoint(48, 45, 1000, {.forwards = false});
    chassis.turnToPoint(61, 29, 1000, {.forwards = false}); // boosted by 1 x 
    chassis.moveToPoint(61, 29, 1000, {.forwards = false}); // booster by 1 x
    chassis.turnToHeading(0, 1000);
    chassis.moveToPoint(58.5, -28, 1500, {.forwards = false}); // booster by 1 x

    //score long goal after alley
    chassis.moveToPoint(44, -45, 2000, {.forwards = false});
    chassis.turnToHeading(180, 1000, {.direction = AngularDirection::CW_CLOCKWISE});
    chassis.distanceReset('L', 'F'); //stop here next run and make sure the coords is good cuz its curving
    chassis.moveToPoint(48, -25, 1000, {.forwards = false});
    chassis.moveToPoint(48, -20, 1000, {.forwards = false, .maxSpeed = 60}, true); //make sure the bot keeps pushing forward to actually align
    intakeState = 1;
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(200);
    intakeState = 1;
    pros::delay(2000);

    //fourth ml
    // velValue = 12000*80;
    trapdoorState = 0;
    chassis.moveToPoint(46.5, -46, 1000);
    chassis.turnToHeading(180, 1000);
    chassis.moveDistance(14.25, 1000);
    pros::delay(1250);
    intakeState = 2;
    pros::delay(100);
    intakeState = 1;
    //pros::delay(400);
    chassis.moveDistance(-6, 100);
    chassis.moveDistance(7.5, 750);
    pros::delay(400);
    // velValue = 12000;
    intakeState = 0;


    //score long
    chassis.moveToPoint(48, -25, 1000, {.forwards = false, .maxSpeed = 100});
    chassis.distanceReset('L', 'F');
    chassis.moveToPoint(48, -20, 1000, {.forwards = false, .maxSpeed = 60}, true);
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(200);
    intakeState = 1;
    pros::delay(2000);
    scraperState = 0;

    //park
    chassis.moveToPose(13.5, -62.25, 270, 2000, {.lead = 0.68, .maxSpeed = 60});  
    // chassis.moveToPoint(48.1, -46.5, 1000);
    // chassis.turnToPoint(20, -59, 1000);
    // chassis.moveToPoint(20, -62, 1000);
    chassis.turnToHeading(270, 1000);
    chassis.moveDistance(7, 1000, {.minSpeed = 40});
    scraperState = 1;
    intakeState = 2;
    wingState = 1;
    chassis.sendVoltage(6000, 250);
    scraperState = 0;
	pros::delay(100);
    chassis.sendVoltage(10000,500);
    while (true) {
        if (distBack.get_distance() / 25.4 >= 66 && distBack.get_distance() / 25.4 < 100) {
            leftMotors.move_voltage(0);
			rightMotors.move_voltage(0);
			break;
        } else {
			leftMotors.move_voltage(9500);
			rightMotors.move_voltage(12000); //prev 10000
		}
        pros::delay(10);
    }  
    chassis.sendVoltage(-8000, 250);

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
    chassis.moveToPose(47.5, -46.5, 180, 1875, {.lead = 0.3});
    chassis.distanceReset('L', 'F');
    //chassis.moveToPoint(47, -57, 1000);
    chassis.moveDistance(13.5, 1000);
    pros::delay(250);
    intakeState = 0;

    //back into long goal and score (tuned)
    chassis.moveToPoint(48, -25, 1000, {.forwards = false, .minSpeed = 70});
    chassis.moveToPoint(48, -20, 1000, {.forwards = false, .maxSpeed = 80}, true);
    trapdoorState = 1;
    intakeState = 1;
    pros::delay(1500);
    
    //curve out and push (tuned)
    scraperState = 0;
    chassis.sendVoltage(6000, 100);
    chassis.moveToPoint(38.75, -38, 1000, {});
    chassis.turnToHeading(0, 1000);
    chassis.moveDistance(31.75, 1000);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.turnToHeading(-17, 1000, {.minSpeed = 40});
    
}

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
    chassis.moveToPose(-43.5, -46.5, 180, 1500, {.lead = 0.2});
    chassis.waitUntilDone();
    chassis.distanceReset('R', 'F');
    chassis.moveDistance(16, 1000);
    pros::delay(250);
    intakeState = 0;

    //back into long goal and score
    chassis.moveToPoint(-48, -25, 1000, {.forwards = false, .minSpeed = 70});
    chassis.moveToPoint(-48, -20, 1000, {.forwards = false, .maxSpeed = 80}, true);
    trapdoorState = 1;
    intakeState = 1;
    pros::delay(1600);

    //curve out and push
    wingState = 0;
    scraperState = 0;
    //chassis.sendVoltage(6000, 100);
    chassis.moveToPoint(-38.15, -36, 1000, {}, true);
    intakeState = 2;
    pros::delay(40);
    intakeState = 0;
    trapdoorState = 0;
    chassis.turnToHeading(180, 1000);
    trapdoorState = 0;
    chassis.moveToPoint(-35, -5.5, 1000, {.forwards = false, .maxSpeed = 100});
    // chassis.moveDistance(33, 1000, {.forwards = false});
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}


void fourBlockPushLeft() {
    chassis.setPose(-1,-1,0);
    chassis.distanceReset('L','B'); //dist reset to begin

    //go to 3 blocks
    wingState = 1;
    intakeState = 1;
    chassis.moveToPoint(-24, -24, 1000, {.earlyExitRange = 6}, true);
    chassis.waitUntil(12);
    scraperState = 1;

    //go to and into matchloader
    chassis.moveToPose(-43.5, -46.5, 180, 1500, {.lead = 0.2});
    chassis.distanceReset('R', 'F');

    //back into long goal and score
    chassis.moveToPoint(-48, -25, 1000, {.forwards = false, .minSpeed = 70});
    chassis.moveToPoint(-48, -20, 1000, {.forwards = false, .maxSpeed = 80}, true);
    trapdoorState = 1;
    intakeState = 1;
    pros::delay(1600);

    //curve out and push
    wingState = 0;
    scraperState = 0;
    //chassis.sendVoltage(6000, 100);
    chassis.moveToPoint(-38.15, -36, 1000);
    chassis.turnToHeading(180, 1000);
    trapdoorState = 0;
    chassis.moveToPoint(-35, -6, 1000, {.forwards = false, .maxSpeed = 100});
    // chassis.moveDistance(33, 1000, {.forwards = false});
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}

 // intakeState = 2;
    // pros::delay(100); //antijam
    // intakeState = 1;

void SAWP() {
    chassis.setPose(0,0,90);

    //go to matchloader 
    scraperState = 1;
    chassis.moveDistance(31.25, 1000); 
    chassis.turnToHeading(180, 1000);

    //reset pose
    chassis.setPose(10, -10, chassis.getPose().theta); //set quadrant and angle
    chassis.waitUntilDone();
    chassis.distanceReset('L', 'F');

    //go into matchloader
    intakeState = 1;
    chassis.moveDistance(13.5, 1000);
    pros::delay(25); //prev 50, 100
    intakeState = 0;
    
    //do long goal
    chassis.moveToPoint(48, -25, 1000, {.forwards = false, .minSpeed = 60});
    chassis.moveToPoint(48, -20, 1000, {.forwards = false, .maxSpeed = 90}, true);
    trapdoorState = 1;
    intakeState = 1;
    pros::delay(700);
    scraperState = 0;
    //intakeState = 0;

    //swing out right
    chassis.sendVoltage(4000, 250);
    chassis.swingToPoint(23.5, -21, lemlib::DriveSide::RIGHT, 1000); //prev -23
    trapdoorState = 0;

    //move to first mid blocks
    intakeState = 1;
    chassis.moveToPoint(23.5, -21, 1500, {}, true); //prev minspeed 40, prev -23
    chassis.waitUntil(10.5);
    scraperState = 1;
    chassis.waitUntilDone();
    scraperState = 0;

    //turn and get second blocks
    chassis.turnToPoint(-24, -17.75, 1000); //if no work then change ttp to same as mtp
    scraperState = 0;
    chassis.moveToPoint(-24, -17.75, 1500, {.minSpeed = 40}, true); //prev -19.5 y, prev -19 x, prev minspeed 40
    chassis.waitUntil(31);
    scraperState = 1;

    // score mid goal
    chassis.waitUntilDone();
    midGoalState = 1;
    chassis.turnToPoint(-11, -5, 1000, {.forwards = false});
    chassis.moveToPoint(-11, -5, 1000, {.forwards = false, .minSpeed = 60}, true); //pre minspeed 60
    chassis.waitUntil(12);
    trapdoorState = 1;
    // intakeState = 2; 
    intakeState = 1;
    midGoalSpeed = 12000;
    intakeState = 2; //antijam
    pros::delay(50);
    intakeState = 1;
    pros::delay(660);

    //move to ml
    scraperState = 1;
    chassis.moveToPose(-49, -46, 230, 1500, {}, true); //prev theta 225
    intakeState = 2; //outtake to bring blocks farther down intake
    pros::delay(80); 
    intakeState = 0;
    trapdoorState = 0;
    midGoalState = 0;

    // turn and reset
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('R', 'F');

    //do ml
    intakeState = 1;
    midGoalState = 1;
    chassis.moveDistance(13.25, 1000);
    pros::delay(25); //prev 80, 100
    midGoalState = 0;
    //intakeState = 0;

    //score long goal
    chassis.moveToPoint(-48, -25, 1000, {.forwards = false, .minSpeed = 60});
    chassis.moveToPoint(-48, -20, 1000, {.forwards = false, .maxSpeed = 90}, true);
    trapdoorState = 1;
    // intakeState = 2;
    // pros::delay(50);
    intakeState = 1;
}