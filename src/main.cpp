#include "main.h"
#include "drivecode/objects.hpp"
#include "pros/motors.h"
#include "drivecode/util.hpp"
#include "pros/misc.h"
#include "drivecode/intake.hpp"
#include "drivecode/pistons.hpp"
#include "drivecode/sensors.hpp"
#include "autonomous/autonomous.hpp"

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
	// chassis.setPose(1,-1,90);
	// chassis.distanceReset('F', 'R');

	// while(true) {
	// chassis.moveToPose(25, 40, 90, 5000);
	// }

	//chassis.moveDistance(4,2000);
	// chassis.setPose(0,0,0);
	// chassis.turnToHeading(90, 1000);

	//chassis.moveToPoint(0,24,1000);
	skills97();
	//skills79(); 
	//SAWP();
	// sevenBlockPushLeft();
	//sevenBlockPushRight();
	//fourBlockPushLeft();
	// leftSplit();
	// rightSplit();
	// pros::screen::print(pros::E_TEXT_MEDIUM, 150, 120, "auton done!");
}

void opcontrol() {
	//driver
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	intakeState = 0;
	velValue = 12000;
	midGoalSpeed = 12000 * 0.8; // mid goal 80% reset for driver

	chassis.setPose(1, 1, 0);
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
		chassis.arcade(throttle, turn, true, 0.6);

		//delay
		pros::delay(10);
	}
}