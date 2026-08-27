#include "drivecode/cascade.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

// initialize state variables
bool cascadePressed = false;
int cascadeState = 0;

bool chainBarPressed = false;
int chainBarState = 0;

bool resetPressed = false;
int resetState = 0;

bool switchPressed = false;
// control type variable for cascade control switch
int controlType = 0;

// chain bar/cascade pid target variable
std::int32_t chainBarPID_target = 0;
std::int32_t cascadePID_target = 0;

float chainBarLoad = 0.00;
float chainBarScore = 0.00;
float cascadeIncrement = 0.00;

int incrementWorks = 0;

// chainBarEasy is a function made just to simplify code
// so we can just call this instead of doing so multiple times, 
// especially in detailed commands such as pinFromWall.cpp
void chainBarEasy(float target) {
    // calculate error and move voltage based on the error voltage
    float chainbarPIDOut = chainBarPID.update(target - chainBarRotation.get_position(), true);
    chainBar.move_voltage(chainbarPIDOut);
}

void updateCascade() {
    // if cascade control down is pressed
    if (controller.get_digital(cascadeDownControl)) {
        if (!cascadePressed) {
            // control type: pid increment
            if (controlType == 0) {
                cascadeState = 3;
                chainBarState = 2;
            } else {
            // control type: manual
                cascadeState = 2;
                chainBarState = 2;
            }
        }
        cascadePressed = true;
    }

    // if cascade control up is pressed
    else if (controller.get_digital(cascadeUpControl)) {
        if (controlType == 0) {
            // control type: pid increment
            if (!cascadePressed) {
                cascadeState = 1;
                chainBarState = 2;
            } else {
            // control type: manual
            cascadeState = 1;
            chainBarState = 2;
            }
        }
    }

    // no cascade buttons are pressed, 0 vel
    else {
        cascadeState = 0;
        cascadePressed = false;
    }
}

void updateCascadeFunctions() {
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
    
    // if switch button is pressed
    if (controller.get_digital(cascadeSwitchControl)) {
        if (!switchPressed) {
            controlType = (controlType + 1) % 2; //toggle logic between the two states
        }
        // switch was just toggled just now
        switchPressed = true;

    }
    // switch was not toggled just now
    else {
        switchPressed = false;
    }
}


void updateChainBar() {
    // if cascade reset position is pressed
    if (controller.get_digital(chainBarControl)) {
        if (!chainBarPressed) {
            chainBarState = (chainBarState + 1) % 2; //toggle logic between the two states
        }
        // switch was just toggled just now
        chainBarPressed = true;

    }
    // flip was not toggled just now
    else {
        chainBarPressed = false;
    }
}

void runCascade() {
    while (true) {
        // based on our cascade state, it goes up or down depending on the value of cascadeState
        switch (cascadeState) {
            // cascade stop
            case 0: {
            if (controlType == 1){
                    cascade.move_velocity(0);
                } else {
                    cascadePID_target = cascadePID_target;
                }
                break;
            }

            // cascade up
            case 1: {
                if (controlType == 1) {
                    cascade.move_velocity(600);
                } else {
                    cascadePID_target += cascadeIncrement;
                    cascadeState = 0;
                    incrementWorks = 1;
                }
                chainBarPID_target = chainBarScore;
                break;
            }

            // cascade down
            case 2: {
                cascade.move_velocity(-600);
                chainBarPID_target = chainBarScore;
                break;
            }
            
            // cascade down incrementing
            case 3: {
                cascadePID_target -= cascadeIncrement;
                incrementWorks = 1;
                pros::delay(100);
                incrementWorks = 0;
                break;
            }

        }

        switch (chainBarState) {
            // chain bar load state
            case 0: {
                chainBarPID_target = chainBarLoad;
                break;
            }
            // chain bar score state
            case 1: {
                chainBarPID_target = chainBarScore;
                break;
            }
        }

        // incremental
        if (controlType == 0) {
            // calculate error and move voltage based on the error voltage
            float cascadePIDOut = cascadePID.update(cascadePID_target - cascadeRotation.get_position(), true);
            cascade.move_voltage(cascadePIDOut);
        }

        // based on our cascade reset state, it will reset/not reset based on the state
        switch (resetState) {
            // cascade no reset
            case 0:
                break;
            // cascade reset
            case 1:
                cascade.move_absolute(0, 600);
                chainBarPID_target = chainBarLoad;
                resetState = 0;
                break;
        }
        
        chainBarEasy(chainBarPID_target);

        pros::delay (10);
    }
}