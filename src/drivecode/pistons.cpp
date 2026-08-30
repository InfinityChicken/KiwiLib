#include "drivecode/pistons.hpp"
#include "drivecode/objects.hpp"
#include "pros/misc.h"

int flipState = 0;
bool flipManualOverride = false;
bool flipTogglePressed = false;

char targetColor = 'Y';
char detectedColor = '?';

int clawRotateState = 0;
int clawCloseState = 0;
bool clawRotatePressed = false;
bool clawClosePressed = false;

void updateFlip() {
    // when color switch button is clicked, it will change the flip color to detect
    if (controller.get_digital(colorSwitchControl)) {
        if (!flipTogglePressed) {
            // modulo fun
            flipState = (flipState + 1) % 3;

            flipManualOverride = false;
        }

        flipTogglePressed = true;
    
    } else {
        flipTogglePressed = false;
    }

    // give manual control after the macro
    if (flipManualOverride) {
        if (controller.get_digital(clawRotateControl)) {
            if (!clawRotatePressed) {
                clawRotateState = (clawRotateState + 1) % 2;
            }
            clawRotatePressed = true;
        } else {
            clawRotatePressed = false;
        }
    }
}

void runFlip() {
    while (true) {
        uint16_t sig = vision.get_by_size(0).signature;

        if (sig == yellowSig.id) {
            detectedColor = 'Y';
        } else if (sig == redSig.id)  {
            detectedColor = 'R';
        } else if (sig == blueSig.id) { 
            detectedColor = 'B';
        } else {
            detectedColor = '?';
        }

        switch (flipState) {
            case 0: targetColor = 'Y'; break;
            case 1: targetColor = 'R'; break;
            case 2: targetColor = 'B'; break;
        }

        // flip only if the color is not the right one
        if (!flipManualOverride && detectedColor != '?') {

            if (detectedColor != targetColor) {
                clawRotateState = (clawRotateState + 1) % 2;
            }

            // turn manual on, macro goes off
            flipManualOverride = true;
        }

        pros::delay(10);
    }
}

void updatePistons() {
    // previously, claw rotate was here but got moved to flip

    // claw close
    if (controller.get_digital(clawCloseControl)) {
        if (!clawClosePressed) {
            if (clawCloseState == 0) {
                clawCloseState = 1;
            } else {
                clawCloseState = 0;
            }
        }
        clawClosePressed = true;
    } else {
        clawClosePressed = false;
    }
}

void runPistons() {
    while (true) {
        // claw close
        if (clawCloseState == 0) {
            pistonClawClose.set_value(false);
        } else if (clawCloseState == 1) {
            pistonClawClose.set_value(true);
        } 

        // claw rotate
        pistonClawRotate.set_value(clawRotateState);
        pistonClawClose.set_value(clawCloseState);

        pros::delay(10);
    }
}