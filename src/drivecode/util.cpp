#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "drivecode/util.hpp"
#include "drivecode/objects.hpp"
#include "sdcard/sdmain.hpp"
#include "drivecode/claw.hpp"
// #include "autonomous/autonSelector.hpp"

void runCascade();

void motorInit() {
    rollerClaw.tare_position();
}

// sensor settings
void sensorInit() {
    vision.clear_led();
    vision.set_exposure(150);
    vision.set_led(4024241);
    vision.set_signature(3, &yellowSig);
    vision.set_signature(2, &blueSig);
    vision.set_signature(1, &redSig);
}

//begin all tasks
void taskInit() {
    if (!pros::competition::is_disabled()) {
        if (!pros::competition::is_autonomous()) {
            pros::Task screenTask(runScreen, "screen task");
        }
    }
}

//brain task
void runScreen() {
    while(true) {
        lemlib::Pose pose = chassis.getPose();

        pros::screen::print(pros::E_TEXT_MEDIUM, 1, "leftFront: %d", leftFront.get_power());
        pros::screen::print(pros::E_TEXT_MEDIUM, 2, "leftMid: %d", leftMid.get_power());
        pros::screen::print(pros::E_TEXT_MEDIUM, 3, "leftBack: %d", leftBack.get_power());
        pros::screen::print(pros::E_TEXT_MEDIUM, 4, "rightFront: %d", rightFront.get_power());
        pros::screen::print(pros::E_TEXT_MEDIUM, 5, "rightMid: %d", rightMid.get_power());
        pros::screen::print(pros::E_TEXT_MEDIUM, 6, "rightBack: %d", rightBack.get_power());

        pros::delay(10);
    }
}

//console task
void runConsole() {
    while(true) {
        pros::delay(10);
    }
}