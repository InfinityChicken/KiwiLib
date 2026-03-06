#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/timer.hpp"
#include "pros/distance.hpp"
#include "main.h"
#include "drivecode/util.hpp"


void skills97() {
    //beginning dist reset
    chassis.setPose(-1, -1, 0);
    chassis.distanceReset('L', 'B');

    //intake first four blocks
    wingState = 1;                    
    intakeState = 3;
    chassis.moveToPoint(-20.5, -27, 1500, {}, true);
    chassis.waitUntil(18.5);
    intakeState = 0;
    chassis.waitUntilDone();

    //turn and move toward mid goal
    chassis.turnToHeading(-135, 1000);
    intakeState = 3;
    chassis.moveToPoint(-6.7, -11.9, 1000, {.forwards = false}); //prev -8.5 -11.5
    
    //score mid goal
    midGoalState = 1;
    intakeState = 2;
    pros::delay(100);
    intakeState = 1;
    pros::delay(700);

    if(interrupt) {
        return;
    }

    //move and dist reset before first ml
    scraperState = 1; 
    chassis.moveDistance(38, 2000, {.minSpeed = 80, .earlyExitRange = 5});
    //chassis.moveToPoint(-26, -43, 1000);
    chassis.turnToHeading(270, 1000);
    chassis.distanceReset('F', 'L');

    //trapdoor up and mid goal down
    midGoalState = 0;
    intakeState = 3;

    //move forward and turn in front of first ml
    chassis.moveToPoint(-45, chassis.getPose().y, 1000);
    chassis.turnToHeading(180, 1000);

    //do first ml
    chassis.moveDistance(15.5, 1000, {.minSpeed = 30}); //prev 15, no minspeed
    pros::delay(750);
    intakeState = 2;
    pros::delay(100);
    intakeState = 3;
    
    //jitter first ml
    chassis.sendVoltage(-6000, 100);
    chassis.sendVoltage(4000, 700);

    if(interrupt) {
        return;
    }

    //go thru alley
    intakeState = 0;
    chassis.sendVoltage(6000,200);
    chassis.moveToPose(-63.5, -28, 0, 1000, {.forwards = false, .minSpeed = 40, .earlyExitRange = 5});
    chassis.moveToPoint(-58.25, 25, 2000, {.forwards = false, .minSpeed = 127});
    chassis.distanceReset('R', 'B');
    
    //exit alley and move into first long goal
    chassis.moveToPoint(-49, 32, 1000, {.forwards = false});
    chassis.turnToHeading(0, 1000, {.direction = AngularDirection::CW_CLOCKWISE});
    chassis.distanceReset('L', 'F');
    chassis.moveToPoint(-48, 25, 1000, {.forwards = false, .minSpeed = 60});
    leftMotors.move(-50); //push into long goal
    rightMotors.move(-50);

    //score long
    intakeState = 2; // anti jam
    pros::delay(125);
    intakeState = 1;
    pros::delay(1750); // score //prev 2350 scoring 
    intakeState = 3;
    leftMotors.move(0);
    leftMotors.move(0);
    chassis.turnToHeading(0, 500);
    chassis.distanceReset('L', 'F');

    if(interrupt) {
        return;
    }

    //move to second ml
    chassis.moveToPose(-46, 46, 0, 1000, {.minSpeed = 90, .earlyExitRange = 8});

    //do second ml
    chassis.moveDistance(13.5, 1000, {.minSpeed = 30}); //prev 18
    pros::delay(750);
    intakeState = 2;
    pros::delay(100);
    intakeState = 3;

    //jitter second ml
    chassis.sendVoltage(-6000, 100);
    chassis.sendVoltage(4000, 1000);

    //score long
    intakeState = 0;
    chassis.moveToPoint(-47, 25, 1000, {.forwards = false, .maxSpeed = 65});
    leftMotors.move(-50); //push into long goal
    rightMotors.move(-50);
    chassis.distanceReset('L', 'F');
    intakeState = 2; // anti jam
    pros::delay(125);
    intakeState = 1;
    pros::delay(1750); // score previously 2350
    leftMotors.move(0);
    leftMotors.move(0);
    scraperState = 0;


    if(interrupt) {
        return;
    }



	//move to park
	chassis.moveToPose(-11, 63, 87, 2000, {.lead = 0.58}, true); //curve to park zone
    intakeState = 2; // anti jam
    pros::delay(125);
    intakeState = 1;
    chassis.turnToHeading(90, 250);
    if(distBack.get_distance() / 25.4 >= 44) {
        chassis.moveDistance(2, 500);
    } 
	odomState = 1; //odom up
    pros::delay(100);
	scraperState = 1; 
	pros::delay(200);

    //use scraper to push blocks
	chassis.sendVoltage(6000, 400); //7500
    scraperState = 0;
    intakeState = 3;
	pros::delay(175);

    //initial cross
    leftMotors.move_voltage(8000);
	rightMotors.move_voltage(8400);
    pros::delay(500);

	//pause in park zone
    leftMotors.move_voltage(0);
	rightMotors.move_voltage(0);
    pros::delay(750);

    //go slower out of park
    leftMotors.move_voltage(7000);
	rightMotors.move_voltage(7400);
    pros::delay(800);

	//cross and go to matchloader to intake all blocks
	while (true) {
        if (distFrontRight.get_distance() / 25.4 <= 35) {
            leftMotors.move_voltage(0);
			rightMotors.move_voltage(0);
			break;
        } else {
			leftMotors.move_voltage(4500);
			rightMotors.move_voltage(4700); //prev 10000
		}
        pros::delay(10);
    } 
	pros::delay(300);

	//back up from ml
	chassis.moveDistance(-16, 1000, {.forwards = false});
    odomState = 0;

    if(interrupt) {
        return;
    }

	//mid goal
	chassis.swingToHeading(196, lemlib::DriveSide::RIGHT, 1000);
	chassis.distanceReset('L', 'B');

	//get one more block
    //chassis.turnToHeading(195, 1000); //187 before
	//chassis.moveToPoint(19, 19.75, 1500); //19, 19.75
	chassis.moveToPose(19, 19.25, 195, 1000, {.lead = 0});
    intakeState = 0;

    //turn and move toward mid goal
    chassis.turnToPoint(-7, -1, 1000, {.forwards = false});
    //chassis.turnToHeading(45, 1000);
	intakeState = 3;
	//chassis.moveToPoint(7.3, 12.3, 1000, {.forwards = false, .minSpeed = 60}, true);
    chassis.moveDistance(-8.5, 1000, {.forwards = false, .minSpeed = 60});
	//pros::delay(500);
    midGoalState = 1;
	chassis.turnToHeading(45, 1000, {}, true);
    intakeState = 2; // anti jam
    pros::delay(125);
    intakeState = 1;
    pros::delay(2350); // score
	intakeState = 0;

    if(interrupt) {
        return;
    }

	//veryyyy slowly go out
	chassis.moveDistance(3, 1000, {.maxSpeed = 10});
	chassis.moveDistance(-2.75, 1000, {.maxSpeed = 5});
	//go to third matchloader
	scraperState = 1;
	chassis.moveDistance(38, 2000, {.minSpeed = 80, .earlyExitRange = 5});
	//chassis.moveToPose(34.6, 46.7, 90, 2000, {.lead = 0.62});
	chassis.turnToHeading(90, 1000, {.minSpeed = 30});
	chassis.distanceReset('F', 'L');
	chassis.moveToPoint(47, chassis.getPose().y, 1500, {}, true);
	pros::delay(500);
	midGoalState = 0; //do states
	intakeState = 3;
	chassis.waitUntilDone();
	intakeState = 3;
	chassis.turnToHeading(0, 1000);
    chassis.distanceReset('R', 'F');

    //do third ml
    chassis.moveDistance(15.75, 1000);
    pros::delay(750);
    intakeState = 2;
    pros::delay(100);
    intakeState = 3;

    //jitter third ml
    // chassis.moveDistance(-6, 100);
    // chassis.moveDistance(7.5, 750);
    // pros::delay(400);
    chassis.sendVoltage(-6000, 100);
    chassis.sendVoltage(4000, 1000);
    intakeState = 0;
    
    if(interrupt) {
        return;
    }

    //go around long goal in alley
    chassis.sendVoltage(-6000, 150);
    chassis.moveToPose(60, 29, 0, 1000, {.forwards = false, .minSpeed = 40, .earlyExitRange = 5}); // booster by 1 x
    chassis.moveToPoint(59, -28, 1500, {.forwards = false, .minSpeed = 127, .earlyExitRange = 5}); // booster by 1 x

    //move to long goal
    chassis.moveToPoint(47, -45, 2000, {.forwards = false});
    chassis.turnToHeading(180, 1000, {.direction = AngularDirection::CW_CLOCKWISE});
    chassis.distanceReset('L', 'F');
    chassis.moveToPoint(48, -25, 1000, {.forwards = false, .minSpeed = 60});
    leftMotors.move(-50); //push into long goal
    rightMotors.move(-50);
    // chassis.moveToPoint(48, -20, 1000, {.forwards = false, .maxSpeed = 60}, true); //make sure the bot keeps pushing forward to actually align

    //score long goal
    intakeState = 3;
    intakeState = 1;
    intakeState = 2; // anti jam
    pros::delay(125);
    intakeState = 1;
    pros::delay(1750); // score //previously 2350
    leftMotors.move(0);
    rightMotors.move(0);
    chassis.turnToHeading(180, 500);
    chassis.distanceReset('L', 'F');
    intakeState = 3;

    if(interrupt) {
        return;
    }

    //move to fourth ml
    chassis.moveToPose(47, -45, 180, 1000, {.minSpeed = 90, .earlyExitRange = 8});
    //chassis.turnToHeading(180, 1000);

    //do fourth ml
    chassis.moveDistance(16.5, 1000);
    pros::delay(750);
    intakeState = 2;
    pros::delay(100);
    intakeState = 3;

    //jitter fourth ml
    // chassis.moveDistance(-6, 100);
    // chassis.moveDistance(7.5, 750);
    // pros::delay(400);
    chassis.sendVoltage(-6000, 100);
    chassis.sendVoltage(4000, 1000);
    intakeState = 0;

    //score long
    chassis.moveToPoint(48, -25, 1000, {.forwards = false, .maxSpeed = 65});
    leftMotors.move(-50);
    rightMotors.move(-50);
    // chassis.moveToPoint(48, -20, 1000, {.forwards = false, .maxSpeed = 60}, true);
    intakeState = 1;
    intakeState = 2; // anti jam
    pros::delay(125);
    intakeState = 1;
    pros::delay(1700); // score //previously 2350
    leftMotors.move(0);
    rightMotors.move(0);
    chassis.distanceReset('L', 'F');
    scraperState = 0;

    if(interrupt) {
        return;
    }

    //move to park
    chassis.moveToPose(11, -63.5, -87, 2000, {.lead = 0.58}, true); //curve to park zone
    intakeState = 1;
    chassis.turnToHeading(270, 250);
    if(distBack.get_distance() / 25.4 >= 44) {
        chassis.moveDistance(2, 500);
    } 
	odomState = 1; //odom up
    pros::delay(10);
	scraperState = 1; 
	pros::delay(200);

    //use scraper to push blocks
	chassis.sendVoltage(6000, 420); //7500
    scraperState = 0;
	pros::delay(175);

    //initial cross
    leftMotors.move_voltage(8000);
	rightMotors.move_voltage(8200);
    pros::delay(650);

	//pause in park zone
    leftMotors.move_voltage(0);
	rightMotors.move_voltage(0);
    pros::delay(750);

    // chassis.moveToPose(13.5, -62.25, 267, 2000, {.lead = 0.58});
    // chassis.turnToHeading(270, 250);
    // if(distBack.get_distance() / 25.4 >= 44) {
    //     chassis.moveDistance(2, 500);
    // } 
    
    // //chassis.moveDistance(2, 1000, {.minSpeed = 40});
    // scraperState = 1;
    // intakeState = 1;
    // odomState = 1;
	// pros::delay(100);
    // chassis.sendVoltage(10000, 250);
	// scraperState = 0;
	// pros::delay(100);
    // //chassis.sendVoltage(9000,750); //prev 10000
    // leftMotors.move_voltage(8000);
	// rightMotors.move_voltage(8400);
    // pros::delay(350);

    if(interrupt) {
        return;
    }

    // leftMotors.move_voltage(9000); //prev 9500
	// rightMotors.move_voltage(10000); //prev 10000
    // pros::delay(1500);
    // chassis.sendVoltage(0, 10);

    // lemlib::Timer timer(500);

    // while (!timer.isDone()) {
    //     if (distBack.get_distance() / 25.4 >= 64 && distBack.get_distance() / 25.4 < 100 || distFrontRight.get_distance() / 25.4 <= 65 && distFrontRight.get_distance() / 25.4 >= 50) {
    //         std::cout<<"back: "<<distBack.get_distance() / 25.4<<"     front: "<<distFrontRight.get_distance() / 25.4<<"\n";
    //         std::cout<<"stopped\n";
    //         leftMotors.move_voltage(0);
	// 		rightMotors.move_voltage(0);
    //         timer.set(0);
	// 		break;
    //     } else {
	// 		std::cout<<"back: "<<distBack.get_distance() / 25.4<<"     front: "<<distFrontRight.get_distance() / 25.4<<"\n";
    //         leftMotors.move_voltage(8000); //prev 9500
	// 		rightMotors.move_voltage(8400); //prev 10000
	// 	}
    //     pros::delay(10);
    // }  
    // chassis.sendVoltage(-6000, 250);

}

void sevenBlockPushRight() {
    chassis.setPose(1,-1,0);
    chassis.distanceReset('R', 'B'); //dist reset to begin

    //go to 3 blocks (tuned)
    intakeState = 3;
    wingState = 1;
    chassis.moveToPoint(24, -24, 1000, {.earlyExitRange = 6}, true);
    chassis.waitUntil(12);
    scraperState = 1;

    //go to and into matchloader (tuned)
    chassis.moveToPose(49.5, -46.5, 180, 1875, {.horizontalDrift = 60, .lead = 0.3});
    chassis.distanceReset('L', 'F');
    //chassis.moveToPoint(47, -57, 1000);
    chassis.moveDistance(13, 1000);
    pros::delay(25);
    intakeState = 0;
    pros::delay(25);
    intakeState = 3;
    pros::delay(75);
    intakeState = 0;

    //back into long goal and score (tuned)
    chassis.moveToPoint(48, -25, 1000, {.forwards = false, .minSpeed = 60});
    chassis.moveToPoint(48, -20, 1000, {.forwards = false, .maxSpeed = 80}, true);
    intakeState = 1;
    chassis.distanceReset('L', 'F');
    pros::delay(1500); //prev 1500
    
    //curve out and push (tuned)
    intakeState = 0;
    scraperState = 0;
    wingState = 0;
    chassis.sendVoltage(6000, 200);
    chassis.moveToPoint(37.75, -38, 1000, {});
    chassis.turnToHeading(0, 1000);
    chassis.moveDistance(28, 1000);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.turnToHeading(-17, 1000, {.minSpeed = 40});
    
}

void sevenBlockPushLeft(){
    chassis.setPose(-1,-1,0);
    chassis.distanceReset('L','B'); //dist reset to begin

    //go to 3 blocks
    wingState = 1;
    intakeState = 3;
    chassis.moveToPoint(-24, -24, 1000, {.earlyExitRange = 6}, true);
    chassis.waitUntil(12);
    scraperState = 1;

    //go to and into matchloader
    chassis.moveToPose(-45, -46.5, 180, 1500, {.lead = 0.2});
    chassis.waitUntilDone();
    chassis.distanceReset('R', 'F');
    chassis.moveDistance(16, 1000);
    pros::delay(350);
    intakeState = 0;

    //back into long goal and score
    chassis.turnToHeading(180, 250);
    chassis.moveToPoint(-48, -25, 1000, {.forwards = false, .minSpeed = 70});
    chassis.moveToPoint(-48, -20, 1000, {.forwards = false, .maxSpeed = 100}, true);
    intakeState = 1;
    chassis.distanceReset('R', 'F');
    pros::delay(1600);

    //curve out and push
    intakeState = 0;
    wingState = 0;
    scraperState = 0;
    //chassis.sendVoltage(6000, 100);
    chassis.moveToPoint(-38, -36, 1000, {}, true);
    intakeState = 2;
    pros::delay(40);
    intakeState = 0;
    chassis.turnToHeading(180, 1000);
    chassis.moveToPoint(-35, -8, 1000, {.forwards = false, .maxSpeed = 100});
    // chassis.moveDistance(33, 1000, {.forwards = false});
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}

void fourBlockPushRight() {
    chassis.setPose(1,-1,0);
    chassis.distanceReset('R', 'B'); //dist reset to begin

    //go to 3 blocks
    intakeState = 3;
    chassis.moveToPoint(24, -24, 1000, {.earlyExitRange = 6}, true);
    chassis.waitUntil(12);
    scraperState = 1;

    //go in front of goal
    chassis.moveToPose(47.5, -46.5, 180, 1875, {.lead = 0.3});
    chassis.distanceReset('L', 'F');

    //back into long goal and score
    chassis.moveToPoint(48, -25, 1000, {.forwards = false, .minSpeed = 70});
    chassis.moveToPoint(48, -20, 1000, {.forwards = false, .maxSpeed = 80}, true);
    intakeState = 1;
    intakeState = 3;
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

void fourBlockPushLeft() {
    chassis.setPose(-1,-1,0);
    chassis.distanceReset('L','B'); //dist reset to begin

    //go to 3 blocks
    wingState = 1;
    intakeState = 3;
    chassis.moveToPoint(-24, -24, 1000, {.earlyExitRange = 6}, true);
    chassis.waitUntil(12);
    scraperState = 1;

    //go in front of long goal
    chassis.moveToPose(-43.5, -46.5, 180, 1500, {.lead = 0.2});
    chassis.distanceReset('R', 'F');

    //back into long goal and score
    chassis.moveToPoint(-48, -25, 1000, {.forwards = false, .minSpeed = 70});
    chassis.moveToPoint(-48, -20, 1000, {.forwards = false, .maxSpeed = 80}, true);
    intakeState = 1;
    intakeState = 3;
    pros::delay(1600);

    //curve out and push
    wingState = 0;
    scraperState = 0;
    //chassis.sendVoltage(6000, 100);
    chassis.moveToPoint(-38.15, -36, 1000);
    chassis.turnToHeading(180, 1000);
    intakeState = 3;
    chassis.moveToPoint(-35, -6, 1000, {.forwards = false, .maxSpeed = 100});
    // chassis.moveDistance(33, 1000, {.forwards = false});
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}
void leftSplitPush() {
    chassis.setPose(-1, -1,270);
    chassis.distanceReset('F', 'L');

    //go to matchloader 
    scraperState = 1;
    wingState = 1;
    chassis.moveToPoint(-46, chassis.getPose().y, 1000);
    //chassis.moveDistance(29, 1000); //prev 31.25

    chassis.turnToHeading(180, 1000);

    //reset pose
    chassis.setPose(-10, -10, chassis.getPose().theta); //set quadrant and angle
    chassis.waitUntilDone();
    chassis.distanceReset('R', 'F');

    //go into matchloader
    intakeState = 3;
    chassis.moveDistance(13.5, 1000);
    pros::delay(40);
    
    //do long goal
    chassis.turnToHeading(180, 250);
    chassis.moveToPoint(-47, -25, 1000, {.forwards = false});
    intakeState = 1;
    pros::delay(750);
    chassis.distanceReset('R', 'F');

    //swing out left
    scraperState = 0;
    //chassis.sendVoltage(4000, 250);
    chassis.moveDistance(3, 1000);
    chassis.swingToPoint(-20.75, -21.75, lemlib::DriveSide::LEFT, 1000);
    chassis.distanceReset('L', 'B');
    intakeState = 3;

    //move to first mid blocks
    intakeState = 3;
    chassis.moveToPoint(-20.75, -21.75, 1500, {}, true);
    chassis.waitUntil(10.5);
    scraperState = 1;
    chassis.waitUntilDone();
    scraperState = 0;

    //score mid
    midGoalState = 1;
    chassis.turnToHeading(228, 1000);
    //chassis.turnToPoint(-8, -10, 1000, {.forwards = false});
    chassis.moveDistance(-15.5, 1000, {.forwards = false});
    intakeState = 1;
    intakeState = 2; //antijam
    pros::delay(50);
    intakeState = 1;
    pros::delay(950);

    //push mid with descore
    chassis.moveDistance(7, 1000, {}, true);
    chassis.waitUntil(4);
    midDescoreState = 1;
    chassis.moveDistance(-4, 1000, {.forwards = false});

    //go to wing position and wing
    chassis.moveToPoint(-33.5, -36, 1000, {}, true);
    midDescoreState = 0;
    intakeState = 2;
    wingState = 0;
    pros::delay(40);
    intakeState = 0;
    //chassis.turnToHeading(180, 1000);
    chassis.turnToPoint(-36.5, -13.7, 1000, {.forwards = false});
    chassis.moveToPoint(-36.5, -13.7, 1000, {.forwards = false, .maxSpeed = 80});
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}

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
    intakeState = 3;
    chassis.moveDistance(13.5, 1000);
    pros::delay(25); //prev 50, 100
    intakeState = 0;
    
    //do long goal
    chassis.moveToPoint(48, -25, 1000, {.forwards = false, .minSpeed = 60});
    chassis.moveToPoint(48, -20, 1000, {.forwards = false, .maxSpeed = 90}, true);
    intakeState = 1;
    intakeState = 3;
    pros::delay(700);
    scraperState = 0;
    //intakeState = 0;

    //swing out right
    chassis.sendVoltage(4000, 250);
    chassis.swingToPoint(23.5, -21, lemlib::DriveSide::RIGHT, 1000); //prev -23
    intakeState = 3;

    //move to first mid blocks
    intakeState = 3;
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
    intakeState = 1;
    // intakeState = 2; 
    intakeState = 3;
    intakeState = 2; //antijam
    pros::delay(50);
    intakeState = 3;
    pros::delay(660);

    //move to ml
    scraperState = 1;
    chassis.moveToPose(-49, -46, 230, 1500, {}, true); //prev theta 225
    intakeState = 2; //outtake to bring blocks farther down intake
    pros::delay(80); 
    intakeState = 0;
    intakeState = 3;
    midGoalState = 0;

    // turn and reset
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('R', 'F');

    //do ml
    intakeState = 3;
    midGoalState = 1;
    chassis.moveDistance(13.25, 1000);
    pros::delay(25); //prev 80, 100
    midGoalState = 0;
    //intakeState = 0;

    //score long goal
    chassis.moveToPoint(-48, -25, 1000, {.forwards = false, .minSpeed = 60});
    chassis.moveToPoint(-48, -20, 1000, {.forwards = false, .maxSpeed = 90}, true);
    intakeState = 1;
    // intakeState = 2;
    // pros::delay(50);
    intakeState = 3;
}

void counterSAWP() {
    chassis.setPose(0,0, 90);

    //go to matchloader
    wingState = 1;
    scraperState = 1;
    chassis.moveDistance(31.25, 1000); 
    chassis.turnToHeading(180, 1000);

    //reset pose
    chassis.setPose(10, -10, chassis.getPose().theta); //set quadrant and angle
    chassis.waitUntilDone();
    chassis.distanceReset('L', 'F');

    //go into matchloader
    intakeState = 3;
    chassis.moveDistance(14.5, 1000); //prev 13.5
    pros::delay(10); //prev 25. 50, 100
    
    //move into long goal
    chassis.moveToPoint(48, -25, 1000, {.forwards = false, .minSpeed = 60});
    leftMotors.move(-50); //push into goal
    rightMotors.move(-50);

    //score long goal
    intakeState = 2;
    pros::delay(50);
    intakeState = 1;
    pros::delay(700);
    chassis.distanceReset('L', 'F');
    scraperState = 0; 

    //swing out right
    chassis.distanceReset('L', 'F');
    chassis.sendVoltage(4000, 300); //sometimes hits long goal increase and tune, prev 250
    chassis.swingToPoint(24, -23, lemlib::DriveSide::RIGHT, 1000); //prev -23
    intakeState = 3;

    //chain to first mid blocks
    //chassis.moveToPose(23.5, -21, 270, 1500, {.horizontalDrift = 1000, .minSpeed = 60}, true);
    chassis.moveToPoint(21.5, -23, 1000, {.minSpeed = 60, .earlyExitRange = 4}, true); //prev 23.5
    chassis.waitUntil(10.5);
    scraperState = 1;
    
    //chain to second mid blocks
    chassis.turnToPoint(-24, -26, 1000, {.minSpeed = 60, .earlyExitRange = 4});
    chassis.moveToPoint(-24, -25, 1500, {.minSpeed = 60, .earlyExitRange = 4}, true);
    chassis.waitUntil(2);
    scraperState = 0;
    chassis.waitUntil(28);
    scraperState = 1;

    //chain to long goal
    chassis.moveToPose(-50, -53 , 180, 2000, {.horizontalDrift = 1000, .lead = 0.4});
    chassis.distanceReset('R', 'F');

    //score long
    chassis.moveToPoint(-48, -25, 1000, {.forwards = false, .minSpeed = 60});
    leftMotors.move(-50); //push into goal
    rightMotors.move(-50);
    intakeState = 2;
    pros::delay(50);
    intakeState = 1;
    pros::delay(700);
    return;
    //do ml
    chassis.distanceReset('R', 'F');
    chassis.moveToPose(-46.5, -45, 180, 1000);
    intakeState = 3;
    chassis.moveDistance(18, 1000, {.minSpeed = 30});
    pros::delay(10);

    //go to mid goal and score
    chassis.moveDistance(12, 1000, {.forwards = false});
    chassis.distanceReset('R', 'F');
    chassis.turnToPoint(0, 0, 1000, {.forwards = false});
    chassis.moveToPoint(-13, -7, 1500, {.forwards = false});

}