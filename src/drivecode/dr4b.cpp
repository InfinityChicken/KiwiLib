#include "main.h"
#include "drivecode/dr4b.hpp"
#include "drivecode/claw.hpp"
#include "pros/motors.h"
#include <cmath>

const float maxLiftHeight = 900;
const float minLiftHeight = 0;

float liftHeight;

int manualLiftState = 0;
bool manualControl = false;

// how do i solve this 

void updateManualLift() {
    // if lift manual up pressed
    if (controller.get_digital(liftUp)) {
        manualLiftState = 1;
        manualControl = true;
    } 
    // if lift manual down pressed
    else if (controller.get_digital(liftDown)) {
        manualLiftState = 3;
        manualControl = true;
    } 
    // lift manual was not toggled
    else {
        manualLiftState = 0;
        manualControl = false;
    }

    if (controller.get_digital(liftFullDown)) {
        manualControl = false;
        liftTarget = initialHeight;
    }

    pros::delay(10); 
}

bool reset = false;

//16 degrees to -722
void runLift() {
    while (true) {
        //TODO: UNCOMMENT FOR LIFT LIMITS
        // if liftheight is over the limits AND you want to manual control then do not allow the lift to move past bounds
        if (lift.get_position() >= maxLiftHeight && manualLiftState == 1 || lift.get_position() <= minLiftHeight && manualLiftState == 3) {
            manualLiftState = 0;
        }

        if(lift.get_position() < 100 && manualLiftState == 0 && !reset) {
            manualLiftState = 2;
            pros::delay(10);
            manualLiftState = 0;
            lift.tare_position_all();
            reset = true;
        }

        // otherwise it's ok to go and lift up/down
        // else {
            switch (manualLiftState) {
                // manual lift off
                case 0: {
                    lift.move_voltage(0);
                    break;
                }

                // manual lift up
                case 1: {
                    lift.move_voltage(12000);
                    reset = false;
                    break;
                }

                // manual lift down
                case 2: {
                    lift.move_voltage(-6000);
                    break;
                }

                // half speed
                case 3: {
                    lift.move_voltage(-10000);
                    reset = false;
                    break;
                }
            }
            
            pros::delay(10);
        }
    // }
}