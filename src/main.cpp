// imports

// main.h
#include "main.h"

// autonomous
#include "autonomous/autonomous.hpp"
#include "autonomous/autonSelector.hpp"

// drivecode
#include "drivecode/cascade.hpp"
#include "drivecode/flip.hpp"
#include "drivecode/intake.hpp"
#include "drivecode/objects.hpp"
#include "drivecode/pistons.hpp"
#include "drivecode/util.hpp"

// lemlib & pros
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/intersect.hpp"
#include "pros/motors.h"
#include "pros/misc.h"

// sdcard
#include "sdcard/sdtest.hpp"
#include "sdcard/sdmain.hpp"

void on_center_button() {}

void initialize() {
	// reset the chassis position
	chassis.calibrate();
	chassis.setPose(0,0,0);

	// initialize the motors
	motorInit();

	// initialize the sensors
	sensorInit();

	// run autonSelector during the set up period
	autonSelector();
}

void disabled() {}

void competition_initialize() {
	// initialize the tasks
	taskInit();
}

void autonomous() {
	// set the autonomous to brake
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

	runAuton();
} 

void opcontrol() {
	// set the drive to coast
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

	while (true) {
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		// gourav's favourite two stick arcade configuration
		chassis.arcade(throttle, turn);

		// update drivecode
		updateCascade();
		updateFlip();
		updateIntake();
		// commented out while we work out the issues surrounding the color sort
		// updatePistons();

		// miscellaneous manual override or macro programs
		runManual();
		macroScore();

		pros::delay(10);
	}
}