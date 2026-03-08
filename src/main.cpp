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

	// //move to park
	// chassis.moveToPose(-24, 63.25, 82, 2000, {.lead = 0.48}, true);    intakeState = 2; // anti jam
    // pros::delay(125);
    // intakeState = 1;
    // chassis.waitUntilDone();
    // std::cout<<"X: "<<std::to_string(chassis.getPose().x)<<"\n";
    // std::cout<<"Y: "<<std::to_string(chassis.getPose().y)<<"\n";
    // std::cout<<"Theta: "<<std::to_string(chassis.getPose().theta)<<"\n";
    // //chassis.turnToHeading(90, 250);
    // while(true) {
    //     if(distBack.get_distance() / 25.4 >= 41.5) {
    //         leftMotors.move_voltage(0);
	//         rightMotors.move_voltage(0);
    //         break;
    //     } else {
    //         leftMotors.move_voltage(5000);
	//         rightMotors.move_voltage(6000);
    //         scraperState = 0;
    //     }
    //     pros::delay(10);
    // }
    // chassis.turnToHeading(90, 250);
    // // chassis.moveToPoint(-12, 63, 500);
    // // if(distBack.get_distance() / 25.4 >= 44) {
    // //     chassis.moveDistance(2, 500);
    // // } 
	// odomState = 1; //odom up
    // pros::delay(100);
	// scraperState = 1; 
	// pros::delay(200);

    // //use scraper to push blocks
	// chassis.sendVoltage(6000, 400); //7500
    // //chassis.moveToPoint(-11, chassis.getPose().y, 500, {.minSpeed = 60});
    // scraperState = 0;
    // intakeState = 3;
	// pros::delay(175);

    // //initial cross
    // leftMotors.move_voltage(8200);
	// rightMotors.move_voltage(8600);
    // pros::delay(450);

	// //pause in park zone
    // leftMotors.move_voltage(0);
	// rightMotors.move_voltage(0);
    // pros::delay(850); //TODO: prev 750

    // //go slower out of park
    // leftMotors.move_voltage(7000);
	// rightMotors.move_voltage(7400);
    // pros::delay(800);

	// //cross and go to matchloader to intake all blocks
	// while (true) {
    //     if (distFrontRight.get_distance() / 25.4 <= 35) {
    //         leftMotors.move_voltage(0);
	// 		rightMotors.move_voltage(0);
	// 		break;
    //     } else {
	// 		leftMotors.move_voltage(4500);
	// 		rightMotors.move_voltage(4700); //prev 10000
	// 	}
    //     pros::delay(10);
    // } 
	// pros::delay(300);

	// //back up from ml
	// chassis.moveDistance(-16, 1000, {.forwards = false});
    // odomState = 0;

    // if(interrupt) {
    //     return;
    // }

	// //mid goal
	// chassis.swingToHeading(198, lemlib::DriveSide::RIGHT, 1000);
	// chassis.distanceReset('L', 'B');

	// //get one more block
    // //chassis.turnToHeading(195, 1000); //187 before
	// //chassis.moveToPoint(19, 19.75, 1500); //19, 19.75
	// chassis.moveToPose(19, 19.25, 197, 1000, {.lead = 0});
    // intakeState = 0;

    // //turn and move toward mid goal
    // chassis.turnToPoint(-7, -1, 1000, {.forwards = false});
    // //chassis.turnToHeading(45, 1000);
	// intakeState = 3;
	// //chassis.moveToPoint(7.3, 12.3, 1000, {.forwards = false, .minSpeed = 60}, true);
    // chassis.moveDistance(-7.5, 1000, {.forwards = false, .minSpeed = 60});
	// //pros::delay(500);
    // midGoalState = 1;
	// chassis.turnToHeading(45, 1000, {}, true);
    // intakeState = 2; // anti jam
    // pros::delay(125);
    // intakeState = 5;
    // pros::delay(2350); // score
	// intakeState = 0;

    // if(interrupt) {
    //     return;
    // }

	// //veryyyy slowly go out
	// chassis.moveDistance(3, 1000, {.maxSpeed = 10});
	// chassis.moveDistance(-3, 1000, {.maxSpeed = 5});



	//skills97();
	//SAWP();
	//sevenBlockPushLeft();
	//sevenBlockPushRight(); 
	//fourBlockPushLeft();
	//fourBlockPushRight();
	//leftSplitPush();
	counterSAWP();
}

void opcontrol() {
	// chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
	// skills97();

	//driver
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	intakeState = 0;

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