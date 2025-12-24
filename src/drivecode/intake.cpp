#include "main.h"
#include "drivecode/intake.hpp"

int intakeState = 0;
int velValue = 12000;

bool intakePressed = false;
bool outtakePressed = false;

void runIntake() {
    while (true) {
        //MUST CHANGE VELVALUE TO CHANGE SPEED
        switch(intakeState) {
            case 0: { // intake off
                roller1.move_velocity(0);
                roller2.move_velocity(0);
                break;
            }
            
            case 1: { // intake 100%
                roller1.move_velocity(velValue);
                roller2.move_velocity(velValue);
                break;
            }

            case 2: { // outtake 75%
                roller1.move_velocity(-velValue);
                roller2.move_velocity(-velValue);
                break;
            }
        }

        pros::delay(10);
    }
}

void updateIntake() {
    //l1 intake
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        if (!intakePressed) {

            if(intakeState == 1) { //state changes
                intakeState = 0;
            } else {
                intakeState = 1;
            }

            if (midGoalState == 1) { //vel change
                velValue = 12000 * 0.75;
            } else {
                velValue = 12000;
            }

        }
        intakePressed = true;
    } else {
        intakePressed = false;
    }


    //l2 outtake
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        if (!outtakePressed) {

            if(intakeState == 2) { //state changes
                intakeState = 0;
            } else {
                intakeState = 2;
            }

            velValue = 12000 * 0.75;

        }
        outtakePressed = true;
    } else {
        outtakePressed = false;
    }
}