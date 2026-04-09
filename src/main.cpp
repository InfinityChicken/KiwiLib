#include "main.h"
#include "drivecode/objects.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"
#include "drivecode/util.hpp"
#include "pros/misc.h"
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
	//leftSplitPush();
	//counterSAWP();
}

void opcontrol() {
	// chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
	// skills97();

	//driver
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	intakeState = 0;

	while (true) {
		//pid
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			chassis.moveToPoint(0, 0, 2000);
			lemlib::Pose pose = chassis.getPose();
			std::cout<<"X: "<<pose.x<<"\n";
			std::cout<<"Y: "<<pose.y<<"\n";
			std::cout<<"T: "<<pose.theta<<"\n\n";
		}

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			chassis.moveToPose(0, 0, 0, 2000);
			lemlib::Pose pose = chassis.getPose();
			std::cout<<"X: "<<pose.x<<"\n";
			std::cout<<"Y: "<<pose.y<<"\n";
			std::cout<<"T: "<<pose.theta<<"\n\n";
		}

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) chassis.setPose(0, 0, 0);
		
		//subsystem updates
		// updateIntake();
		// updatePistons();
		
		//drive
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		chassis.arcade(throttle, turn);

		//delay
		pros::delay(10);
	}
}