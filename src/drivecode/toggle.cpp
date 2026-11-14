#include "drivecode/toggle.hpp"
#include "drivecode/objects.hpp"
#include <iostream>

const int toggleOpticRange = 30;
int toggleState = 0;
int toggleSideState = 0;
int opticalTeamColor_upper= 0;
int opticalTeamColor_lower= 0;
char teamColor = 'R'; // default red

bool toggleSideMacro_oncePressed = false;
bool toggleSideMacro_twicePressed = false;
bool autoToggleActive = false;

// upper red: 0/lower red: 330
// upper blue: 170/lower blue: 230

void autoToggle() {
    while(autoToggleActive) {
        // if toggle optical sensor sees a toggle
        if (toggleOptical.get_proximity() <= 100) {
            if(teamColor == 'R') {
                if(toggleOptical.get_hue() > 330 && toggleOptical.get_hue() < 360 || toggleOptical.get_hue() > 0 && toggleOptical.get_hue() < 30)  {// red has weird logic because it has two sides
                    toggleState = 0;
                } else {
                    toggleState = 1;
                }
            } else if (teamColor == 'B') {
                if(toggleOptical.get_hue() > 170 && toggleOptical.get_hue() < 230) {
                    toggleState = 0;
                } else {
                    toggleState = 1;
                }
            }
        }
        else {
            toggleState = 0;
        }

        pros::delay(10);
    }
}

void updateToggleSideMacro() {
    if (controller.get_digital(toggleClockwise)) {
        if (!toggleSideMacro_oncePressed) {
            toggleSideState = 1;
        }
        toggleSideMacro_oncePressed = true;
    } 
    else {
        toggleSideMacro_oncePressed = false;
    }

    if (controller.get_digital(toggleCounterClockwise)) {
        if (!toggleSideMacro_twicePressed) {
            toggleSideState = 2;
        }
        toggleSideMacro_twicePressed = true;
    } 
    else {
        toggleSideMacro_twicePressed = false;
    }

    pros::delay(10);
}

void updateManualToggle() {
    if (controller.get_digital(toggleClockwise)) {
        toggleState = 1;
    } 
    else if (controller.get_digital(toggleCounterClockwise)) {
        toggleState = 2;
    } 
    else {
        toggleState = 0;
    }

    pros::delay(10);
}

void runToggle() {
    while (true) {
        switch (toggleSideState) {
            // toggle off
            case 0: {
                toggle.move_voltage(0);
                break;
            }

            // toggle rolling
            case 1: {
                toggle.move_voltage(12000);
                break;
            }

            case 2: {
                toggle.move_voltage(-12000);
                break;
            }
        }
        
        pros::delay(10);
    }
}

void runToggleSideMacro() {
    while (true) {
        switch (toggleSideState) {
            // toggle off
            case 0: {
                toggle.move_voltage(0);
                break;
            }

            // toggle rolling
            case 1: {
                toggle.move_relative(360, 12000);
                toggleSideState = 0;
                break;
            }

            case 2: {
                toggle.move_relative(-720, -12000);
                toggleSideState = 0;
                break;
            }
        }
        
        pros::delay(10);
    }
}
