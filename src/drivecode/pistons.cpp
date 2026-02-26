#include "main.h"
#include "drivecode/pistons.hpp"
#include "drivecode/intake.hpp"
#include "pros/misc.h"

int trapdoorState = 0; //0 closed
int midGoalState = 0; //0 closed
int scraperState = 0; //0 up
int wingState = 0; //0 down
int odomState = 0; //0 down
int midDescoreState = 0;

bool trapdoorPressed = false;
bool midGoalPressed = false;
bool scraperPressed = false;
bool wingPressed = false;
bool odomPressed = false;
bool midDescorePressed = false;

// bool trapOverride = false;

void updatePistons() {
    // //TODO: R2 wing hold
    // if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    //     wingState = 1;
    // } else {
    //     wingState = 0;
    // }

    // R2 wing toggle
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        if (!wingPressed) {
            if(wingState == 0) {
                wingState = 1;
            } else {
                wingState = 0;
            }
        }
        wingPressed = true;
    } else {
        wingPressed = false;
    }

    // mid goal descore toggle
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        if (!midDescorePressed) {
            if(midDescoreState == 0) {
                midDescoreState = 1;
            } else {
                midDescoreState = 0;
            }
        }
        midDescorePressed = true;
    } else {
        midDescorePressed = false;
    }

    // //TODO: R1 trapdoor hold
    // if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    //     trapdoorState = 1;
    // } else {
    //     trapdoorState = 0;
    // }

    // R1 trapdoor long toggle
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        if (!trapdoorPressed) {
            if(trapdoorState == 0) {
                trapdoorState = 1;
                //velValue = 12000;
            } else {
                trapdoorState = 0;
                //velValue = 12000 * 0.75;
            }
        }
        trapdoorPressed = true;
    } else {
        trapdoorPressed = false;
    }

    //right matchloader
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        if (!scraperPressed) {
            if (scraperState == 0) {
                scraperState = 1;
                trapdoorState =  0;
                midGoalState = 0;
            } else if (scraperState == 1) {
                scraperState = 0;
            }
        }
        scraperPressed = true;
    } else {
        scraperPressed = false;
    }

    //Y mid goal
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
        if (!midGoalPressed) {
            if (midGoalState == 0) {
                midGoalState = 1;
                //velValue = 12000 * 0.60;
            } else {
                midGoalState = 0;
            }
        }
        midGoalPressed = true;
    } else {
        midGoalPressed = false;
    }

    //up odom lift (get it because it like lifts up)
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
        if (!odomPressed) {
            if (odomState == 0) {
                odomState = 1;
            } else {
                odomState = 0;
            }
        }
        odomPressed = true;
    } else {
        odomPressed = false;
    }
}

void runPistons() {
    while (true) {
        // matchload
        if(scraperState == 0) {
            scraper.set_value(false);
        } else if (scraperState == 1) {
            scraper.set_value(true);
        }

        // wings
        if(wingState == 0) {
            wing.set_value(false);
        } else if (wingState == 1) {
            wing.set_value(true);
        }

        // mid goal descore
        if (midDescoreState == 0) {
            midGoalDescore.set_value(false);
        } else if (midDescoreState == 1) {
            midGoalDescore.set_value(true);
        }

        // long trapdoor
        // if(trapdoorState == 0) {
        //     trapdoor.set_value(false);
        // } else if (trapdoorState == 1) {
        //     trapdoor.set_value(true);
        // }

        // mid trapdoor
        if(midGoalState == 0) {
            midGoal.set_value(false);
        } else if (midGoalState == 1) {
            midGoal.set_value(true);
        }

        // odom lift
        if(odomState == 0) {
            odomLift.set_value(false);
        } else if (odomState == 1) {
            odomLift.set_value(true);
        }

        pros::delay(10);
    }
};