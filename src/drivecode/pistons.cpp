#include "main.h"
#include "drivecode/pistons.hpp"

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
    //r1 wing
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
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

    //r2 trapdoor
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        if (!trapdoorPressed) {
            if(trapdoorState == 0) {
                trapdoorState = 1;
            } else {
                trapdoorState = 0;
            }
        }
        trapdoorPressed = true;
    } else {
        trapdoorPressed = false;
    }

    //down odom lift
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        if (!odomPressed) {
            if(odomState == 0) {
                odomState = 1;
            } else {
                odomState = 0;
            }
        }
        odomPressed = true;
    } else {
        odomPressed = false;
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

    //y mid goal
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
        if (!midGoalPressed) {
            if (midGoalState == 0) {
                midGoalState = 1;
            } else {
                midGoalState = 0;
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