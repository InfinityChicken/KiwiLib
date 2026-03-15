#include "drivecode/sensors.hpp"

bool autoScore = true;
bool autoScoreActive = false;

void updateSensors() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        autoScore = false;
    } 
}

void runAutoScore() {
    while(autoScore) {
        //TODO: add function to choose dist sensor and add here
        if(limitSwitch.get_value() == 1 && distFrontRight.get()/25.4 < 36) { //if limit switch pressed and perimeter detected 
            if(!autoScoreActive) { //if autoscore hasn't been activated yet
                trapdoorState = 1; //open trapdoor
                intakeState = 1; //activate intake
                autoScoreActive = true; //mark autoscore as active
            }
        } else { //if limit switch not pressed or no perimeter detected
            if(autoScoreActive) { //if autoscore was active
                intakeState = 0; //stop intake
                autoScoreActive = false; //mark autoscore as inactive
            }
        }
    }
}