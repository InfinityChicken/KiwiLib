#include "main.h"
#include "util.hpp"
#include "intake.hpp"

//motor settings

void motorInit() {
    roller1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    roller2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
}

//sensor settings
void sensorInit() {}

//begin all tasks
void taskInit() {}

//brain task
void runScreen() {

    while(true) {
        lemlib::Pose pose = chassis.getPose();
        pros::screen::print(
            pros::E_TEXT_SMALL,
            1,
            "x: %.3f | y: %.3f | h: %.3f",
            pose.x,
            pose.y,
            pose.theta
        );
        

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

void runController() {
    while (true) {
        if(velValue == 12000)
            controller.set_text(0, 0, "100%");
        else if(velValue == 12000 * 0.75)
            controller.set_text(0, 0, "75%");
    }
}