#include "main.h"
#include "drivecode/pistons.hpp"
#include "drivecode/intake.hpp"
#include "pros/misc.h"

int trapdoorState = 0; //0 closed
int scraperState = 0; //0 up
int wingState = 0; //0 down
int intakeLiftState = 0;
int midDescoreState = 0; //down

bool trapdoorPressed = false;
bool scraperPressed = false;
bool wingPressed = false;
bool midDescorePressed = false;
bool intakeLiftPressed;

void updatePistons() {
    // //TODO: R2 wing hold
    // if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    //     wingState = 1;
    // } else {
    //     wingState = 0;
    // }

    // R1 wing toggle
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

    // R2 trapdoor long toggle
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
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
            } else if (scraperState == 1) {
                scraperState = 0;
            }
        }
        scraperPressed = true;
    } else {
        scraperPressed = false;
    }

    //up first stage lift
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
        if (!intakeLiftPressed) {
            if (intakeLiftState == 0) {
                intakeLiftState = 1;
            } else if (intakeLiftState == 1) {
                intakeLiftState = 0;
            }
        }
        intakeLiftPressed = true;
    } else {
        intakeLiftPressed = false;
    }

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
        if (!midDescorePressed){
            if (midDescoreState == 0){
                midDescoreState = 1;
            }
            else if(midDescoreState = 1){
                midDescoreState = 0;
                
            }
        }
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
        if(intakeLiftState == 0) {
            intakeLift.set_value(false);
        } else if (intakeLiftState == 1) {
            intakeLift.set_value(true);
        }

        pros::delay(10);
    }
};