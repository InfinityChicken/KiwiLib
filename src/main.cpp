#include "main.h"
#include "objects.hpp"
#include "util.hpp"
#include "pros/misc.h"

void on_center_button() {}

void initialize() {
	taskInit();
	motorInit();
	sensorInit();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
}

void opcontrol() {

	bool l1Pressed = false;
	while (true) {
		//subsystem updates
		
		//drive
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			if(!l1Pressed) {
				chassis.setPose(0, 0, 0);
				chassis.turnToHeading(90, 2000);
				l1Pressed = true;
			}
		} else {
			l1Pressed = false;
		}

		//delay
		pros::delay(10);
	}
}