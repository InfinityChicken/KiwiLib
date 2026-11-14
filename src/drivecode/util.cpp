#include "drivecode/util.hpp"

// drivecode
#include "drivecode/claw.hpp"
#include "drivecode/toggle.hpp"
#include "drivecode/dr4b.hpp"
#include "pros/misc.h"
#include "util.hpp"
#include <cmath>

// initialize motors
void motorInit() {
    lift.set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_BRAKE);
}

// sensor settings
void sensorInit() {
    
}

// begin all tasks
void taskInit() {
    pros::Task screenTask(runScreen, "screen task");
    pros::Task consoleTask(runConsole, "console task");

    pros::Task clawTask(runClaw, "claw task");
    pros::Task toggleTask(runToggle, "toggle task");
    pros::Task liftTask(runLift, "dr4b task");
    pros::Task pidLiftTask(runPidLift, "pid lift task");
    pros::Task autoToggleTask(autoToggle, "auto toggle task");
}

// print screen task
void runScreen() {
    while(true) {
        lemlib::Pose pose = chassis.getPose();

        pros::screen::print(pros::E_TEXT_SMALL, 0, "X: %.3f Y: %.3f Theta: %.3f", pose.x, pose.y, pose.theta);
        pros::screen::print(pros::E_TEXT_SMALL, 1, "lift height: %.3f", lemlib::mmToIn(distLiftHeight.get_distance()));
        pros::screen::print(pros::E_TEXT_SMALL, 2, "color: %.3f", toggleOptical.get_hue());
        pros::screen::print(pros::E_TEXT_SMALL, 3, "lift pid target: %.3f", liftTarget);
        pros::screen::print(pros::E_TEXT_SMALL, 6, "1-6 drive motors, 11 claw, 9 toggle, 19+17 lift");

        pros::delay(10);
    }
}

// gamepad task
void runConsole() {
    while(true) {
        pros::delay(10);
    }
}


void liftPIDTuning(float target) {
    bool buttonPressed = false;
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        if (!buttonPressed) {
            if (liftTarget != target) {
                liftTarget = target;
            }
            else if (liftTarget == target) {
                liftTarget = initialHeight;
            }

        }
        buttonPressed = true;
    } 
    else {
        buttonPressed = false;
    }
}

void linearPIDTuning(float target) {
    bool buttonPressed = false;
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        if (!buttonPressed) {
            if (std::abs(chassis.getPose().y - target) < 0.5) {
                chassis.moveToPoint(0, target, 1000);
            }
            else {
                chassis.moveToPoint(0, 0, 1000, {.forwards = false});
            }

        }
        buttonPressed = true;
    } 
    else {
        buttonPressed = false;
    }
}

void angularPIDTuning(float target) {
    bool buttonPressed = false;
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        if (!buttonPressed) {
            if (std::abs(chassis.getPose().theta - target) < 0.5) {
                chassis.turnToHeading(target, 1000);
            }
            else {
                chassis.turnToHeading(0, 1000);
            }

        }
        buttonPressed = true;
    } 
    else {
        buttonPressed = false;
    }
}