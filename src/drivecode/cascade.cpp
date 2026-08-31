#include "drivecode/cascade.hpp"
#include "drivecode/cascadeControl.hpp"
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
float cascadeHeight = 0;

int scoreHeights[6] = {};
int heightConstant = 0;
int currentLevel = 0;
int targetInches = 0;


// control type variable for cascade control switch
// 0: incrementing, 1: manual
int controlType = 0; 

// chain bar/cascade pid target variable
std::int32_t chainBarPID_target = 0;
std::int32_t cascadePID_target = 0;

float chainBarLoad = 0.00;
float chainBarScore = 0.00;
float cascadeIncrement = 1.00;

// rotation per inch (200rotations/inch)
float relativeRatio = 0;

// offset boosts for goals
const double low_boost = 3.25;
const double mid_boost = 5.77;
const double high_boost = 8.77;
const double score_boost = 3.25;

float pinDimension = 6.5;
float stackDimension = 6.561;

// oorja's variable we can get rid of after all testing is complete
int incrementWorks = 0; 

// chainBarEasy is a function made just to simplify code
// so we can just call this instead of doing so multiple times, 
// especially in detailed commands such as pinFromWall.cpp

void chainBarEasy(float target) {
    float error = 1.0;

    // calculate error and move voltage based on the error voltage
    float chainbarPIDOut = chainBarPID.update(target - chainBarRotation.get_position(), true);

    // reduce error as much as possible
    // continue unless it is within the max error and min error
    while (!(chainbarPIDOut <= target + error && chainbarPIDOut >= target - error) ) {
        chainbarPIDOut = chainBarPID.update(target - chainBarRotation.get_position(), true);
        chainBar.move_voltage(chainbarPIDOut);
    }
}

// running variable for cascade level 
// once height modulus is over the threhsold add one to that variable
// when it let go, set the pid height to the running variable plus one 
// have something that constantly updating the running variable to track what level it is at 
// const tracking separate task check if going up and down and modulus to set if its adding or subtracting 
// ds tracks height of floor convert these heights into the levels 
//constantly update the level youre at, to do this we can use modulus and once the mod of the set interval is = 0, track going up and down as well (use velocity of motor positive or negative)
//track when button is released, set target height for cascade height for the pid to that level plus one, then convert to the actual number youre supposed to be on ( step function! )


// tracking the get_distance 

// tracking current scoring level you're at 

// once get distance reaches a certain threshold that we agree upon later, we increment the scoring level and then snap to the next level (step function)
// these levels are going to be tracked independently of the level 
// every time we gp up a certain height moduloing that will incremenet the levle size 

void cascadeEasy() {
    while (controller.get_digital(cascadeUpControl)) {
        cascadeHeight = distCascadeEasy.get_distance()/25.4; // converting cascade height into inches from mm
        currentLevel = static_cast<int>((cascadeHeight) / heightConstant); // tracking the level of pin/cup height that we're at. using integer division to truncate our level down
    }
    targetInches = scoreHeights[currentLevel + 1]; //since we want to snap up, we want to increase the level by 1 to be able to snap to the next cup/pin target height, accessing the height from an array
    while (distCascadeEasy.get_distance()/25.4 < targetInches) { // whilst our cascade height is less than our target inches amount..
        //float cascadePIDOut = cascadePID.update(cascadePID_target - cascadeHeight); // pid update
         float cascadePIDOut = cascadePID.update(targetInches, cascadeHeight); 

        pros::delay (10);
    }
}

void updateCascade() {
    // manual
    if (controlType == 1) {
        updateCascadeManual();
    }

    // with increment
    else if (controlType == 0) {
        updateCascadeIncremental();
    }

    // no cascade buttons are pressed, so stop cascade
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
        // manual cascade control
        if (controlType == 0) {
            runCascadeManual();
        }
        // incremental cascade control
        if (controlType == 1) {
            runCascadeIncremental();
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

        chainBarEasy(chainBarPID_target);

        pros::delay (10);
    }
}