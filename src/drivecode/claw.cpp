#include "drivecode/claw.hpp"
#include "drivecode/objects.hpp"
#include <iostream>

int clawState = 0;
bool clawSpinPressed = false;
bool clawPressed = false;

int tempRoller = 0;

void updateClaw() {
    // constantly checks if clawButton held; if not then set claw to temp roller
    if (controller.get_digital(clawButton)) {
        clawState = 2;
        clawPressed = true;

    } else {
        if(clawPressed) {
            clawState = tempRoller;
            clawPressed = false;
        }
    }

    // uses toggle logic to set tempRoller, if clawState=2 and clawButton no longer held-->goes back to tempRoller last saved 
    // by the toggle below
    if (controller.get_digital(clawSpinToggle)) {
        if (!clawSpinPressed) {
            // if it is not rolling in turn it rolling in
            if (clawState != 1) {
                clawState = 1;
                tempRoller = clawState;
            }
            // if it is rolling in turn it off
            else if (clawState == 1) {
                clawState = 0;
                tempRoller = clawState;
            }

        }
        clawSpinPressed = true;
    } 
    else {
        clawSpinPressed = false;
    }

    pros::delay(10);
}

void runClaw() {
    while (true) {
        switch (clawState) {
            // claw off
            case 0: {
                claw.move_voltage(0);
                break;
            }

            // claw rollers turning inwards (closed)
            case 1: {
                claw.move_voltage(12000);
                break;
            }

            // claw rollers turning outwards (open)
            case 2: {
                claw.move_voltage(-6000);
                break;
            }
        }
        
        pros::delay(10);
    }

}