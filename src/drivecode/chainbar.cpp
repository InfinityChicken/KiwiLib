#include "drivecode/chainbar.hpp"

void updateChainBar() {
    if (controller.get_digital(cbUpControl)) {
        if (!cbUpPressed) {
            chainBarState += 1;
            chainBarState = std::min(chainBarState, 3);
        }
        cbUpPressed = true;
    } else cbUpPressed = false;
    
    if (controller.get_digital(cbDownControl)) {
        if (!cbDownPressed) {
            chainBarState -= 1;
            chainBarState = std::min(chainBarState, 0);
        }
        cbDownPressed = true;
    } else cbDownPressed = false;
}

void runChainBar(float target) {
    while(true) {
        float pos = chainBarRotation.get_position();
        float power = chainBarPID.update(chainBarRotation.get_position(), true);

        if(std::abs(power) > 127) {
            if(power < 0) {
                power = -127;
            } else {
                power = 127;
            }
        }

        chainBar.move(power);

        pros::delay(10);
    }
}