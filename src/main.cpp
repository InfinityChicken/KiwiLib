#include "main.h"
#include "drivecode/objects.hpp"
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
	chassis.setPose(-1,1,0);
	scraperState = 1;
	pros::delay(1000);

	//dist reset
	chassis.distanceReset('L', 'F');
    intakeState = 1;
    scraperState = 0;

	//move to park
	chassis.moveToPose(-14, 63, 83, 2000, {.lead = 0.55}); //curve to park zone
	odomState = 1; //odom up
	scraperState = 1; 
	pros::delay(100);

	//use scraper to push blocks
	chassis.sendVoltage(10000, 300); //7500
    scraperState = 0;
	pros::delay(350);

	//inital cross
	leftMotors.move_voltage(10500); //prev 8k, needs a tiny bit more power
	rightMotors.move_voltage(10700);
	pros::delay(650);

	//pause in park zone
	chassis.sendVoltage(0, 1000); 
	//scraperState = 1;

	//lift front wheels out of park
	leftMotors.move_voltage(2000);
	rightMotors.move_voltage(2200);
	pros::delay(250);

	//exit park zone
	leftMotors.move_voltage(6000); //go slow out of park zone
	rightMotors.move_voltage(6200); //prev 6200
	pros::delay(1000);
	scraperState = 0;

	//antijam + odom down
    odomState = 0;
	intakeState = 2;
	pros::delay(100);
	intakeState = 1;
	chassis.sendVoltage(0, 10);

	//go to matchloader to intake all blocks
	while (true) {
        if (distBack.get_distance() / 25.4 >= 98) {
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

	//back up from matchloader
	// while (true) {
    //     if (distBack.get_distance() / 25.4 <= 93.5) {
    //         leftMotors.move_voltage(0);
	// 		rightMotors.move_voltage(0);
	// 		break;
    //     } else {
	// 		leftMotors.move_voltage(-4500);
	// 		rightMotors.move_voltage(-4500); //prev 10000
	// 	}
    //     pros::delay(10);
    // } 
	chassis.moveDistance(-14, 1000, {.forwards = false});

	//mid goal
	chassis.turnToHeading(180, 1000);
	chassis.distanceReset('L', 'B');

	//get one more block
    chassis.moveToPoint(18, 19.5, 1500);

    //turn and move toward mid goal
    chassis.turnToHeading(45, 1000);
    intakeState = 1;
	chassis.moveDistance(-10, 1000, {.forwards = false, .minSpeed = 60});
    // chassis.moveToPoint(12, 12, 1000, {.forwards = false, .minSpeed = 60});
    midGoalState = 1;
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(250); //antijam time
	midGoalSpeed = 12000 * 0.8;
    intakeState = 1;
    pros::delay(1250); //score time
	lowGoalVel = true;
	pros::delay(500);
	intakeState = 0;
	lowGoalVel = false;

	//veryyyy slowly go out
	chassis.moveDistance(3, 1000, {.maxSpeed = 10});
	chassis.moveDistance(-3, 1000, {.maxSpeed = 5});

	//go to third matchloader
	scraperState = 1;
	chassis.moveToPoint(47, 52.5, 1500, {}, true);
	pros::delay(500);
	midGoalState = 0;
	intakeState = 1;
	chassis.waitUntilDone();
	trapdoorState = 1;
	chassis.turnToHeading(0, 1000);

	//skills97();
	//skills79(); 
	//SAWP();
	//sevenBlockPushLeft();
	//sevenBlockPushRight();
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