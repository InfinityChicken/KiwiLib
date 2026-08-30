#include "drivecode/intake.hpp"
#include "drivecode/cascade.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

int intakeState = 0;

bool intakePressed = false;
bool outtakePressed = false;

void updateIntake() {
    // if intake control is pressed
    // and if cascade macro is off
    if (controller.get_digital(intakeControl) && cascadeState != 1 && manualOverride == false) {
        if (!intakePressed) {
            // if it is intakking turn it off
            if(intakeState == 1) {
                intakeState = 0;
            }

            // if it is off or outtaking turn it intaking
            else {
                intakeState = 1;
            }
        }
        // intake was just toggled just now
        intakePressed = true;

    } 
    // intake was not toggled just now
    else {
        intakePressed = false;
    }

    // if outtake control is pressed
    if (controller.get_digital(outtakeControl)) {
        if (!outtakePressed) {
            // if it is outtaking turn it off
            if(intakeState == 2) {
                intakeState = 0;
            }

            // if it is off or intaking turn it outtaking
            else {
                intakeState = 2;
            }
        }
        // outtake was just toggled just now
        outtakePressed = true;

    } 
    // outtake was not toggled just now
    else {
        outtakePressed = false;
    }
}

void runIntake() {
    while (true) {
        // based on our intake state, we toggle it on or off
        switch (intakeState) {
            // off
            case 0:
                intake.move_voltage(0);
                break;
            // intaking
            case 1:
                intake.move_voltage(12000);
                break;
            // outtaking
            case 2:
                intake.move_voltage(-12000);
                break;
        }

        pros::delay(10);
    }
}