#include "main.h"
#include "objects.hpp"
#include "pros/motors.h"
#include "util.hpp"
#include "pros/misc.h"

void on_center_button() {}

void initialize() {
	taskInit();
	motorInit();
	sensorInit();

	chassis.calibrate();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
}

void opcontrol() {
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

	bool l1Pressed = false;
	while (true) {
		//drive
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		chassis.arcade(throttle, turn);

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			if(!l1Pressed) {
				chassis.setPose(0, 0, 0);
				chassis.moveToPoint(0, 24, 2000);
				l1Pressed = true;
			}
		} else {
			l1Pressed = false;
		}

		//delay
		pros::delay(10);
	}
}