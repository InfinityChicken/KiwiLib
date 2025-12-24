#include "main.h"
#include "pros/rtos.hpp"
#include "drivecode/util.hpp"

//motor settings

void motorInit() {
    roller1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    roller2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

//sensor settings
void sensorInit() {}

//begin all tasks
void taskInit() {
    pros::Task intakeTask(runIntake, "intake task");
    pros::Task pistonTask(runPistons, "piston task");
    pros::Task screenTask(runIntake, "screen task");
    pros::Task controllerTask(runIntake, "controller task");
    // pros::Task consoleTask(runConsole, "console task");
}

//brain task
void runScreen() {
    while(true) {
        
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
        if(velValue == 12000)
            controller.set_text(0, 0, "100%");
        else if(velValue == 12000 * 0.75)
            controller.set_text(0, 0, "75%");

        pros::delay(50);
    }
}