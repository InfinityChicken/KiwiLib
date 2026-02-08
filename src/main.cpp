#include "main.h"
#include "drivecode/objects.hpp"
#include "pros/motors.h"
#include "drivecode/util.hpp"
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

	chassis.setPose(-1,1,0);
	scraperState = 1;
	pros::delay(1000);

	chassis.distanceReset('L', 'F');
    intakeState = 1;
    scraperState = 0;

	//first park zone
	chassis.moveToPose(-19, 63, 83, 2000, {.lead = 0.55});    
	odomState = 1; 
	scraperState = 1;
	chassis.sendVoltage(7000, 250);
    scraperState = 0;
	pros::delay(100);
	leftMotors.move_voltage(7000);
	rightMotors.move_voltage(7200);
	pros::delay(1500);
	scraperState = 1;
    odomState = 1;
    pros::delay(750);
	chassis.sendVoltage(0, 100);
	scraperState = 1;

	//mid goal
	chassis.turnToHeading(0,1000);
	odomState = 0;
	chassis.distanceReset('R', 'F');
    chassis.moveToPose(8.9, 10.5, 45, 2000, {.forwards = false, .minSpeed = 60});
    midGoalState = 1;
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(100);
    intakeState = 1;
    pros::delay(1000);

	//skills97();
	//skills79(); 
	//SAWP();
	// sevenBlockPushLeft();
	//sevenBlockPushRight();
	//fourBlockPushLeft();
	// leftSplit();
	// rightSplit();
	// pros::screen::print(pros::E_TEXT_MEDIUM, 150, 120, "auton done!");
}

void opcontrol() {
	//driver
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	intakeState = 0;
	velValue = 12000;
	midGoalSpeed = 12000 * 0.8; // mid goal 80% reset for driver

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
		chassis.arcade(throttle, turn, true, 0.6);

		//delay
		pros::delay(10);
	}
}