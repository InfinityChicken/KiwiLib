#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include <string>
#include "drivecode/util.hpp"
#include <iomanip>

//motor settings
void motorInit() {
    topIntake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    bottomIntake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

//sensor settings
void sensorInit() {}

//begin all tasks
void taskInit() {
    pros::Task intakeTask(runIntake, "intake task");
    pros::Task pistonTask(runPistons, "piston task");
    pros::Task screenTask(runScreen, "screen task");
}

//brain task
void runScreen() {
    while(true) {
        lemlib::Pose pose = chassis.getPose();

        pros::screen::print(pros::E_TEXT_MEDIUM, 1, "X: %.3f", pose.x);
        pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Y: %.3f", pose.y);
        pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Theta: %.3f", pose.theta);
        pros::screen::print(pros::E_TEXT_MEDIUM, 4, "top wattage: %.3f", topIntake.get_power());
        pros::screen::print(pros::E_TEXT_MEDIUM, 5, "bottom wattage: %.3f", bottomIntake.get_power());
        pros::screen::print(pros::E_TEXT_MEDIUM, 6, "front left dist: %.3f", distFrontLeft.get_distance()/25.4);
        pros::screen::print(pros::E_TEXT_MEDIUM, 7, "front right dist: %.3f", distFrontRight.get_distance()/25.4);
        pros::screen::print(pros::E_TEXT_MEDIUM, 8, "back dist: %.3f", distBack.get_distance()/25.4);
        pros::screen::print(pros::E_TEXT_MEDIUM, 9, "left dist: %.3f", distLeft.get_distance()/25.4);
        pros::screen::print(pros::E_TEXT_MEDIUM, 10, "right dist: %.3f", distRight.get_distance()/25.4);

        pros::delay(50);
    }
}

//console task
void runConsole() {
    while(true) {
        std::cout<<drivetrain.leftMotors->get_voltage()<<"\n";
        std::cout<<drivetrain.rightMotors->get_voltage()<<"\n\n";

        pros::delay(50);
    }
}

void runController() {
    while (true) {}
}
