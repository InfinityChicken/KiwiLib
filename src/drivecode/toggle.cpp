#include "drivecode/toggle.hpp"
#include "drivecode/objects.hpp"
#include <iostream>

const int toggleOpticRange = 30;
int toggleState = 0;
int opticalTeamColor_upper= 0;
int opticalTeamColor_lower= 0;
// upper red: 0/lower red: 330
// upper blue: 170/lower blue: 230

void updateToggle() {
    // if toggle optical sensor sees a toggle
    if (toggleOptical.get_proximity() <= 100) {
        // if toggle optical color is within the appropriate range 
        // // TODO: NEEDS TO BE FIXED SO IT CHECKS IF IT'S OUR ALLIANCE COLOR
        // if (!(toggleOptical.get_hue() > opticalTeamColor + toggleOpticRange && toggleOptical.get_hue() < opticalTeamColor - toggleOpticRange)) {
        //     toggleState = 1;
        // }
        // else {
        //     toggleState = 0;
        // }
    }

    pros::delay(10);
}

void updateToggleTest() {
    if (controller.get_digital(CONTROL6)) {
        toggleState = 1;
    } 
    else if (controller.get_digital(CONTROL7)) {
        toggleState = 2;
    } 
    else {
        toggleState = 0;
    }

    pros::delay(10);
}

void runToggle() {
    while (true) {
        switch (toggleState) {
            // toggle off
            case 0: {
                toggleRoller.move_voltage(0);
                break;
            }

            // toggle rolling
            case 1: {
                toggleRoller.move_voltage(12000);
                break;
            }

            case 2: {
                toggleRoller.move_voltage(-12000);
                break;
            }
        }
        
        pros::delay(10);
    }
}