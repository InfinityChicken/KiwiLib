#include "lemlib/timer.hpp"
#include "main.h"
#include "pros/misc.h"
#include "drivecode/intake.hpp"

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
                topIntake.move_voltage(-12000);
                midIntake.move_voltage(-12000);
                bottomIntake.move_voltage(-12000);
                break;
            }

            case 3: { // store/intake (L1 toggle)
                topIntake.move_voltage(12000);
                midIntake.move_voltage(12000);
                bottomIntake.move_voltage(12000);
                break;
            }

            case 4: { // mid goal score (Y toggle)
                topIntake.move_voltage(-12000);
                midIntake.move_voltage(12000);
                bottomIntake.move_voltage(12000);
                break;
            }
        }

        // if(intakeState > 0) {
        //     if(midIntake.get_actual_velocity() < 50) {
        //         midTicks++;
        //     } else {
        //         midTicks = 0;
        //     }

        //     if(topIntake.get_actual_velocity() < 50) {
        //         topTicks++;
        //     } else {
        //         topTicks = 0;
        //     }
        // }

        // if(prevState != intakeState) {
        //     midTicks = 0;
        //     topTicks = 0;
        //     midStalled = false;
        //     topStalled = false;
        // }

        // if(midTicks > 25) {
        //     midStalled = true;
        // }

        // if(topTicks > 25) {
        //     topStalled = true;
        // }

        // if(midStalled == true) {
        //     midIntake.move(0);
        // }
        
        // if(topStalled == true) {
        //     topIntake.move(0);
        // }

        // prevState = intakeState;
        // pros::delay(10);
    }
}

void updateIntake() {

    // L1: intake/store toggle
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        if (!intakePressed) {
            if (toggleState == 3) {
                toggleState = 0;
                // trapdoorState = 0; //TODO: intake turning off does not activate trapdoor
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
                intakeLiftState = 0; 
            } else {
                toggleState = 2;
                intakeLiftState = 1;
            }
        }
        outtakePressed = true;
    } else {
        outtakePressed = false;
    }

    // Y: mid goal score toggle
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
        if (!midPressed) {
            if (toggleState == 4) {
                toggleState = 0;
            } else {
                toggleState = 4;
                trapdoorState = 0; //TODO: mid score closes trapdoor
            }
        }
        midPressed = true;
    } else {
        midPressed = false;
    }

    // R2: hold override (scoring)
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        intakeState = 1;
        trapdoorState = 1;
    } else {
        intakeState = toggleState;
    }
}