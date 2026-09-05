#include "drivecode/chainbar.hpp"

int chainBarState = 0;

bool cbUpPressed = false;
bool cbDownPressed = false;

void updateChainBar() {
    // if the chain bar up is pressed
    if (controller.get_digital(cbUpControl)) {
        if (!cbUpPressed) {
            // if not current pressed, ++ to chain bar state
            chainBarState += 1;
            // make sure chainBarstate is capped at 3
            chainBarState = std::min(chainBarState, 3);
        }
        cbUpPressed = true;
        // set toggle pressed to true so holding doesn't change states
    } else cbUpPressed = false;
    // if controller didn't pressed chainbar up, keep it false so code doesnt triggger
    
    if (controller.get_digital(cbDownControl)) {
        // if chain bar down is pressed
        if (!cbDownPressed) {
            // check if its already been pressed
            chainBarState -= 1;
            // cap chainbarstate to 0
            chainBarState = std::max(chainBarState, 0);
        }
        cbDownPressed = true;
        // if chain bar down as already been pressed, then set back to false
    } else cbDownPressed = false;
}

void runChainBar() {
    // adjust PID target positions based on chainbar states
    while(true) {
        switch(chainBarState) {
            case(0): targetPos = neutralPos;
            case(1): targetPos = loadPos;
            case(2): targetPos = upperScorePos;
            case(3): targetPos = lowerScorePos;
            break;
        }

        float pos = chainBarRotation.get_position();
        // get current chain bar rotation
        float error = targetPos - pos;
        // calculate your error
        float power = chainBarPID.update(error, true);
        // calculate the PIDOutput based on error

        if(std::abs(power) > 127) {
            // if the pid output is greater than motor threshold
            // calculate what direction the chainbar must move
            // then set it to max volts to motors
            if(power < 0) {
                power = -127;
            } else {
                power = 127;
            }
        }

        chainBar.move(power);
        // make it move to the PID output
        pros::delay(10);
    }
}