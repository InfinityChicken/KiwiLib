#include "lemlib/timer.hpp"
#include "main.h"
#include "pros/misc.h"
#include "drivecode/intake.hpp"

int sortState = 0;
bool currentCorrectColor;
bool prevCorrectColor;
int prevIntakeState;

int intakeState = 0;
int toggleState = 0;

int prevState = 0;

bool intakePressed = false;
bool outtakePressed = false;
bool midPressed = false;

bool topStalled = false;
bool midStalled = false;

int topTicks = 0;
int midTicks = 0;

// Jam detection threshold (mA) — tune as needed
static const int JAM_CURRENT = 2500;

void runIntake() {
    while (true) {
        switch(intakeState) {
            case 0: { // stopped
                topIntake.move_voltage(0);
                midIntake.move_voltage(0);
                bottomIntake.move_voltage(0);
                break;
            }

            case 1: { // full intake (R2 hold)
                topIntake.move_voltage(12000);
                midIntake.move_voltage(12000);
                bottomIntake.move_voltage(12000);
                break;
            }

            case 2: { // outtake
                topIntake.move_voltage(-12000*0.35);
                midIntake.move_voltage(-12000);
                bottomIntake.move_voltage(-12000*0.75);
                break;
            }

            case 3: { // store/intake (L1 toggle)
                topIntake.move_voltage(12000);
                midIntake.move_voltage(12000);
                bottomIntake.move_voltage(12000);
                break;
            }

            case 4: { // mid goal score (Y toggle)
                if (prevState != intakeState) { //outtake for mid
                    topIntake.move_voltage(-12000);
                    midIntake.move_voltage(-12000);
                    bottomIntake.move_voltage(-12000);

                    pros::delay(250);

                    midTicks = 0;
                    topTicks = 0;
                    midStalled = false;
                    topStalled = false;
                }

                topIntake.move_voltage(-12000);
                midIntake.move_voltage(12000);
                bottomIntake.move_voltage(12000);
                break;
            }

            case 5: { //special auto state for filling
                topIntake.move_voltage(0);
                midIntake.move_voltage(0);
                bottomIntake.move_voltage(12000);
            }

        }

        if(intakeState > 0) {
            if(std::fabs(midIntake.get_actual_velocity()) < 25) {
                midTicks++;
            } else {
                midTicks = 0;
            }

            if(std::fabs(topIntake.get_actual_velocity()) < 25) {
                topTicks++;
            } else {
                topTicks = 0;
            }
        }

        if(sortState == 1) { //sort out red, score blue
            if(color.get_hue() < 20 && color.get_hue() > 0 || color.get_hue() > 340 && color.get_hue() < 356) { //check for color
                prevCorrectColor = currentCorrectColor;
                currentCorrectColor = false;
                std::cout<<"wrong color detected\n";
            } else if(color.get_hue() < 220 && color.get_hue() > 200) {
                prevCorrectColor = currentCorrectColor;
                currentCorrectColor = true;
                std::cout<<"right color detected\n";
            }
        } else if(sortState == 2) {
            if(color.get_hue() < 20 && color.get_hue() > 0 || color.get_hue() > 340 && color.get_hue() < 356) { //check for color
                prevCorrectColor = currentCorrectColor;
                currentCorrectColor = true;
                std::cout<<"right color detected\n";
            } else if(color.get_hue() < 220 && color.get_hue() > 200) {
                prevCorrectColor = currentCorrectColor;
                currentCorrectColor = false;
                std::cout<<"wrong color detected\n";
            }
        }

        if(prevCorrectColor != currentCorrectColor) {
            if(intakeState == 1 || intakeState == 3) { //sort through mid
                prevIntakeState = intakeState;
                intakeState = 5;
            } else if(intakeState == 5) {
                intakeState = prevIntakeState;
            }
            if (intakeState == 4) { //sort through long
                intakeState = 6;
            } else if (intakeState == 6) {
                intakeState = 4;
            }
        }

        if(prevState != intakeState) {
            midTicks = 0;
            topTicks = 0;
            midStalled = false;
            topStalled = false;
        }

        if(midTicks > 25) midStalled = true;
        if(topTicks > 25) topStalled = true;
        if(midStalled == true) midIntake.move(0);
        if(topStalled == true) topIntake.move(0);

        prevState = intakeState;
        pros::delay(10);
    }
}

void updateIntake() {
    //l1 intake store, l2 outtake, r1 score, y mid score 

    // L1: intake/store toggle
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        if (!intakePressed) {
            if (toggleState == 3) {
                toggleState = 0;
            } else {
                toggleState = 3;
                trapdoorState = 0;
            }
        }
        intakePressed = true;
    } else {
        intakePressed = false;
    }

    // L2: outtake toggle
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        if (!outtakePressed) {
            if (toggleState == 2) {
                toggleState = 0;
            } else {
                toggleState = 2;
            }
        }
        outtakePressed = true;
    } else {
        outtakePressed = false;
    }

    // R1: hold override (scoring)
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        intakeState = 1;
        trapdoorState = 1;
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) { //Y hold override (mid goal score)
        intakeState = 4;
        trapdoorState = 0;
    } else {
        intakeState = toggleState; //update intake state to toggle state
    }
}