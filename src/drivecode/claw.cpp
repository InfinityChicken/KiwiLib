#include "drivecode/claw.hpp"
// #include "pros/misc.h"
#include "drivecode/objects.hpp"

// initialize state variables
int rollerState = 0;
bool rollerPressedIn = false;
bool rollerPressedOut = false;

int clawState = 0;
bool clawPressed = false;

void updateRoller() {
    // if intake control is pressed
    if (controller.get_digital(rollerControlIn)) {
        if (!rollerPressedIn) {
            // if it is on turn it off
            if(rollerState == 1) {
                rollerState = 0;
            }

            // if it is off turn it on
            else {
                rollerState = 1;
            }
        }
        // intake was just toggled just now
        rollerPressedIn = true;

    } 
    // intake was not toggled just now
    else {
        rollerPressedIn = false;
    }

    // if R2 is pressed
    if (controller.get_digital(rollerControlOut)) {
        if (!rollerPressedOut) {
            // if it is on turn it off
            if(rollerState == 2) {
                rollerState = 0;
            }
            
            // if it is off turn it on
            else {
                rollerState = 2;
            }
        }
        // intake was just toggled just now
        rollerPressedOut = true;
        
    }
    // intake was not toggled just now
    else {
        rollerPressedOut = false;
    }
}

void updateClaw() {
    // if flip control is pressed
    if (controller.get_digital(clawControl)) {
        if (!clawPressed) {
            clawState = (clawState + 1) % 2;
        }
        // flip was just toggled just now
        clawPressed = true;

    }
    // flip was not toggled just now
    else {
        clawPressed = false;
    }
}

void runRoller() {
    while (true) {
        // based on our roller state, we toggle it on or off
        switch (rollerState) {
            // intaking
            case 1:
                rollerClaw.move_velocity(200);
                break;
            // outtaking
            case 2:
                rollerClaw.move_velocity(-200);
                break;
            // stop
            case 0: 
                rollerClaw.move_velocity(0);
                break;
        }

        pros::delay(10);
    }
}

void runClaw() {
    while (true) {
        // based on our claw state, we toggle to open and close
        switch (clawState) {
            // open
            case 0:
                pistonClaw.set_value(false);
                break;
            // close
            case 1:
                pistonClaw.set_value(true);
                break;
        }

        pros::delay(10);
    }
}