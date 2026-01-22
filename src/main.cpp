#include "main.h"
#include "objects.hpp"
#include "util.hpp"
#include "pros/misc.h"
#include "drivecode/intake.hpp"
#include "drivecode/pistons.hpp"
#include "drivecode/sensors.hpp"
#include "autonomous/autonomous.hpp"

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
	// chassis.setPose(1,-1,90);
	// chassis.distanceReset('F', 'R');

	chassis.moveDistance(6, 1000, {.minSpeed = 40});
    scraperState = 1;
    intakeState = 0;
    chassis.sendVoltage(6000, 250); //TODO: changed from 1000ms
    scraperState = 0;
	pros::delay(100);
    //chassis.sendVoltage(12000,500);
    while (true) {
        if (distBack.get_distance() / 25.4 >= 68) {
            leftMotors.move_voltage(0);
			rightMotors.move_voltage(0);
			break;
        } else {
			leftMotors.move_voltage(10000);
			rightMotors.move_voltage(10000);
		}
        pros::delay(10);
    }

	//skills();
	// SAWP();
	// sevenBlockPushLeft();
	// sevenBlockPushRight();
}

void opcontrol() {
	//driver
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	intakeState = 0;
	velValue = 12000;
	midGoalSpeed = 12000 * 0.55;

	bool buttonPressed = false;

	while (true) {
		// //pid
		// PIDTuning(0, 90);
		
		//subsystem updates
		updateIntake();
		updatePistons();
		updateSensors();
		
		//drive
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		chassis.arcade(throttle, turn);

		//delay
		pros::delay(10);
	}
}