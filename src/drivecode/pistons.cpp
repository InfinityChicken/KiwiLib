#include "drivecode/pistons.hpp"
#include "drivecode/intake.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

int trapdoorState = 0;   // 0 closed
int scraperState = 0;    // 0 up
int wingState = 0;       // 0 down
int intakeLiftState = 0; // 0 down
int midDescoreState = 0;

bool trapdoorPressed = false;
bool wingPressed = false;
bool intakeLiftPressed = false;
bool scraperPressed = false;
bool midDescorePressed = false;

void updatePistons() {
    // R1: wing toggle
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        if (!wingPressed) {
            if (wingState == 0) {
                wingState = 1;
            } else {
                wingState = 0;
            }
        }
        wingPressed = true;
    } else {
        wingPressed = false;
    }

    // R2: score on hold — open trapdoor while held, close on release
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        trapdoorState = 1;
        trapdoorPressed = true;
    } else {
        if (trapdoorPressed) {
            trapdoorState = 0;
        }
        trapdoorPressed = false;
    }

    // UP: odom lift toggle
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
        if (!intakeLiftPressed) {
            if (intakeLiftState == 0) {
                intakeLiftState = 1;
            } else {
                intakeLiftState = 0;
            }
        }
        intakeLiftPressed = true;
    } else {
        intakeLiftPressed = false;
    }

    // RIGHT: matchloader w/ trapdoor closed
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        if (!scraperPressed) {
            if (scraperState == 0) {
                scraperState = 1;
                trapdoorState = 1;
            } else {
                scraperState = 0;
            }
        scraperPressed = true;
        }
    } else {
        scraperPressed = false;
    }

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
        if (!midDescorePressed) {
            if (midDescoreState == 0) {
                midDescoreState = 1;
            } else {
                midDescoreState = 1;
            }
        midDescorePressed = true;
        }
    } else {
        midDescorePressed = false;
    }


}

void runPistons() {
    while (true) {
        // wings
        if (wingState == 0) {
            wing.set_value(false);
        } else if (wingState == 1) {
            wing.set_value(true);
        }

        // trapdoor (score)
        if (trapdoorState == 0) {
            trapdoor.set_value(false);
        } else if (trapdoorState == 1) {
            trapdoor.set_value(true);
        }

        // odom lift
        if (intakeLiftState == 0) {
            intakeLift.set_value(false);
        } else if (intakeLiftState == 1) {
            intakeLift.set_value(true);
        }

        // scraper
        if (scraperState == 0) {
            scraper.set_value(false);
        } else if (scraperState == 1) {
            scraper.set_value(true);
        }

        // mid descore
        if (midDescoreState == 0) {
            midDescore.set_value(false);
        } else if (midDescoreState == 1) {
            midDescore.set_value(true);
        }

    }
}
