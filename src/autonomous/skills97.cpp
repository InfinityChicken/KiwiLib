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
    chassis.moveToPoint(-6.7, -11.9, 800, {.forwards = false}); //prev -8.5 -11.5

    //score mid goal
    midGoalState = 1;
    intakeState = 2;
    pros::delay(100);
    intakeState = 1;
    pros::delay(800);

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
    chassis.moveToPoint(-45.5, chassis.getPose().y, 1000);
    chassis.turnToHeading(180, 1000);

    //do first ml
    chassis.moveDistance(16, 1000, {.minSpeed = 30}); //prev 15, no minspeed
    pros::delay(750);
    //intakeState = 2;
    pros::delay(100);
    intakeState = 3;

    //jitter first ml
    chassis.sendVoltage(-6000, 100);
    chassis.sendVoltage(4000, 700);

    if(interrupt) {
        return;
    }

    //go thru alley
    //intakeState = 0;
    chassis.sendVoltage(6000,200);
    chassis.moveToPose(-63.5, -28, 0, 1000, {.forwards = false, .minSpeed = 40, .earlyExitRange = 5});
    scraperState = 0;
    chassis.moveToPoint(-58.25, 25, 2000, {.forwards = false, .minSpeed = 127});
    chassis.distanceReset('R', 'B');

    //exit alley and move into first long goal
    chassis.moveToPoint(-49.5, 32, 1000, {.forwards = false});
    chassis.turnToHeading(0, 1000, {.direction = AngularDirection::CW_CLOCKWISE});
    chassis.distanceReset('L', 'F');
    chassis.moveToPoint(-48, 25, 1000, {.forwards = false, .minSpeed = 60});
    leftMotors.move(-50); //push into long goal
    rightMotors.move(-50);

    //score long
    scraperState = 1;
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
    chassis.moveToPose(-47, 46, 0, 1000, {.minSpeed = 90, .earlyExitRange = 8});

    //do second ml
    chassis.moveDistance(15.75, 1000, {.minSpeed = 30}); //prev 18
    pros::delay(750);
    //intakeState = 2;
    pros::delay(100);
    intakeState = 3;

    //jitter second ml
    chassis.sendVoltage(-6000, 100);
    chassis.sendVoltage(4000, 1000);

    //score long
    intakeState = 0;
    //chassis.moveToPose(-48, 24, 0, 1000, {.forwards = false, .maxSpeed = 80}); //risky change
    chassis.moveToPoint(-47, 25, 1000, {.forwards = false, .maxSpeed = 65});
    // leftMotors.move(-50); //push into long goal
    // rightMotors.move(-50);
    chassis.distanceReset('L', 'F');
    intakeState = 2; // anti jam
    pros::delay(125);
    intakeState = 4;
    pros::delay(1750); // score previously 2350
    leftMotors.move(0);
    leftMotors.move(0);
    intakeState = 1;
    scraperState = 0;


    if(interrupt) {
        return;
    }



	//move to park
	chassis.moveToPose(-24, 63.25, 82, 2000, {.lead = 0.48}, true);    intakeState = 2; // anti jam
    pros::delay(125);
    intakeState = 1;
    chassis.waitUntilDone();
    std::cout<<"X: "<<std::to_string(chassis.getPose().x)<<"\n";
    std::cout<<"Y: "<<std::to_string(chassis.getPose().y)<<"\n";
    std::cout<<"Theta: "<<std::to_string(chassis.getPose().theta)<<"\n";
    //chassis.turnToHeading(90, 250);
    while(true) {
        if(distBack.get_distance() / 25.4 >= 41.5) {
            leftMotors.move_voltage(0);
	        rightMotors.move_voltage(0);
            break;
        } else {
            leftMotors.move_voltage(5000);
	        rightMotors.move_voltage(6000);
            scraperState = 0;
        }
        pros::delay(10);
    }
    chassis.turnToHeading(90, 250);
    // chassis.moveToPoint(-12, 63, 500);
    // if(distBack.get_distance() / 25.4 >= 44) {
    //     chassis.moveDistance(2, 500);
    // }
	odomState = 1; //odom up
    pros::delay(100);
	scraperState = 1;
	pros::delay(200);

    //use scraper to push blocks
	chassis.sendVoltage(6000, 400); //7500
    //chassis.moveToPoint(-11, chassis.getPose().y, 500, {.minSpeed = 60});
    scraperState = 0;
    intakeState = 3;
	pros::delay(175);

    //initial cross
    leftMotors.move_voltage(8200);
	rightMotors.move_voltage(8600);
    pros::delay(450);

	//pause in park zone
    leftMotors.move_voltage(0);
	rightMotors.move_voltage(0);
    pros::delay(850); //TODO: prev 750

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
    chassis.moveDistance(-7.5, 1000, {.forwards = false, .minSpeed = 60});
	//pros::delay(500);
    midGoalState = 1;
	chassis.turnToHeading(45, 1000, {}, true);
    intakeState = 2; // anti jam
    pros::delay(125);
    intakeState = 5;
    pros::delay(2350); // score
	intakeState = 0;

    if(interrupt) {
        return;
    }

	//veryyyy slowly go out
	chassis.moveDistance(3, 1000, {.maxSpeed = 10});
	chassis.moveDistance(-3, 1000, {.maxSpeed = 5});

	//go to third matchloader
	scraperState = 1;
	chassis.moveDistance(38, 2000, {.minSpeed = 80, .earlyExitRange = 5});
	//chassis.moveToPose(34.6, 46.7, 90, 2000, {.lead = 0.62});
	chassis.turnToHeading(90, 1000, {.minSpeed = 30});
	chassis.distanceReset('F', 'L');
	chassis.moveToPoint(46, chassis.getPose().y, 1500, {}, true);
	pros::delay(500);
	midGoalState = 0; //do states
	intakeState = 3;
	chassis.waitUntilDone();
	intakeState = 3;
	chassis.turnToHeading(0, 1000);
    chassis.distanceReset('R', 'F');

    //do third ml
    chassis.moveDistance(16.75, 1000);
    pros::delay(750);
    //intakeState = 2;
    pros::delay(100);
    intakeState = 3;

    //jitter third ml
    // chassis.moveDistance(-6, 100);
    // chassis.moveDistance(7.5, 750);
    // pros::delay(400);
    chassis.sendVoltage(-6000, 100);
    chassis.sendVoltage(4000, 1000);
    //intakeState = 0;

    if(interrupt) {
        return;
    }

    //go around long goal in alley
    chassis.sendVoltage(-6000, 150);
    chassis.moveToPose(60, 29, 0, 1000, {.forwards = false, .minSpeed = 40, .earlyExitRange = 5}); // booster by 1 x
    scraperState = 0;
    chassis.moveToPoint(59, -28, 1500, {.forwards = false, .minSpeed = 127}); // booster by 1 x

    //move to long goal
    chassis.moveToPoint(45.5, -43, 2000, {.forwards = false});
    chassis.turnToHeading(180, 1000, {.direction = AngularDirection::CW_CLOCKWISE});
    chassis.distanceReset('L', 'F');
    chassis.moveToPoint(48, -25, 1000, {.forwards = false, .minSpeed = 60});
    leftMotors.move(-50); //push into long goal
    rightMotors.move(-50);
    // chassis.moveToPoint(48, -20, 1000, {.forwards = false, .maxSpeed = 60}, true); //make sure the bot keeps pushing forward to actually align

    //score long goal
    scraperState = 1;
    intakeState = 2; // anti jam
    pros::delay(125);
    intakeState = 1;
    pros::delay(1750); // score //previously 2350
    leftMotors.move(0);
    rightMotors.move(0);
    chassis.turnToHeading(181, 500);
    chassis.distanceReset('L', 'F');
    intakeState = 3;

    if(interrupt) {
        return;
    }

    //move to fourth ml
    chassis.moveToPose(46.75, -45, 180, 1000, {.minSpeed = 90, .earlyExitRange = 8});
    //chassis.turnToHeading(180, 1000);

    //do fourth ml
    chassis.moveDistance(17, 1000);
    pros::delay(750);
    //intakeState = 2;
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
    //chassis.moveToPose(48, -25, 180, 1000, {.forwards = false, .maxSpeed = 80}); //risky change
    chassis.moveToPoint(48, -25, 1000, {.forwards = false, .maxSpeed = 65});
    leftMotors.move(-50);
    rightMotors.move(-50);
    // chassis.moveToPoint(48, -20, 1000, {.forwards = false, .maxSpeed = 60}, true);
    intakeState = 2; // anti jam
    pros::delay(125);
    intakeState = 4;
    pros::delay(1700); // score //previously 2350
    leftMotors.move(0);
    rightMotors.move(0);
    chassis.distanceReset('L', 'F');
    intakeState = 1;
    scraperState = 0;

    if(interrupt) {
        return;
    }

    //move to park
    chassis.moveToPose(24, -63.25, -98, 2000, {.lead = 0.4}, true);    intakeState = 2; // anti jam
    pros::delay(125);
    chassis.waitUntilDone();
    while(true) {
        if(distBack.get_distance() / 25.4 >= 41.5) {
            leftMotors.move_voltage(0);
	        rightMotors.move_voltage(0);
            break;
        } else {
            leftMotors.move_voltage(5000);
	        rightMotors.move_voltage(6000);
            scraperState = 0;
        }
        pros::delay(10);
    }
    chassis.turnToHeading(270, 250);
    intakeState = 2;
	odomState = 1; //odom up
    pros::delay(100);
	scraperState = 1;
	pros::delay(200);

    //use scraper to push blocks
	chassis.sendVoltage(6000, 400); //7500
    scraperState = 0;
	pros::delay(175);

    //initial cross
    leftMotors.move_voltage(8000);
	rightMotors.move_voltage(8400);
    pros::delay(250);

	while (true) {
        if (distBack.get_distance() / 25.4 >= 62 && distBack.get_distance() / 25.4 < 100 || distFrontRight.get_distance() / 25.4 <= 67 && distFrontRight.get_distance() / 25.4 >= 50) {
            std::cout<<"back: "<<distBack.get_distance() / 25.4<<"     front: "<<distFrontRight.get_distance() / 25.4<<"\n";
            std::cout<<"stopped\n";
            leftMotors.move_voltage(0);
			rightMotors.move_voltage(0);
			break;
        } else {
			std::cout<<"back: "<<distBack.get_distance() / 25.4<<"     front: "<<distFrontRight.get_distance() / 25.4<<"\n";
            leftMotors.move_voltage(9500); //prev 9500
			rightMotors.move_voltage(10000); //prev 10000
		}
        pros::delay(10);
    }
    intakeState = 1;
    chassis.sendVoltage(-3000, 250);

}
