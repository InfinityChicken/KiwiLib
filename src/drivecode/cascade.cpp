#include "drivecode/cascade.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

// initialize state variables
bool cascadePressed = false;
int cascadeState = 0;

bool resetPressed = false;
int resetState = 0;

void updateCascade() {
    // if cascade control down is pressed
    if (controller.get_digital(cascadeDownControl)) {
        cascadeState = 2;
    }

    // if cascade control up is pressed and down is not
    else if (controller.get_digital(cascadeUpControl)) {
        cascadeState = 1;
    }

    // cascade was not toggled just now
    else {
        cascadeState = 0;
    }

    // if cascade reset position is pressed
    if (controller.get_digital(cascadeResetControl)) {
        if (!resetPressed) {
            resetState = (resetState + 1) % 2;
        }
        // flip was just toggled just now
        resetPressed = true;

    }
    // flip was not toggled just now
    else {
        resetPressed = false;
    }
}

void runCascade() {
    while (true) {
        // based on our cascade state, it goes up or down depending on the value of cascadeState
        switch (cascadeState) {
            // cascade stop
            case 0:
                cascade.move(0);
                break;
            // cascade up
            case 1:
                cascade.move(600);
                break;
            // cascade down
            case 2:
                cascade.move(-600);
                break;
        
        }

        // based on our cascade reset state, it will reset/not reset based on the state
        switch (resetState) {
            // cascade no reset
            case 0:
                break;
            // cascade reset
            case 1:
                cascade.move_absolute(0, 600);
                resetState = 0;
                break;
        }

        pros::delay(10);
    }
}