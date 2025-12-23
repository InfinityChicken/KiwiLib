#include "main.h"
#include "util.hpp"

//motor settings
void motorInit() {}

//sensor settings
void sensorInit() {}

//begin all tasks
void taskInit() {}

//brain task
void runScreen() {

    while(true) {
        lemlib::Pose pose = chassis.getPose();
        pros::screen::print(pros::E_TEXT_MEDIUM, 1, "x pos: %.3f", pose.x);
        pros::screen::print(pros::E_TEXT_MEDIUM, 2, "y pos: %.3f", pose.y);
        pros::screen::print(pros::E_TEXT_MEDIUM, 3, "heading: %.3f", pose.theta);

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
    while (true) {}
}