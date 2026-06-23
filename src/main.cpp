#include "main.h"
#include "drivecode/objects.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"
#include "drivecode/util.hpp"
#include "pros/misc.h"
#include "lemlib/intersect.hpp"
#include "autonomous/autonomous.hpp"
#include "sdcard/sdtest.hpp"
#include "sdcard/sdmain.hpp"

void on_center_button() {}

void initialize() {
	chassis.calibrate();
	chassis.setPose(0,0,0);

	taskInit();
	motorInit();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

	override_june();
} 

void opcontrol() {
	//driver
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

	while (true) {
		//drive
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		chassis.arcade(throttle, turn);
		//delay
		pros::delay(10);
	}

}