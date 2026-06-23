#include "main.h"
#include "drivecode/objects.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"
#include "drivecode/util.hpp"
#include "pros/misc.h"
#include "lemlib/intersect.hpp"
#include "autonomous/autonomous.hpp"
#include "sdcard/sdtest.hpp"
#include "sdcard/sdmain.hpp"

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

	override_june();
} 

void opcontrol() {
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

	char xSensor = 'R';
	char ySensor = 'F';
	int quadrant = 1;
	uint32_t startTime = pros::millis();
	uint32_t lastPrint = 0;

	// quadrant sign lookup: index 1-4
	const float qx[] = {0, 1, -1, -1,  1};
	const float qy[] = {0, 1,  1, -1, -1};
	const char* qLabel[] = {"", "+,+", "-,+", "-,-", "+,-"};

	while (true) {
		int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		chassis.arcade(throttle, turn);

		// hold L1 + d-pad to pick X sensor, L2 + d-pad to pick Y sensor
		bool l1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
		bool l2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);

		if (l1) {
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))    xSensor = 'F';
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))  xSensor = 'B';
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))  xSensor = 'L';
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) xSensor = 'R';
		} else if (l2) {
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))    ySensor = 'F';
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))  ySensor = 'B';
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))  ySensor = 'L';
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) ySensor = 'R';
		}

		// R1 cycles quadrant
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
			quadrant = (quadrant % 4) + 1;
		}

		// A executes the reset
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
			lemlib::Pose cur = chassis.getPose();
			chassis.setPose(qx[quadrant], qy[quadrant], cur.theta);
			chassis.distanceReset(xSensor, ySensor);
			lemlib::Pose resetPose = chassis.getPose();
			pros::screen::print(pros::E_TEXT_MEDIUM, 9,  "Last DSR: X=%c Y=%c Q%d", xSensor, ySensor, quadrant);
			pros::screen::print(pros::E_TEXT_MEDIUM, 10, "-> X:%.2f Y:%.2f", resetPose.x, resetPose.y);
		}

		pros::delay(10);
	}
}