#include "main.h"
#include "objects.hpp"
#include "util.hpp"
#include "pros/misc.h"

void on_center_button() {}

void initialize() {
	chassis.calibrate();
	chassis.setPose(0, 0, 0);

	taskInit();
	motorInit();
	sensorInit();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
}

void opcontrol() {
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

	while (true) {
		//subsystem updates
		
		//drive
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		chassis.arcade(throttle, turn);

		//delay
		pros::delay(10);
	}
}