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

	//initial stuff for dist reset
	chassis.setPose(-1,1,0); //-1, 1, 0
	scraperState = 1;
	pros::delay(1000);

	//dist reset
	chassis.distanceReset('L', 'F');
    intakeState = 1;
    scraperState = 0;

	//move to park
	chassis.moveToPose(-12, 65, 84, 2000, {.lead = 0.58}); //curve to park zone
	odomState = 1; //odom up
	scraperState = 1; 
	pros::delay(100);

    //use scraper to push blocks
	chassis.sendVoltage(6000, 400); //7500
    scraperState = 0;
    intakeState = 3;
	pros::delay(175);

    //initial cross
    leftMotors.move_voltage(8000);
	rightMotors.move_voltage(8400);
    pros::delay(500);

	//pause in park zone
    leftMotors.move_voltage(0);
	rightMotors.move_voltage(0);
    pros::delay(250);

    //go faster out of park
    leftMotors.move_voltage(8000);
	rightMotors.move_voltage(8400);
    pros::delay(700);

	//cross and go to matchloader to intake all blocks
	while (true) {
        if (distFrontRight.get_distance() / 25.4 <= 35) {
            leftMotors.move_voltage(0);
			rightMotors.move_voltage(0);
			break;
        } else {
			leftMotors.move_voltage(4500);
			rightMotors.move_voltage(4700); //prev 10000
		}
        pros::delay(10);
    } 
	pros::delay(300);

	//back up from ml
	chassis.moveDistance(-16, 1000, {.forwards = false});
    odomState = 0;

    if(interrupt) {
        return;
    }

	//mid goal
	chassis.swingToHeading(196, lemlib::DriveSide::RIGHT, 1000);
	chassis.distanceReset('L', 'B');

	//get one more block
    //chassis.turnToHeading(195, 1000); //187 before
	//chassis.moveToPoint(19, 19.75, 1500); //19, 19.75
	chassis.moveToPose(19, 19.25, 195, 1000, {.lead = 0});
    intakeState = 0;

    //turn and move toward mid goal
    chassis.turnToPoint(-7, -1, 1000, {.forwards = false});
    //chassis.turnToHeading(45, 1000);
	intakeState = 3;
	//chassis.moveToPoint(7.3, 12.3, 1000, {.forwards = false, .minSpeed = 60}, true);
    chassis.moveDistance(-8.5, 1000, {.forwards = false, .minSpeed = 60});
	//pros::delay(500);
    midGoalState = 1;
	chassis.turnToHeading(45, 1000, {}, true);
    intakeState = 2;
    pros::delay(100); //antijam time
	midGoalSpeed = 12000 * 0.7;
    intakeState = 1;
    pros::delay(1400); //score time
	lowGoalVel = true;
	pros::delay(600);
	intakeState = 0;
	lowGoalVel = false;

    if(interrupt) {
        return;
    }

	//veryyyy slowly go out
	chassis.moveDistance(3, 1000, {.maxSpeed = 10});
	chassis.moveDistance(-2.75, 1000, {.maxSpeed = 5});

	//chassis.moveDistance(4,2000);


	//skills97();
	//SAWP();
	//sevenBlockPushLeft();
	//sevenBlockPushRight(); 
	//fourBlockPushLeft();
	//fourBlockPushRight();
	//leftSplitPush();
}

void opcontrol() {
	// chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
	// skills97();

	//driver
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	intakeState = 0;
	velValue = 12000;
	midGoalSpeed = 12000 * 0.7; // mid goal 80% reset for driver

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
		chassis.arcade(throttle, turn, true, 0.7);

		//delay
		pros::delay(10);
	}
}