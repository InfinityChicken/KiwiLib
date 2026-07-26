#include "drivecode/cascade.hpp"
#include "drivecode/pistons.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

// cascade state variable
// cascadeState = 0: sensing is OFF
// cascadeState = 1: sensing is ON
int cascadeState = 0;
int macroUpState = 0;
int macroDownState = 0;

// boolean to track if cascade was just pressed now
// since we haven't pressed it earlier, it's off at the start

bool topStack = false;
bool cascadePressed = false;
bool macroUpPressed = false;
bool macroDownPressed = false;

// boolean to track if the manual override is overriding
// get it? override?
bool manualOverride = false;

// boolean to track if macro is running
bool macroIsOn = false;

// chain bar stall variables
int currentDraw = 0;
double currentVelocity = 0.0;

// cascade pid target variables
std::int32_t target = 0;

void updateCascade() {
    // if my certain button is pressed
    if (controller.get_digital(cascadeControl)) {
        if (!cascadePressed) {
            // if at zero, change to one, if at one, change to zero
            // the two is the total number of states, the +1 refers to
            // the state coming up, so 2 would be 0 because that's the next state 
            cascadeState = (cascadeState + 1) % 2;
            if (cascadeState == 1 && manualOverride == true) {
                manualOverride = false;
                macroIsOn = (distCascade.get() <= 254 && distCascade.get() >= 1);
            }
        }
        
        // cascade button just pressed
        cascadePressed = true;
    } else {
        // cascade button not just pressed
        cascadePressed = false;
    }

    // if intake control is pressed and macro is on
    if (controller.get_digital(intakeControl) && cascadeState == 1) {
        if (!macroUpPressed) {
            // set macro to go up, and will later turn 0 after it goes up
            macroUpState = 1;
        }
        // macro up was just toggled just now
        macroUpPressed = true;

    } 
    // macro up was not toggled just now
    else {
        macroUpPressed = false;
    }

    // if intake control is pressed and macro is on
    if (controller.get_digital(outtakeControl) && cascadeState == 1) {
        if (!macroDownPressed) {
            // set macro to go down, and will later turn 0 after it goes down
            macroDownState = 1;
        }
        // macro up was just toggled just now
        macroDownPressed = true;

    } 
    // macro up was not toggled just now
    else {
        macroDownPressed = false;
    }
}


// macro cascade program
void runCascade() {
    while (true) {
        if (manualOverride == false) {
            // cascade dist sensor sensing is OFF
            if (cascadeState == 0) {
                // don't move if it's off
                macroIsOn = false;
                cascadeL.move_velocity(0);
                cascadeR.move_velocity(0);
            }
            else if (cascadeState == 1) {
                macroIsOn = (distCascade.get() <= 254 && distCascade.get() >= 1);

                // if the cascade distance sensor is within 1-254mm, and it is not overriden by manuals
                if (macroIsOn) { // less than 10 in away
                    // move if it is in the range
                    cascadeL.move_velocity(200);
                    cascadeR.move_velocity(200);
                }
                // if not in the range, it will cease to move until furthe sensor results
                if (!macroIsOn) {
                    cascadeL.move_velocity(0);
                    cascadeR.move_velocity(0);
                }
            }
        }

        // based on macro up or down it will change the cascade's pid amount and reset the state
        if (macroDownState) target -= 5; macroDownState = 0;
        if (macroUpState) target += 5; macroUpState = 0;
        

        float targetOut = cascadePID.update(target - cascadeRotation.get_position(), 0.01f);
        cascadeL.move_voltage(targetOut);
        cascadeR.move_voltage(targetOut);

        pros::delay(10);
    }
}

void () {
    // if manual control for cascade up pressed
    if (controller.get_digital(manualCascadeControlUp)) {
        // cascade move up
        cascadeL.move_voltage(200);
        cascadeR.move_voltage(200);
        manualOverride = true;
        cascadeState = 0;
        macroIsOn = false;
    }

    // if manual control for cascade down pressed
    else if (controller.get_digital(manualCascadeControlDown)) {
        // cascade move down
        cascadeL.move_voltage(-12000);
        cascadeR.move_voltage(-12000);
        manualOverride = true;
        cascadeState = 0;
        macroIsOn = false;
    }

    // if no manual controls for cascade pressed
    else if (manualOverride){
        // stop providing power to cascade
        cascadeL.move_velocity(0);
        cascadeR.move_velocity(0);
    }

    // if manual control for chain bar up pressed
    if (controller.get_digital(manualChainBarControlUp)) {
        // chain bar rotate forwards
        chainBar.move_velocity(200);
        manualOverride = true;
        cascadeState = 0;
        macroIsOn = false;
    }

    // if manual control for chain bar down pressed
    else if (controller.get_digital(manualChainBarControlDown)) {
        // chain bar rotate backwards
        chainBar.move_velocity(-200);
        manualOverride = true;
        cascadeState = 0;
        macroIsOn = false;
    }

    // if no manual controls for chain bar pressed
    else if (manualOverride){
        // stop providing power to cascade
        chainBar.move_velocity(0);
    }
}

// void macroScore() {
//     while (true) {
//         if (!macroIsOn && cascadeState == 1 && manualOverride == false) {
//             // if the cascade is at the top of the stack (turns macroIsOn to false), 
//             // cascadeState still equals 1 (you were just previosly running the macro), 
//             // and manualOverride is false (you are not manually controlling the cascade), 
//             // then you can run the macro to score
            
//             // stop cascade
//             cascadeL.move_velocity(0);
//             cascadeR.move_velocity(0);
            
//             // chain bar score
//             chainBar.move_absolute(300, 200);

//             // run piston macro here some how?
//             uint16_t sig = vision.get_by_size(0).signature;

//             if (sig == yellowSig.id) {
//                 detectedColor = 'Y';
//             } else if (sig == redSig.id)  {
//                 detectedColor = 'R';
//             } else if (sig == blueSig.id) { 
//                 detectedColor = 'B';
//             } else {
//                 detectedColor = '?';
//             }

//             switch (flipState) {
//                 case 0: targetColor = 'Y'; break;
//                 case 1: targetColor = 'R'; break;
//                 case 2: targetColor = 'B'; break;
//             }

//             // flip only if the color is not the right one
//             if (!flipManualOverride && detectedColor != '?') {
//                 if (detectedColor != targetColor) {
//                     clawRotateState = (clawRotateState + 1) % 2;
//                 }
//             }

//             chainBar.move_absolute(0, 200);
//         }
//     }
// }