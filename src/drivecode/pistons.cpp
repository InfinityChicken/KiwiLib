#include "main.h"
#include "drivecode/objects.hpp"
#include "drivecode/pistons.hpp"

int longTrapState = 0;
int midTrapState = 0;
int willState = 0;
int wingState = 0;
int odomLiftState = 0;

bool longPressed = false;
bool midPressed = false;
bool willPressed = false;
bool wingPressed = false;
bool odomPressed = false;

void updatePistons() {

    // R1 -- toggle wing
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        if (!wingPressed) {
            wingPressed = true;
            if (wingState == 0) {
                wingState = 1;
            } else if (wingState == 1) {
                wingState = 0;
            }
        }
    } else {
        wingPressed = false;
    }

    // R2 -- long trapdoor
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        if (!longPressed) {
            longPressed = true;
            if (longTrapState == 0) {
                longTrapState = 1;
            } else if (longTrapState == 1) {
                longTrapState = 0;
            }
        }
    } else {
        longPressed = false;
    }
};


void runPistons() {
    while (true) {
       
        // matchload
        if(willState == 0) {
            will.set_value(0);
        } else if (willState == 1) {
            will.set_value(1);
        }

        // wings
        if(wingState == 0) {
            wing.set_value(0);
        } else if (wingState == 1) {
            wing.set_value(1);
        }

        // long trapdoor
        if(longTrapState == 0) {
            longTrap.set_value(0);
        } else if (longTrapState == 1) {
            longTrap.set_value(1);
        }

        // mid trapdoor
        if(midTrapState == 0) {
            midTrap.set_value(0);
        } else if (midTrapState == 1) {
            midTrap.set_value(1);
        }

        // odom lift
        if(odomLiftState == 0) {
            odomLift.set_value(0);
        } else if (odomLiftState == 1) {
            odomLift.set_value(1);

        }
    };
};