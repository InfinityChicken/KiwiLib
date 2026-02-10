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
	chassis.moveToPose(-15, 63, 83, 2000, {.lead = 0.55}); //curve to park zone
	odomState = 1; //odom up
	scraperState = 1; 
	pros::delay(100);
	chassis.sendVoltage(7500, 250); //use scraper to push blocks
    scraperState = 0;
	pros::delay(350);
	leftMotors.move_voltage(8000); //cross
	rightMotors.move_voltage(8200);
	pros::delay(550);
	chassis.sendVoltage(0, 100); //stop for a bit to let it intake
	pros::delay(500);
	leftMotors.move_voltage(6000); //go slow out of park zone
	rightMotors.move_voltage(6200);
	pros::delay(1000);
    odomState = 0;
	intakeState = 2;
	pros::delay(100);
	intakeState = 1;
    pros::delay(500); //go all the way to matchloader to get blocks that rolled
	chassis.sendVoltage(0,10);
	pros::delay(300);
	chassis.sendVoltage(-6000, 600); //back up and put down matchloader to dsr

	//mid goal
	chassis.turnToHeading(180,1000);
	chassis.distanceReset('L', 'B');

	//get one more block
    chassis.moveToPoint(17.83, 17.35, 1500, {}, true); //-21, -24

    //turn and move toward mid goal
    chassis.turnToPoint(6.7, 11.9, 1000, {.forwards = false});
    intakeState = 1;
    chassis.moveToPoint(6.7, 11.9, 1000, {.forwards = false, .minSpeed = 60});
    midGoalState = 1;
    trapdoorState = 1;
    intakeState = 2;
    pros::delay(100);
    intakeState = 1;
    pros::delay(1000);
	lowGoalVel = true;
	pros::delay(750);
	intakeState = 0;

	//veryyyy slowly go out
	chassis.moveDistance(5, 1000, {.maxSpeed = 20});
	chassis.moveDistance(-5, 1000, {.maxSpeed = 20});



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
		chassis.arcade(throttle, turn, true);

		//delay
		pros::delay(10);
	}
}