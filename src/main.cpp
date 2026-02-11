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
	chassis.moveToPose(-15, 63, 83, 2000, {.lead = 0.55}); //curve to park zone
	odomState = 1; //odom up
	scraperState = 1; 
	pros::delay(100);

	//use scraper to push blocks
	chassis.sendVoltage(7500, 300); //7500
    scraperState = 0;
	pros::delay(350);

	//inital cross
	leftMotors.move_voltage(9000); //prev 8k, needs a tiny bit more power
	rightMotors.move_voltage(9200);
	pros::delay(550);

	//pause in park zone
	chassis.sendVoltage(0, 1000); 
	scraperState = 1;

	//lift front wheels out of park
	leftMotors.move_voltage(2000);
	rightMotors.move_voltage(2200);
	pros::delay(250);

	//exit park zone
	leftMotors.move_voltage(8000); //go slow out of park zone
	rightMotors.move_voltage(8200); //prev 6200
	pros::delay(500);
	scraperState = 0;

	//antijam + odom down
    odomState = 0;
	intakeState = 2;
	pros::delay(100);
	intakeState = 1;

	//go to matchloader to intake all blocks
	chassis.sendVoltage(4000, 1000);
	pros::delay(300);

	//back up from matchloader
	chassis.sendVoltage(-4000, 800); //-6k 600

	//mid goal
	chassis.turnToHeading(180, 1000);
	chassis.distanceReset('L', 'B');

	//get one more block
    chassis.moveToPoint(18, 20, 1500);

    //turn and move toward mid goal
    chassis.turnToHeading(45, 1000);
    intakeState = 1;
	chassis.moveDistance(-8, 1000, {.forwards = false, .minSpeed = 60});
    // chassis.moveToPoint(12, 12, 1000, {.forwards = false, .minSpeed = 60});
    midGoalState = 1;
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(100); //antijam time
    intakeState = 1;
    pros::delay(1500); //score time
	intakeState = 0;

	//veryyyy slowly go out
	chassis.moveDistance(5, 1000, {.maxSpeed = 20});
	chassis.moveDistance(-5, 1000, {.maxSpeed = 20});

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