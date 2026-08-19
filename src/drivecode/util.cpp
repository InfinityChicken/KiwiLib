#include "drivecode/util.hpp"
#include "autonomous/autonSelector.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "drivecode/util.hpp"
#include "drivecode/objects.hpp"

void motorInit() {
    // set current roller claw "absolute" position to zero
    rollerClaw.tare_position();

    // set current cascade "absolute" position to zero
    cascade.tare_position();

    // set chain bar "absolute" position to zero, assuming you 
    // are resting it against something rigid
    chainBar.tare_position();
}

//sensor settings
void sensorInit() {
    vision.clear_led();
    vision.set_exposure(150);
    vision.set_led(4024241);

    vision.set_signature(0, &yellowSig);
    vision.set_signature(0, &blueSig);
    vision.set_signature(0, &redSig);
}

//begin all tasks
void taskInit() {
    pros::Task screenTask(runScreen, "screen task");
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

        // pros::screen::print(pros::E_TEXT_MEDIUM, 1, "cascadeState: %d", cascadeState);
        // pros::screen::print(pros::E_TEXT_MEDIUM, 2, "rollerState: %d", rollerState);
        // pros::screen::print(pros::E_TEXT_MEDIUM, 3, "resetState: %d", resetState);
        // pros::screen::print(pros::E_TEXT_MEDIUM, 4, "chainBarState: %d", chainBarState);
        // pros::screen::print(pros::E_TEXT_MEDIUM, 5, "rollerState: %d", flipState);
        // pros::screen::print(pros::E_TEXT_MEDIUM, 6, "controlType: %d", controlType);
        
        pros::delay(50);
    }
}

//console task
void runConsole() {
    while(true) {
        pros::delay(50);
    }
}