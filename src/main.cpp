#include "main.h"
#include "drivecode/objects.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"
#include "drivecode/util.hpp"
#include "pros/misc.h"
#include "drivecode/intake.hpp"
#include "drivecode/pistons.hpp"
#include "drivecode/sensors.hpp"
#include "autonomous/autonomous.hpp"
#include "lemlib/intersect.hpp"
#include "autonomous/autonSelector.hpp"

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

	// //initialize for final skills park reset in lg
	// chassis.setPose(10, -10, 180);
	// scraperState = 1;
	// wingState = 1;
	// pros::delay(1000);
	// chassis.distanceReset('L', 'F');
	// scraperState = 0;

	// //initialize for first skills park reset in lg
	// chassis.setPose(-10, 10, 0);
	// scraperState = 1;
	// wingState = 1;
	// pros::delay(1000);
	// chassis.distanceReset('L', 'F');
	// scraperState = 0;

	//chooseAuton();

	//skills97();
	//SAWP();
	//sevenBlockPushLeft();
	//sevenBlockPushRight(); 
	//fourBlockPushLeft();
	//fourBlockPushRight();
	leftSplitPush();
	//counterSAWP();
}

void opcontrol() {
	//driver
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

	while (true) {
		//drive
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
			chassis.setPose(0, 0, 0);
			chassis.turnToHeading(90, 2000);
		}

		//delay
		pros::delay(10);
	}
}