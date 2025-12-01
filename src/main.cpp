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

	while (true) {
		//subsystem updates
		
		//drive
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		//delay
		pros::delay(10);
	}
}