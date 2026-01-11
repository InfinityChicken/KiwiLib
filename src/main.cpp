#include "main.h"
#include "objects.hpp"
#include "util.hpp"
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
	// chassis.setPose(1,-1,-90);
	// chassis.distanceReset('B', 'L');
	SAWP();
}

void opcontrol() {
	//chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
	//SAWP();

	//driver
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	intakeState = 0;
	velValue = 12000;

	bool buttonPressed = false;

	while (true) {
		// if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
		// 	chassis.setPose(0, 0, 0);
		// 	chassis.turnToHeading(90, 1000);
		// 	chassis.turnToHeading(180, 1000);
		// 	chassis.turnToHeading(270, 1000);
		// 	chassis.turnToHeading(0, 1000);
		// }

		// //pid
		// PIDTuning(0, 90);
		
		// //subsystem updates
		updateIntake();
		updatePistons();
		updateSensors();
		
		//drive
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		chassis.arcade(throttle, turn);

		//delay
		pros::delay(10);
	}
}