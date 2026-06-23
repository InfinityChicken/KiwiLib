#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "drivecode/util.hpp"
#include "drivecode/objects.hpp"
#include "sdcard/sdmain.hpp"

void motorInit() {
}

//sensor settings
void sensorInit() {}

//begin all tasks
void taskInit() {
    pros::Task screenTask(runScreen, "screen task");
    pros::Task sdWriteTask(sdWriter::runWriter, "sd write task");
}

//brain task
void runScreen() {
    while(true) {
        lemlib::Pose pose = chassis.getPose();

        pros::screen::print(pros::E_TEXT_MEDIUM, 1, "X: %.3f", pose.x);
        pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Y: %.3f", pose.y);
        pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Theta: %.3f", pose.theta);
        pros::screen::print(pros::E_TEXT_MEDIUM, 4, "Front: %.2f in", distFront.get() / 25.4);
        pros::screen::print(pros::E_TEXT_MEDIUM, 5, "Right: %.2f in", distRight.get() / 25.4);
        pros::screen::print(pros::E_TEXT_MEDIUM, 6, "Left:  %.2f in", distLeft.get() / 25.4);
        pros::screen::print(pros::E_TEXT_MEDIUM, 7, "Back:  %.2f in", distBack.get() / 25.4);

        pros::delay(500);
    }
}

//console task
void runConsole() {
    while(true) {
        pros::delay(50);
    }
}