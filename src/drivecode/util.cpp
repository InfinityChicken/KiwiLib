#include "main.h"
#include "pros/rtos.hpp"
#include <string>
#include "drivecode/util.hpp"

//motor settings

void motorInit() {
    leftIntake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightIntake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

//sensor settings
void sensorInit() {}

//begin all tasks
void taskInit() {
    pros::Task intakeTask(runIntake, "intake task");
    pros::Task pistonTask(runPistons, "piston task");
    pros::Task screenTask(runScreen, "screen task");
    pros::Task controllerTask(runController, "controller task");
    pros::Task autoScoreTask(runAutoScore, "autoscore task");
    // pros::Task consoleTask(runConsole, "console task");
}

//brain task
void runScreen() {
    while(true) {

        pros::screen::print(pros::E_TEXT_MEDIUM, 1, "left wattage: %.3f", leftIntake.get_power());
        pros::screen::print(pros::E_TEXT_MEDIUM, 2, "right wattage: %.3f", rightIntake.get_power());
        
        pros::delay(50);
    }
}

//console task
void runConsole() {
    while(true) {
        lemlib::Pose pose = chassis.getPose();

        std::cout<<"X: "<<std::to_string(pose.x)<<"\n";
        std::cout<<"Y: "<<std::to_string(pose.y)<<"\n";
        std::cout<<"Theta: "<<std::to_string(pose.theta)<<"\n";

        pros::delay(500);
    }
}

//controller text task
void runController() {
    while (true) {
        controller.set_text(0, 0, std::to_string(velValue/12000.0*100)+"%");
        pros::delay(50);
    }
}