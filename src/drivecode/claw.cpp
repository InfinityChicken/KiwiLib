#include "drivecode/claw.hpp"
// #include "pros/misc.h"
#include "drivecode/objects.hpp"

// initialize state variables
int rollerState = 0;
bool rollerPressedIn = false;
bool rollerPressedOut = false;

int clawState = 0;
bool clawPressed = false;

// TODO: changed control for gourav
// TODO: toggle without roll out
// TODO: Modulo fun added instead its just easier for me
void updateRoller() {
    // if intake control is pressed
    if (controller.get_digital(rollerInControl)) {
        if (!rollerPressedIn) {
            rollerState = (rollerState + 1) % 2;
        }
        // intake was just toggled just now
        rollerPressedIn = true;

    } 
    // intake was not toggled just now
    else {
        rollerPressedIn = false;
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

// TODO: changed control for gourav
// TODO: toggle without roll out
void runRoller() {
    while (true) {
        // based on our roller state, we toggle it on or off
        switch (rollerState) {
            // intaking
            case 1:
                rollerClaw.move_velocity(200);
                break;
            // stop
            case 0: 
                rollerClaw.move_velocity(0);
                break;
        }

        pros::delay(10);
    }
}

// TODO: changed control for gourav
// TODO: claw open/close will stop roller
void runClaw() {
    while (true) {
        // based on our claw state, we toggle to open and close
        switch (clawState) {
            // open
            case 0:
                pistonClaw.set_value(false);
                rollerState = 0;
                break;
            // close
            case 1:
                pistonClaw.set_value(true);
                rollerState = 0;
                break;
        }

        pros::delay(10);
    }
}