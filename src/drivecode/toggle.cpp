#include "drivecode/toggle.hpp"
// #include "pros/misc.h"
#include "drivecode/objects.hpp"

// initialize state variables
int toggleState = 0;
bool togglePressed = false;

void updateToggle() {
    // if toggle control is pressed
    if (controller.get_digital(toggleControl)) {
        if (!togglePressed) {
            toggleState = (toggleState + 1) % 2;
        }
        // toggle was just toggled just now
        togglePressed = true;

    }
    // toggle was not toggled just now
    else {
        togglePressed = false;
    }
}

void runToggle() {
    while (true) {
        // based on our toggle state, we toggle to up and down
        switch (toggleState) {
            // up
            case 0:
                pistonToggle.set_value(false);
                break;
            // down
            case 1:
                pistonToggle.set_value(true);
                break;
        }

        pros::delay(10);
    }
}