#include "drivecode/util.hpp"
#include "autonomous/autonSelector.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "drivecode/util.hpp"
#include "drivecode/objects.hpp"
#include "pros/screen.h"

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

void printMotorVoltages(int line) {
    pros::screen::print(pros::E_TEXT_SMALL, line+0, "leftFront: %d", leftFront.get_power());
    pros::screen::print(pros::E_TEXT_SMALL, line+1, "leftMid: %d", leftMid.get_power());
    pros::screen::print(pros::E_TEXT_SMALL, line+2, "leftBack: %d", leftBack.get_power());
    pros::screen::print(pros::E_TEXT_SMALL, line+3, "rightFront: %d", rightFront.get_power());
    pros::screen::print(pros::E_TEXT_SMALL, line+4, "rightMid: %d", rightMid.get_power());
    pros::screen::print(pros::E_TEXT_SMALL, line+5, "rightBack: %d", rightBack.get_power());
}

//brain task
void runScreen() {
    while(true) {
        lemlib::Pose pose = chassis.getPose();

        // printMotorVoltages(0)

        pros::screen::print(pros::E_TEXT_SMALL, 0, "-- CASCADE STATES --");
        pros::screen::print(pros::E_TEXT_SMALL, 1, "cascadeState: %d", cascadeState);
        pros::screen::print(pros::E_TEXT_SMALL, 2, "chainBarState: %d", chainBarState);
        pros::screen::print(pros::E_TEXT_SMALL, 3, "resetState: %d", resetState);
        pros::screen::print(pros::E_TEXT_SMALL, 4, "controlType: %d", controlType);

        pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, 5, "-- CLAW STATES --");
        pros::screen::print(pros::E_TEXT_SMALL, 6, "rollerState: %d", rollerState);
        pros::screen::print(pros::E_TEXT_SMALL, 7, "flipState: %d", flipState);
        pros::screen::print(pros::E_TEXT_SMALL, 8, "clawState: %d", clawState);
        pros::screen::print(pros::E_TEXT_SMALL, 9, "controlType: %d", controlType);

        pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, 10, "-- PIN FROM WALL STATES --");
        pros::screen::print(pros::E_TEXT_SMALL, 11, "pinWallState: %d", pinWallState);
        
        pros::delay(50);
    }
}

//console task
void runConsole() {
    while(true) {
        pros::delay(50);
    }
}