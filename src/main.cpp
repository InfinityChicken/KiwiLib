#include "main.h"
#include "lemlib/chassis/chassis.hpp"
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
	bool l2Pressed = false;
	bool r1Pressed = false;

	while (true) {
		//drive
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		chassis.arcade(throttle, turn);

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			if(!l1Pressed) {
				chassis.setPose(0, 0, 0);
				chassis.turnToHeading(90,5000);
				l1Pressed = true;
			}
		} else {
			l1Pressed = false;
		}

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			if(!l2Pressed) {
				chassis.setPose(0, 0, 0);
				chassis.turnToHeading(180, 5000, {lemlib::AngularDirection::CW_CLOCKWISE});
				l2Pressed = true;
			}
		} else {
			l2Pressed = false;
		}

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			if(!r1Pressed) {
				chassis.setPose(0, 0, 0);
				chassis.turnToHeading(45, 5000);
				r1Pressed = true;
			}
		} else {
			r1Pressed = false;
		}

		//delay
		pros::delay(10);
	}
}