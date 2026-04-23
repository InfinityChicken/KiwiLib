#include "main.h"
#include "drivecode/objects.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"
#include "drivecode/util.hpp"
#include "pros/misc.h"
#include "lemlib/intersect.hpp"
#include "autonomous/autonSelector.hpp"
#include "autonomous/autonomous.hpp"

void on_center_button() {}

void initialize() {
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

	//chassis.moveDistance(4, 1000);
	//chassis.turnToHeading(180, 1000);

	// sevenRight();
	// sevenLeft();

	fourPlusThreeRight(); //DONE! saturday night
	//fourPlusThreeLeft(); //DONE! friday night

	//counterSAWP(); //DONE! saturday night

	// auroraAuto();

	// nineBallRight(); //good sunday
	// nineBallLeft(); //BAD
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

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
			chassis.moveToPose(0, 0, 0, 3000);
		}

		// if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
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