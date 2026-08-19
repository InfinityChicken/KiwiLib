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

void updateCascade() {
    // if cascade control down is pressed
    if (controller.get_digital(cascadeDownControl)) {
        cascadeState = 2;
        chainBarState = 2;
    }

    // if cascade control up is pressed and down is not
    else if (controller.get_digital(cascadeUpControl)) {
        cascadeState = 1;
        chainBarState = 2;
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

    // if switch button is pressed
    if (controller.get_digital(cascadeSwitchControl)) {
        if (!switchPressed) {
            controlType = (controlType + 1) % 2;
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
            chainBarState = (chainBarState + 1) % 2;
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
                if (controlType == 1) {cascade.move(0);}
                else {cascadePID_target = cascadePID_target;}
                chainBarPID_target = 0.00;
                break;
            }

            // cascade up
            case 1: {
                if (controlType == 1) {cascade.move(600);}
                else {cascadePID_target += 0.00;}
                chainBarPID_target = 0.00;
                break;
            }

            // cascade down
            case 2: {
                if (controlType == 1) {cascade.move(-600);}
                else {cascadePID_target -= 0.00;}
                chainBarPID_target = 0.00;
                break;
            }

        }
    }

    switch (chainBarState) {
        case 0: {
            chainBarPID_target = 0.00;
            break;
        }
        case 1: {
            chainBarPID_target = 0.00;
            break;
        }
    }
    
    // calculate error and move voltage based on the error voltage
    float chainbarPIDOut = chainBarPID.update(chainBarPID_target - chainBarRotation.get_position(), true);
    chainBar.move_voltage(chainbarPIDOut);

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
            resetState = 0;
            break;
    }

    pros::delay(10);
}