#include "main.h"
#include "drivecode/dr4b.hpp"
#include "drivecode/claw.hpp"

const float maxLiftHeight = 50;
const float minLiftHeight = 0;

float liftHeight;

int manualLiftState = 0;
bool manualControl = false;

void updateManualLift() {
    // if lift manual up pressed
    if (controller.get_digital(CONTROL3)) {
        manualLiftState = 1;
        manualControl = true;
        std::cout<<manualLiftState<<"\n";
    } 
    // if lift manual down pressed
    else if (controller.get_digital(CONTROL4)) {
        manualLiftState = 2;
        manualControl = true;
        std::cout<<manualLiftState<<"\n";
    } 
    // lift manual was not toggled
    else {
        manualLiftState = 0;
        manualControl = false;
        std::cout<<manualLiftState<<"\n";
    }

    pros::delay(10);
}

void runLift() {
    while (true) {
        // TODO: UNCOMMENT FOR LIFT LIMITS
        // // if liftheight is over the limits AND you want to manual control then do not allow the lift to move past bounds
        // if (liftHeight >= maxLiftHeight && manualLiftState == 1 || liftHeight <= minLiftHeight && manualLiftState == 2) {
        //     reversebar.move_voltage(0);
        // }

        // otherwise it's ok to go and lift up/down
        // else {
            switch (manualLiftState) {
                // manual lift off
                case 0: {
                    reversebar.move_voltage(0);
                    break;
                }

                // manual lift up
                case 1: {
                    reversebar.move_voltage(12000);
                    break;
                }

                // manual lift down
                case 2: {
                    reversebar.move_voltage(-12000);
                    break;
                }
            }
            
            pros::delay(10);
        }
    // }
}