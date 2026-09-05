#include "drivecode/cascade.hpp"
#include "drivecode/objects.hpp"

// initialize state variables
bool cascadePressed = false;
int cascadeState = 0;

bool chainBarPressed = false;
int chainBarState = 0;

bool cbUpPressed = false;
bool cbDownPressed = false;

bool resetPressed = false;
int resetState = 0;

bool switchPressed = false;
float cascadeHeight = 0;

// control type variable for cascade control switch
// 0: incrementing, 1: manual
int controlType = 0; 

// chain bar/cascade pid target variable
std::int32_t chainBarPID_target = 0;
std::int32_t cascadePID_target = 0;

float chainBarLoad = 0.00;
float chainBarScore = 0.00;
float cascadeIncrement = 1.00;

//TODO: zcheng done
//chain bar update loop

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

void updateCascadeAuto() {}

void cascadeManual() {
    if (controller.get_digital(cascadeUpControl)) {
        cascadeFulls.move_velocity(600);
        cascadeHalf.move_velocity(200);
    } else if (controller.get_digital(cascadeDownControl)) {
        cascadeFulls.move_velocity(-600);
        cascadeHalf.move_velocity(-200);
    }
}

void runCascadeAuto() {
    
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

/* running variable for cascade level 
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
*/

/*
void cascadeEasy() {
    while (controller.get_digital(cascadeUpControl)) {
        cascadeHeight = distCascade.get_distance()/25.4; // converting cascade height into inches from mm
        currentLevel = static_cast<int>((cascadeHeight) / heightConstant); // tracking the level of pin/cup height that we're at. using integer division to truncate our level down
    }
    targetInches = scoreHeights[currentLevel + 1]; //since we want to snap up, we want to increase the level by 1 to be able to snap to the next cup/pin target height, accessing the height from an array
    while (distCascade.get_distance()/25.4 < targetInches) { // whilst our cascade height is less than our target inches amount..
        //float cascadePIDOut = cascadePID.update(cascadePID_target - cascadeHeight); // pid update
         float cascadePIDOut = cascadePID.update(targetInches, cascadeHeight); 

        pros::delay (10);
    }
} */