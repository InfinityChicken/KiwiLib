#include "drivecode/claw.hpp"
#include "drivecode/objects.hpp"
#include <iostream>

int clawState = 0;
bool clawOpenPressed = false;
bool clawClosePressed = false;

void updateClaw() {
    if (controller.get_digital(CONTROL1)) {
        if (!clawOpenPressed) {
            // if it is not rolling in turn it rolling in
            if (clawState != 2) {
                clawState = 2;
            }
            // if it is rolling in turn it off
            else if (clawState == 2) {
                clawState = 0;
            }
        }
        clawOpenPressed = true;
    } 
    else {
        clawOpenPressed = false;
    }

    if (controller.get_digital(CONTROL2)) {
        if (!clawClosePressed) {
            // if it is not rolling in turn it rolling in
            if (clawState != 1) {
                clawState = 1;
            }
            // if it is rolling in turn it off
            else if (clawState == 1) {
                clawState = 0;
            }

        }
        clawClosePressed = true;
    } 
    else {
        clawClosePressed = false;
    }

    pros::delay(10);
}

void runClaw() {
    while (true) {
        switch (clawState) {
            // claw off
            case 0: {
                clawRoller.move_voltage(0);
                break;
            }

            // claw rolling in
            case 1: {
                clawRoller.move_voltage(12000);
                break;
            }

            // claw rolling out
            case 2: {
                clawRoller.move_voltage(-6000);
                break;
            }
        }
        
        pros::delay(10);
    }
}