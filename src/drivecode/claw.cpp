#include "drivecode/claw.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

// initialize state variables
int rollerState = 0;
bool rollerPressed = false;

int flipState = 0;
bool flipPressed = false;

int clawState = 0;
bool clawPressed = false;

void updateRoller() {
    // if roller control intake is pressed
    if (controller.get_digital(rollerControlIn)) {
        if (!rollerPressed) {
            rollerState = 0;
        }
        // roller was just toggled just now
        rollerPressed = true;

    }

    // if roller control score is pressed
    if (controller.get_digital(rollerControlOut)) {
        if (!rollerPressed) {
            rollerState = 1;
        }
        // roller was just toggled just now
        rollerPressed = true;

    }

    // roller was not toggled just now
    else {
        rollerPressed = false;
    }
}

// DONE TODO: add update function for opening and closing claw piston

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

void updateFlip() {
    // if flip control is pressed
    if (controller.get_digital(clawFlipControl)) {
        if (!flipPressed) {
            flipState = (flipState + 1) % 2;
        }
        // flip was just toggled just now
        flipPressed = true;

    }
    // flip was not toggled just now
    else {
        flipPressed = false;
    }
}



// TODO: change to be always running, have 3 states for off, intaking, and outtaking
void runRoller() {
    while (true) {
        // based on our roller state, we toggle it on or off
      

        switch (rollerState) {
            // intaking
            case 0:
                rollerClaw.move_voltage(12000); // TODO: tune where open and closed state of rollerclaw is
                break;
            // outtaking
            case 1:
                rollerClaw.move_voltage(-12000);
                break;
        }

        pros::delay(10);
    }
}

// DONE TODO: add run function for opening and closing claw piston

void runClaw() {
    while (true) {
        // based on our claw state, we toggle to open and close
        switch (clawState) {
            // 0
            case 0:
                pistonClaw.set_value(false);
                break;
            // 180
            case 1:
                pistonClaw.set_value(true);
                break;
        }

        pros::delay(10);
    }
}

void runFlip() {
    while (true) {
        // based on our flip state, we toggle it 180 or 0
        switch (flipState) {
            // 0
            case 0:
                pistonFlip.set_value(false);
                break;
            // 180
            case 1:
                pistonFlip.set_value(true);
                break;
        }

        pros::delay(10);
    }
}
