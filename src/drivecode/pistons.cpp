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

    // down -- odom lift
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        if (!odomPressed) {
            odomPressed = true;
            if (odomLiftState == 0) {
                odomLiftState = 1;
            } else if (odomLiftState == 1) {
                odomLiftState = 0;
            }
        }
    } else {
        odomPressed = false;
    }

    // right -- will (matchloader)
    // idk if this still grants manual control -- when will goes down trapdoor closes
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        if (!willPressed) {
            willPressed = true;
            if (willState == 0) {
                willState = 1;
                longTrapState = 0;
                midTrapState = 0;
            } else if (willState == 1) {
                willState = 0;
            }
        }
    } else {
        willPressed = false;
    }

    // y -- mid trapdoor
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
        if (!midPressed) {
            midPressed = true;
            if (midTrapState == 0) {
                midTrapState = 1;
            } else if (midTrapState == 1) {
                midTrapState = 0;
            }
        }
    } else {
        midPressed = false;
    }

    // down -- odom lift
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        if (!odomPressed) {
            odomPressed = true;
            if (odomLiftState == 0) {
                odomLiftState = 1;
            } else if (odomLiftState == 1) {
                odomLiftState = 0;
            }
        }
    } else {
        odomPressed = false;
    }
    
};


void runPistons() {
    while (true) {
       
        // matchload
        if(willState == 0) {
            will.set_value(false);
        } else if (willState == 1) {
            will.set_value(true);
        }

        // wings
        if(wingState == 0) {
            wing.set_value(false);
        } else if (wingState == 1) {
            wing.set_value(true);
        }

        // long trapdoor
        if(longTrapState == 0) {
            longTrap.set_value(false);
        } else if (longTrapState == 1) {
            longTrap.set_value(true);
        }

        // mid trapdoor -- 0 is open, 1 is closed for this (rest vs active)
        if(midTrapState == 0) {
            midTrap.set_value(true);
        } else if (midTrapState == 1) {
            midTrap.set_value(false);
        }

        // odom lift
        if(odomLiftState == 0) {
            odomLift.set_value(false);
        } else if (odomLiftState == 1) {
            odomLift.set_value(true);

        }
    };
};