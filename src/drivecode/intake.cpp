#include "drivecode/intake.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

int intakeState = 0;

bool intakePressed = false;

// void updateIntake() {

//     pros::screen::print(pros::E_TEXT_MEDIUM, 2, "L1: %d", controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1));

//     // if intake control is pressed
//     if (controller.get_digital(intakeControl)) {
//         if (!intakePressed) {
//             // modulo fun
//             intakeState = (intakeState + 1) % 3;
//         }
//         // intake was just toggled just now
//         intakePressed = true;

//     } 
//     // intake was not toggled just now
//     else {
//         intakePressed = false;
//     }
// }

void updateIntake() {
    bool pressed = controller.get_digital(intakeControl);

    pros::screen::print(pros::E_TEXT_MEDIUM, 2,
                        "Pressed: %d  State: %d",
                        pressed, intakeState);

    if (pressed) {
        if (!intakePressed) {
            intakeState = (intakeState + 1) % 3;
        }

        intakePressed = true;
    } else {
        intakePressed = false;
    }
}

void runIntake() {
    while (true) {
        // based on our intake state, we toggle it on or off
        switch (intakeState) {
            // intaking
            case 1:
                intake.move_voltage(12000);
                break;
            // outtaking
            case 2:
                intake.move_voltage(-12000);
                break;
            // off
            case 0:
                intake.move_voltage(0);
                break;
        }

        pros::delay(10);
    }
}