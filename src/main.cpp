#include "main.h"
#include "drivecode/objects.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"
#include "drivecode/util.hpp"
#include "pros/misc.h"
#include "lemlib/intersect.hpp"
#include "autonomous/autonSelector.hpp"
#include "autonomous/autonomous.hpp"
#include "logo.c"
#include "liblvgl/display/lv_display.h"
#include "liblvgl/widgets/image/lv_image.h"

void displayImageFromArray() {
	lv_obj_t* img = lv_image_create(lv_screen_active());
	lv_image_set_src(img, &logo);
	lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
}

void on_center_button() {}

void initialize() {
	displayImageFromArray();

	chassis.calibrate();
	chassis.setPose(0,0,0);

	//autonSelector();
	taskInit();
	motorInit();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

	// sevenRight();
	// sevenLeft();
	fourPlusThreeRight();
	// fourPlusThreeLeft();
	
}

void opcontrol() {
	//driver
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	intakeState = 0;

	while (true) {
		// // subsystem updates
		updateIntake();
		updatePistons();

		// 	pros::delay(500);
		// }

		// if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
		// 	chassis.moveToPose(0, 0, 0, 3000);
		// }

		// if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
		// 	chassis.setPose(0, 0, 0);
		// }
		
		//drive
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		chassis.arcade(throttle, turn);

		//delay
		pros::delay(10);
	}
}