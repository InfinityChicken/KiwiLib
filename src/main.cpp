#include "main.h"
#include "drivecode/intake.hpp"
#include "drivecode/objects.hpp"
#include "drivecode/util.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/misc.h"
#include "drivecode/sensors.hpp"
#include "autonomous/autonSelector.hpp"
#include "autonomous/autons.hpp"
#include "pros/motors.h"
#include "autonomous/pidTuning.hpp"

void on_center_button() {}

void initialize() {
	// pros::lcd::initialize();

	chassis.calibrate();
	chassis.setPose(0, 0, 0);

	taskInit();
	motorInit();
	sensorInit();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
	// chassis.setPose(0, 0, 0);

	chassis.moveToPoint(0, 36, 100000);
	intakeState = 1;
	// chassis.turnToPoint(0, 0, 10000);
	// chassis.moveToPoint(0, 0, 10000);
}

void opcontrol() {
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
	velValue = 12000;
	intakeState = 0;

	while (true) {
		//subsystem updates //TODO: add these back
		// updateIntake();
		// updatePistons();

		pidTuning();

		//drive
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		chassis.arcade(throttle, turn);
			
		//delay
		pros::delay(10);
	}
}