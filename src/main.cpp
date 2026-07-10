#include "main.h"

#include "autonomous/autonomous.hpp"

#include "drivecode/cascade.hpp"
#include "drivecode/flip.hpp"
#include "drivecode/intake.hpp"
#include "drivecode/objects.hpp"
#include "drivecode/pistons.hpp"
#include "drivecode/util.hpp"

#include "lemlib/chassis/chassis.hpp"
#include "lemlib/intersect.hpp"
#include "pros/motors.h"
#include "pros/misc.h"

#include "sdcard/sdtest.hpp"
#include "sdcard/sdmain.hpp"

#include "liblvgl/display/lv_display.h"
#include "liblvgl/misc/lv_area.h"
#include "liblvgl/widgets/image/lv_image.h"

void on_center_button() {}

void initialize() {
	chassis.calibrate();
	chassis.setPose(0,0,0);

	motorInit();
	sensorInit();
	
	taskInit();

	displayLogo();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
	dsunauto();
} 

void opcontrol() {
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

	while (true) {
		// dispVinish_cArray();
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		chassis.arcade(throttle, turn);

		updateCascade();
		updateIntake();
		updateFlip();
		// updatePistons();
		runManual();
		// macroScore();

		pros::delay(10);
	}
}