#include "drivecode/util.hpp"

// drivecode
#include "drivecode/claw.hpp"
#include "drivecode/toggle.hpp"
#include "drivecode/dr4b.hpp"

// initialize motors
void motorInit() {
    reversebar.set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_BRAKE);
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
}

// print screen task
void runScreen() {
    while(true) {
        lemlib::Pose pose = chassis.getPose();

        pros::screen::print(pros::E_TEXT_SMALL, 0, "X: %.3f Y: %.3f Theta: %.3f", pose.x, pose.y, pose.theta);
        // pros::screen::print(pros::E_TEXT_SMALL, 1, "clawOpenPressed: %d clawState: %d", clawOpenPressed, clawState);
        pros::screen::print(pros::E_TEXT_SMALL, 2, "toggleState: %d", toggleState);
        pros::screen::print(pros::E_TEXT_SMALL, 3, "liftHeight: %d", liftHeight);
        pros::screen::print(pros::E_TEXT_SMALL, 4, "manualLiftState: %d manualControl: %d", manualLiftState, manualControl);
        pros::screen::print(pros::E_TEXT_SMALL, 5, "liftMacroState: %d liftMacroPressed: %d", liftMacroState, liftMacroPressed);

        pros::delay(10);
    }
}

// gamepad task
void runConsole() {
    while(true) {
        pros::delay(10);
    }
}