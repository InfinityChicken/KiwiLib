#include "drivecode/flip.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"
#include "drivecode/pistons.hpp"
#include <cstdint>

// flipstate for what color we're locating
// 0 yellow 1 red 2 blue
int flipState = 0;
bool flipManualOverride = false;
bool flipTogglePressed = false;

bool clawClosePressed = false;
int clawCloseState = 0;

char color = 'Y';
pros::vision_signature_s_t colorSig = yellowSig;
uint16_t detected = vision.get_by_size(0).signature;
char detectedStr = 'Y';

// clawrotatecontrol is a placholder for the color change
void updateFlip() {
    // color change
    if (controller.get_digital(colorSwitchControl)) {
        if (!flipTogglePressed) {
            flipState = (flipState + 1) % 3;
        }
        flipTogglePressed = true;
    } else {
        flipTogglePressed = false;
    }

    // claw close detection
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

void runFlip() {
    while (true) {
        uint16_t detected = vision.get_by_size(0).signature;
        if (detected == yellowSig.id) {
            detectedStr = 'Y';
        } else if (detected == blueSig.id) {
            detectedStr = 'B';
        } else if (detected == redSig.id) {
            detectedStr = 'R';
        } else {
            detectedStr = '?';
        }

        switch (flipState) {
            case 0:
                // yellow
                color = 'Y';
                colorSig = yellowSig;
                break;
            case 1:
                // red
                color = 'R';
                colorSig = redSig;
                break;
            case 2:
                // blue
                color = 'B';
                colorSig = blueSig;
                break;
        }

        controller.print(0, 0, "Color: %c | Seeing: %c     ", color, detectedStr);
        
        // TODO: check if the largest color 
        // TODO: for the next program2mer, please make the code such as
        // TODO: that the code will flip once (which should get it to that side)
        // TODO: and set manualoverride to true
        // if (detected != colorSig.id) {
        //     break;
        // }]
    }
}