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
#include "autonomous/pidTuning.hpp"

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
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	// chassis.setPose(0, 0, 0);

	leftMotors.move_velocity(600);
	rightMotors.move_velocity(600);
	// chassis.turnToPoint(0, 0, 10000);
	// chassis.moveToPoint(0, 0, 10000);
}

void opcontrol() {
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	velValue = 12000;
	intakeState = 0;

	bool l1Pressed = false;
	bool l2Pressed = false;
	bool r1Pressed = false;
	bool r2Pressed = false;

	while (true) {
		//subsystem updates //TODO: add these back
		// updateIntake();
		// updatePistons();
		/*
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) { //45
            if(!l1Pressed) {
                l1Pressed = true;

                chassis.setPose(0, 0, 0);
                chassis.turnToHeading(45, 3000);
            }
        } else {
            l1Pressed = false;
        }

        //l2: turn 90
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { //90
            if(!l2Pressed) {
                l2Pressed = true;

                chassis.setPose(0, 0, 0);
                chassis.turnToHeading(90, 3000);
            }
        } else {
            l2Pressed = false;
        }


        //r1: turn 180
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { //180
            if(!r1Pressed) {
                r1Pressed = true;

                chassis.setPose(0, 0, 0);
                chassis.turnToHeading(180, 3000);
            }
        } else {
            r1Pressed = false;
        }
		*/

		//l1: 12 inches forward
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            if(!l1Pressed) {
                l1Pressed = true;

                chassis.setPose(0, 0, 0);
                chassis.moveToPoint(0, 24,5000, {.maxSpeed = 80});
                std::cout<<"Movement run, ending coord: "<<chassis.getPose().y<<"\n";
            }
        } else {
            l1Pressed = false;
        }

        //l2: 24 inches forward
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            if(!l2Pressed) {
                l2Pressed = true;

                chassis.setPose(0, 0, 0);
                chassis.moveToPoint(0, 48, 5000, {.maxSpeed = 80});
                std::cout<<"Movement run, ending coord: "<<chassis.getPose().y<<"\n";
            }
        } else {
            l2Pressed = false;
        }

        //r1: 36 inches forward
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            if(!r1Pressed) {
                r1Pressed = true;

                chassis.setPose(0, 0, 0);
                chassis.turnToHeading(90, 3000, {.maxSpeed = 90});
                std::cout<<"Movement run, ending coord: "<<chassis.getPose().y<<"\n";
            }
        } else {
            r1Pressed = false;
        }

        //r2: 48 inches forward
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            if(!r2Pressed) {
                r2Pressed = true;

                chassis.setPose(0, 0, 0);
                chassis.turnToHeading(180, 3000, {.maxSpeed = 90});
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