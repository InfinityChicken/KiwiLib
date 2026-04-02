#include "main.h"
#include "pros/misc.h"
#include "drivecode/intake.hpp"

int intakeState = 0;

bool intakePressed = false;
bool outtakePressed = false;
bool scoringPressed = false;

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

            case 1: { // full intake
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

            case 3: { // store/intake (L1)
                // jam detection: if top roller stalls (e.g. closing on a ball),
                // open trapdoor and reverse to clear, then re-close
                if (topIntake.get_current_draw() > JAM_CURRENT) {
                    trapdoorState = 1;
                    topIntake.move_voltage(-4000);
                    midIntake.move_voltage(0);
                    bottomIntake.move_voltage(0);
                    pros::delay(150);
                    trapdoorState = 0;
                } else {
                    topIntake.move_voltage(12000);
                    midIntake.move_voltage(12000);
                    bottomIntake.move_voltage(12000);
                }
                break;
            }

            case 4: { // scoring (R2 hold)
                topIntake.move_voltage(12000 * 0.65);
                midIntake.move_voltage(12000);
                bottomIntake.move_voltage(12000);
                break;
            }
        }

        pros::delay(10);
    }
}

void updateIntake() {

    // L1: intake/store — toggle, close trapdoor to keep blocks in
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        if (!intakePressed) {
            if (intakeState == 3) {
                intakeState = 0;
            } else {
                intakeState = 3;
                trapdoorState = 0;
            }
        }
        intakePressed = true;
    } else {
        intakePressed = false;
    }

    // R2: score on hold — brief outtake on press, then scoring state while held
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        if (!scoringPressed) {
            intakeState = 2;
            pros::delay(100);
        }
        intakeState = 4;
        scoringPressed = true;
    } else if (intakeState == 4) {
        intakeState = 0;
        scoringPressed = false;
    }

    // L2: outtake everything + raise intake lift
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        if (!outtakePressed) {
            if (intakeState == 2) {
                intakeState = 0;
                intakeLiftState = 0;
            } else {
                intakeState = 2;
                intakeLiftState = 1;
            }
        }
        outtakePressed = true;
    } else {
        outtakePressed = false;
    }

}
