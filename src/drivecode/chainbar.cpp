#include "drivecode/chainbar.hpp"

bool cbUpPressed = false;
bool cbDownPressed = false;

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
            chainBarState = std::max(chainBarState, 0);
        }
        cbDownPressed = true;
    } else cbDownPressed = false;
}

void runChainBar() {
    while(true) {
        switch(chainBarState) {
            case(0): targetPos = neutralPos;
            case(1): targetPos = loadPos;
            case(2): targetPos = upperScorePos;
            case(3): targetPos = lowerScorePos;
            break;
        }

        float pos = chainBarRotation.get_position();
        float error = targetPos - pos;
        float power = chainBarPID.update(error, true);

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