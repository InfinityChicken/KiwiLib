#include "main.h"

#include "autonomous/autonomous.hpp"

#include "drivecode/cascade.hpp"
#include "drivecode/pistons.hpp"
#include "drivecode/intake.hpp"
#include "drivecode/flip.hpp"
#include "drivecode/objects.hpp"
#include "drivecode/util.hpp"

#include "lemlib/chassis/chassis.hpp"
#include "lemlib/intersect.hpp"
#include "pros/motors.h"
#include "pros/misc.h"

#include "liblvgl/display/lv_display.h"
#include "liblvgl/misc/lv_area.h"
#include "liblvgl/widgets/image/lv_image.h"

// #include "sdcard/sdtest.hpp"
// #include "sdcard/sdmain.hpp"

void on_center_button() {}

void dispVinish_cArray() {
    // create a variable for the c array (image)
    LV_IMAGE_DECLARE(vinish);

    // declare and define the image object
    lv_obj_t* img = lv_image_create(lv_screen_active());

    // set the source data for the image 
    lv_image_set_src(img,&vinish);

    // (Optional) set the image's alignment
    lv_obj_align(img,LV_ALIGN_CENTER,0,0); // centered in the screen
}

void initialize() {
	chassis.calibrate();
	chassis.setPose(0,0,0);

	motorInit();
	sensorInit();
	
	taskInit();

	dispVinish_cArray();
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