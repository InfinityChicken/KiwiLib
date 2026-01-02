#include "drivecode/sensors.hpp"

bool autoScore = true;

void updateSensors() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        autoScore = false;
    } 
}

void runAutoScore() {
    while(autoScore) {
        if(limitSwitch.get_value() == 0 && distFront.get()/25.4 < 36) { //if limit switch pressed and perimeter detected
            trapdoorState = 1; //open trapdoor
            intakeState = 1; //activate intake
        }
    }
}