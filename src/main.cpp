// imports

// main.h
#include "main.h"

// autonomous
#include "autonomous/autonomous.hpp"
#include "autonomous/autonSelector.hpp"

// drivecode
#include "drivecode/objects.hpp"
#include "drivecode/util.hpp"
#include "drivecode/cascade.hpp"
#include "drivecode/claw.hpp"

// lemlib & pros
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/intersect.hpp"
#include "pros/motors.h"
#include "pros/misc.h"
#include "pros/apix.h"

// sdcard
#include "sdcard/sdtest.hpp"
#include "sdcard/sdmain.hpp"

// anti tip and all bs stuff
static constexpr float IMU_PITCH_SIGN = -1.0; // flip the sign of the pitch if the bot is flipped, shudnt be changed


void on_center_button() {

}

void initialize() {
	// reset the chassis position
	chassis.calibrate();
	chassis.setPose(0,0,0);

	// initialize the motors
	motorInit();

	// initialize the sensors
	sensorInit();

	// initialize the tasks after hardware initialization
	taskInit();
	

	// run autonSelector during the set up period
	// autonSelector();
}

void disabled() {

}

void competition_initialize() {

}

void autonomous() {
	// set the autonomous to brake
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

	// runAuton();
	drc();
} 

void opcontrol() {
	// set the drive to coast
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	static bool antiTipping = false;

	while (true) {
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		// fetch the current tilt of the bot during driver
		float pitch = imu.get_pitch() * IMU_PITCH_SIGN;

		// if bot tip is over 15 degrees(left or right), set antiTipping mode to true and rest the pid
		if (!antiTipping && (pitch > 15 || pitch < -15)) {
			antiTipping = true;
			antiTipPID.reset();
		}

		// early exit if tip is within 3 degrees 
		if (antiTipping && (pitch < 3) && (pitch > -3)) {
			antiTipping = false;
		}

		// manual override exit
		if (antiTipping && (throttle != 0 || turn != 0)) {
			antiTipping = false;
		}


		// execute if antiTip is true (the bot is tipping)
		// P and D cuz forums online said I causes more error
		if (antiTipping) {
			float antiTipPIDOut = antiTipPID.update(0.0 - pitch, false);

			// if the PID out is over motor threshold then js set it to max threshold
			if (antiTipPIDOut > 127) {
				antiTipPIDOut = 127;
			}
			if (antiTipPIDOut < -127) {
				antiTipPIDOut = -127;
			}

			// now execute the PIDout
			chassis.arcade(int(antiTipPIDOut), 0);



		} else {
			// if not tipping just throttle
			chassis.arcade(throttle, turn);
		}



		// gourav's favourite two stick arcade configuration
		updateCascade();
		updateChainBar();
		updateCascadeFunctions();
		
		updateRoller();
		updateClaw();

		pros::delay(10);
	}
}