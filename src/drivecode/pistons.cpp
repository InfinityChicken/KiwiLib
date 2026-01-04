#include "main.h"
#include "drivecode/pistons.hpp"
#include "drivecode/intake.hpp"
#include "pros/misc.h"

int trapdoorState = 0; //0 closed
int midGoalState = 0; //0 closed
int scraperState = 0; //0 up
int wingState = 0; //0 down
int odomState = 0; //0 down

bool trapdoorPressed = false;
bool midGoalPressed = false;
bool scraperPressed = false;
bool wingPressed = false;
bool odomPressed = false;

void updatePistons() {
    //R2 wing
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) { // going back to toggle 
        if (!wingPressed) {
            if(wingState == 0) {
                wingState = 1;
            } else {
                wingState = 0;
            }
        }
        wingState = true;
    } else {
        wingState = false;
    }

    //R1 trapdoor long 
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        if (!trapdoorPressed) {
            if(trapdoorState == 0) {
                trapdoorState = 1;
                velValue = 12000;
            } else {
                trapdoorState = 0;
                velValue = 12000 * 0.75;
            }
        }
        trapdoorPressed = true;
    } else {
        trapdoorPressed = false;
    }

    //down odom lift
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) { //only goes once for driver
        odomState = 1;
    } 

    //right matchloader
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        if (!scraperPressed) {
            if (scraperState == 0) {
                scraperState = 1;
                trapdoorState = 0;
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
                trapdoorState = 1;
                velValue = 12000 * 0.75;
            } else {
                midGoalState = 0;
                trapdoorState = 0;
            }
        }
        midGoalPressed = true;
    } else {
        midGoalPressed = false;
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

        // long trapdoor
        if(trapdoorState == 0) {
            trapdoor.set_value(false);
        } else if (trapdoorState == 1) {
            trapdoor.set_value(true);
        }

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