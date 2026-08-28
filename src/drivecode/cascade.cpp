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
int controlType = 0; // 0 means incrementing, 1 means not incrementing

// chain bar/cascade pid target variable
std::int32_t chainBarPID_target = 0;
std::int32_t cascadePID_target = 0;

float chainBarLoad = 0.00;
float chainBarScore = 0.00;
float cascadeIncrement = 1.00;

// rotation per inch (200rotations/inch)
float relativeRatio = 0;
// inches
const low_boost = 3.25;
const mid_boost = 5.77;
const high_boost = 8.77;

const score_boost = 3.25;

float pinDimension = 6.5
float stackDimension = 6.561;

int incrementWorks = 0; // variable we can get rid of after all testing is complete



// chainBarEasy is a function made just to simplify code
// so we can just call this instead of doing so multiple times, 
// especially in detailed commands such as pinFromWall.cpp

void chainBarEasy(float target) {
    target = target - chainBarRotation.get_position();
    // float upperBound, float lowerBound = target + 5.00, target - 5.00;

    // while (!(target <= upperBound || target >= lowerBound)) {
    while (!target == 0.00) {
        float error = target - chainBarRotation.get_position()
        
        float chainbarPIDOut = chainBarPID.update(error, true);
        chainBar.move_voltage(chainbarPIDOut);
    }
    chainBar.move_voltage(0);
}

// ------------------ Relative  ------------------
void moveRelative(int pins, int stacks, String level) {
    // calculate target height
    float goal_boost = 0;
    if (level == "low") {
        goal_boost = low_boost;
    } else if (level == "mid") {
        goal_boost = mid_boost;
    } else (level == "high") {
        goal_boost = high_boost;
    }

    float target_rot = (pins*pinDimension + stacks*stackDimension + goal_boost + score_boost) * relativeRatio;

    while (target_rot != cascadeRotation.get_position()) {
        // calculate PID output based on rotation input and move the motor to that
        float cascadePIDOut = cascadePID.update((target_rot) - cascadeRotation.get_position(), true);
        cascade.move_voltage(cascadePIDOut);
    }
    cascade.move_voltage(0);
}

// void moveAbsolute(float cups) {
//     // calculate target height
//     float goal_boost = 0;
//     if (level == "low") {
//         goal_boost = low_boost;
//     } else if (level == "mid") {
//         goal_boost = mid_boost;
//     } else (level == "high") {
//         goal_boost = high_boost;
//     }

//     float target_rot = (cups * relativeRatio);

//     while (target_rot != cascadeRotation.get_position()) {
//         // calculate PID output based on rotation input and move the motor to that
//         float cascadePIDOut = cascadePID.update((target_rot) - cascadeRotation.get_position(), true);
//         cascade.move_voltage(cascadePIDOut);
//     }
//     cascade.move_voltage(0);
// }
// ------------------ Relative + Absolute ------------------

void updateCascade() {
    // if cascade is not incrementing
    if (controlType == 1) {
        // cascade down
        if (controller.get_digital_new_press(cascadeDownControl)) {
            if (cascadeState != 2) {
                cascadeState = 2;
            }
            else {
                cascadeState = 0;
            }
        }

        // cascade up
        else if (controller.get_digital_new_press(cascadeUpControl)) {
            if (cascadeState != 1) {
                cascadeState = 1;
            }
            else {
                cascadeState = 0;
            }
        }
    }

    // with increment
    else if (controlType == 0) {
        // cascade up
        if (controller.get_digital_new_press(cascadeDownControl)) {
            if (cascadeState != 3) {
                cascadeState = 3;
            }
            else {
                cascadeState = 0;
            }
        }

        // cascade down
        else if (controller.get_digital_new_press(cascadeUpControl)) {
            if (cascadeState != 4) {
                cascadeState = 4;
            }
            else {
                cascadeState = 0;
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

            // cascade down without decrement
            case 1: {
                cascade.move_velocity(-600);
                chainBarPID_target = chainBarScore;
                break;
            }

            // cascade up without increment
            case 2: {
                cascade.move_velocity(600);
                chainBarPID_target = chainBarScore;
                break;
            }
            
            // cascade down with decrementing
            case 3: {
                cascadePID_target -= cascadeIncrement;
                incrementWorks = 1;
                pros::delay(100);
                incrementWorks = 0;
                cascadeState = 0;
                break;
            }

            // cascade up with incrementing
            case 4: {
                cascadePID_target += cascadeIncrement;
                incrementWorks = 1;
                pros::delay(100);
                incrementWorks = 0;
                cascadeState = 0;
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