#include "drivecode/rollerClaw.hpp"
#include "drivecode/cascade.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

int rollerState = 0;

bool rollerPressed = false;
bool outtakePressed = false;

void updateRoller() {
    // if roller control is pressed
    if (controller.get_digital(rollerControl)) {
        if (!rollerPressed) {
            rollerState = (rollerState + 1) % 4;
        }
        // roller was just toggled just now
        rollerPressed = true;

    }
    // roller was not toggled just now
    else {
        rollerPressed = false;
    }
}

void runRoller() {
    while (true) {
        // based on our roller state, we toggle it on or off
        switch (rollerState) {
            // off
            case 0:
                break;
            // intaking
            case 1:
                rollerClaw.move_absolute(50, 600);
                break;
            // off
            case 2:
                break;
            // outtaking
            case 3:
                rollerClaw.move_absolute(-50, 600);
                break;
        }

        pros::delay(10);
    }
}