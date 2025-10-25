#include "main.h"
#include "drivecode/intake.hpp"
#include "drivecode/objects.hpp"
#include "drivecode/util.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/misc.h"
#include "drivecode/sensors.hpp"
#include "autonomous/autonSelector.hpp"
#include "autonomous/autons.hpp"
#include "pros/motors.h"

void on_center_button() {}

void initialize() {
	// pros::lcd::initialize();

	chassis.calibrate();
	chassis.setPose(0, 0, 0);

	taskInit();
	motorInit();
	sensorInit();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
	// chassis.setPose(0, 0, 0);

	chassis.moveToPoint(0, 36, 100000);
	intakeState = 1;
	// chassis.turnToPoint(0, 0, 10000);
	// chassis.moveToPoint(0, 0, 10000);
}

void opcontrol() {
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
	velValue = 12000;
	intakeState = 0;

	bool upPressed = false;
	bool downPressed = false;
	bool rightPressed = false;
	
	bool l1Pressed = false;
	bool l2Pressed = false;
	bool r1Pressed = false;
	bool r2Pressed = false;

	int selectionMode = 0; //1 is kP, 2 is kD, 3 is slew

	while (true) {
		//subsystem updates //TODO: add these back
		// updateIntake();
		// updatePistons();

		//PID updates
		//increment
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
			if(!upPressed) {
				upPressed = true;
				switch(selectionMode) {
					case 1: {
						kP = kP + 0.1;
						std::cout<<kP<<"\n";
						break;
					}

					case 2: {
						kD = kD + 0.1;
						std::cout<<kD<<"\n";
						break;
					}

					case 3: {
						slew = slew + 0.1;
						std::cout<<slew<<"\n";
						break;
					}

				}
			} 
		} else {
			upPressed = false;
		}

		//decrement
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			if(!downPressed) {
				downPressed = true;
				switch(selectionMode) {
					case 1: {
						kP = kP - 0.1;
						std::cout<<kP<<"\n";
						break;
					}

					case 2: {
						kD = kD - 0.1;
						std::cout<<kD<<"\n";
						break;
					}

					case 3: {
						slew = slew - 0.1;
						std::cout<<slew<<"\n";
						break;
					}

				}
				
			} 
		} else {
			downPressed = false;
		}
	
		//cycle tune value
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
			if(!rightPressed) {
				rightPressed = true;

				selectionMode++;

				if (selectionMode == 4) {
					selectionMode = 1;
					std::cout<<selectionMode<<"\n";
				}
			}
		} else {
			rightPressed = false;
		}

		//move 12 inches
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) { //l1, long goal (indexer outtake), state 1
			if(!l1Pressed) {
				l1Pressed = true;

				chassis.setPose(0, 0, 0);
				chassis.moveToPoint(0, 12, 10000);
				std::cout<<"Movement run, ending coord: "<<chassis.getPose().y<<"\n";
			}
		} else {
			l1Pressed = false;
		}

		//move 24 inches
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { //l1, long goal (indexer outtake), state 1
			if(!l2Pressed) {
				l2Pressed = true;

				chassis.setPose(0, 0, 0);
				chassis.moveToPoint(0, 24, 10000);
				std::cout<<"Movement run, ending coord: "<<chassis.getPose().y<<"\n";
			}
		} else {
			l2Pressed = false;
		}


		//move 36 inches
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { //l1, long goal (indexer outtake), state 1
			if(!r1Pressed) {
				r1Pressed = true;

				chassis.setPose(0, 0, 0);
				chassis.moveToPoint(0, 36, 10000);
				std::cout<<"Movement run, ending coord: "<<chassis.getPose().y<<"\n";
			}
		} else {
			r1Pressed = false;
		}

		//move 48 inches
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) { //l1, long goal (indexer outtake), state 1
			if(!r2Pressed) {
				r2Pressed = true;

				chassis.setPose(0, 0, 0);
				chassis.moveToPoint(0, 48, 10000);
				std::cout<<"Movement run, ending coord: "<<chassis.getPose().y<<"\n";
			}
		} else {
			r2Pressed = false;
		}

		//drive
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		chassis.arcade(throttle, turn);
		
		//delay
		pros::delay(10);
	}
}