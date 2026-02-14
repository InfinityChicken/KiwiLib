#include "main.h"
#include "drivecode/objects.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"
#include "drivecode/util.hpp"
#include "pros/misc.h"
#include "drivecode/intake.hpp"
#include "drivecode/pistons.hpp"
#include "drivecode/sensors.hpp"
#include "autonomous/autonomous.hpp"
#include "lemlib/intersect.hpp"

void on_center_button() {}

void initialize() {
	chassis.calibrate();
	chassis.setPose(0,0,0);

	taskInit();
	motorInit();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

	//initial stuff for dist reset
	chassis.setPose(-1,1,0); //-1, 1, 0
	scraperState = 1;
	pros::delay(1000);

	//dist reset
	chassis.distanceReset('L', 'F');
    intakeState = 1;
    scraperState = 0;

	// chassis.moveToPose(14, -63, 263, 2000, {.lead = 0.55});
    // //chassis.turnToHeading(270, 1000);
    // //chassis.moveDistance(4, 1000, {.minSpeed = 40});
    // scraperState = 1;
    // intakeState = 2;
    // odomState = 1;
	// pros::delay(100);
    // chassis.sendVoltage(10000, 250);
	// scraperState = 0;
	// pros::delay(100);
    // chassis.sendVoltage(10000,500); //prev 10000
    // while (true) {
    //     if (distBack.get_distance() / 25.4 >= 66 && distBack.get_distance() / 25.4 < 100) {
    //         leftMotors.move_voltage(0);
	// 		rightMotors.move_voltage(0);
	// 		break;
    //     } else {
	// 		leftMotors.move_voltage(9000); //prev 9500
	// 		rightMotors.move_voltage(10000); //prev 10000
	// 	}
    //     pros::delay(10);
    // }  
    // chassis.sendVoltage(-8000, 250);

	//move to park
	chassis.moveToPose(-14, 63, 83, 2000, {.lead = 0.55}); //curve to park zone
	odomState = 1; //odom up
	scraperState = 1; 
	pros::delay(100);

	//use scraper to push blocks
	chassis.sendVoltage(11000, 200); //7500
    scraperState = 0;
	pros::delay(175);

	//inital cross
	leftMotors.move_voltage(10500); //prev 8k, needs a tiny bit more power
	rightMotors.move_voltage(10900);
	pros::delay(615);

	//pause in park zone
	chassis.sendVoltage(0, 500);  //1100 before
	//scraperState = 1;

	//lift front wheels out of park
	leftMotors.move_voltage(2000);
	rightMotors.move_voltage(2400);
	pros::delay(100);

	//exit park zone
	leftMotors.move_voltage(6000); //go slow out of park zone
	rightMotors.move_voltage(6100); //prev 6200
	pros::delay(1000);
	scraperState = 0;

	//antijam + odom down
    odomState = 0;
	intakeState = 2;
	pros::delay(50);
	intakeState = 1;
	chassis.sendVoltage(0, 10);

	//go to matchloader to intake all blocks
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

	//mid goal
	chassis.swingToHeading(180, lemlib::DriveSide::RIGHT, 1000);
	chassis.distanceReset('L', 'B');

	//get one more block
    chassis.turnToHeading(192, 1000); //187 before
	chassis.moveToPoint(18.5, 19.5, 1500);
	//chassis.moveToPose(22, 14.4, chassis.getPose().theta, 1000, {.lead = 0});

    //turn and move toward mid goal
    //chassis.turnToPoint(5.3, 10.3, 1000, {.forwards = false});
    chassis.turnToHeading(40, 1000);
	intakeState = 1;
	//chassis.moveToPoint(7.3, 12.3, 1000, {.forwards = false, .minSpeed = 60}, true);
    chassis.moveDistance(-8, 1000, {.forwards = false, .minSpeed = 60});
	pros::delay(500);
    midGoalState = 1;
    trapdoorState = 1;
	chassis.turnToHeading(45, 1000, {}, true);
    intakeState = 2;
    pros::delay(200); //antijam time
	midGoalSpeed = 12000 * 0.7;
    intakeState = 1;
    pros::delay(1200); //score time
	lowGoalVel = true;
	pros::delay(600);
	intakeState = 0;
	lowGoalVel = false;

	//veryyyy slowly go out
	chassis.moveDistance(3, 1000, {.maxSpeed = 10});
	chassis.moveDistance(-2.75, 1000, {.maxSpeed = 5});

	//go to third matchloader
	scraperState = 1;
	chassis.moveDistance(43, 2000, {.earlyExitRange = 5});
	//chassis.moveToPose(34.6, 46.7, 90, 2000, {.lead = 0.62});
	chassis.turnToHeading(90, 1000, {.minSpeed = 30});
	chassis.distanceReset('F', 'L');
	chassis.moveToPoint(45.75, chassis.getPose().y, 1500, {}, true);
	pros::delay(500);
	midGoalState = 0; //do states
	intakeState = 1;
	chassis.waitUntilDone();
	trapdoorState = 0;
	chassis.turnToHeading(0, 1000);
    chassis.distanceReset('R', 'F');

    //do third ml
    chassis.moveDistance(16, 1000);
    pros::delay(750);
    intakeState = 2;
    pros::delay(100);
    intakeState = 1;



	//skills97();
	//skills79(); 
	//SAWP();
	//sevenBlockPushLeft();
	//sevenBlockPushRight(); score 96 points
	//fourBlockPushLeft();
	//fourBlockPushRight();
	//leftSplitPush();
}

void opcontrol() {
	//driver
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	intakeState = 0;
	velValue = 12000;
	midGoalSpeed = 12000 * 0.8; // mid goal 80% reset for driver

	while (true) {
		// //pid
		// PIDTuning(0, 90);
		
		//subsystem updates
		updateIntake();
		updatePistons();
		updateSensors();
		
		//drive
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		chassis.arcade(throttle, turn, true);

		//delay
		pros::delay(10);
	}
}