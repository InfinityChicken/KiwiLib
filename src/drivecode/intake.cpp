#include "main.h"
#include "pros/misc.h"
#include "drivecode/intake.hpp"

// trapdoor closed 75 - open - 100, scoring midgoal - 75

int intakeState = 0;
//int tempVelValue = 12000 * 0.75;

bool intakePressed = false;
bool outtakePressed = false;
bool speedPressed = false;
bool testPressed = false;

void runIntake() {
    while (true) {
        //MUST CHANGE VELVALUE TO CHANGE SPEED
        switch(intakeState) {
            case 0: { // intake off
                topIntake.move_voltage(0);
                bottomIntake.move_voltage(0);
                break;
            }
            
            case 1: { // intake 100%
                topIntake.move_voltage(velValue);
                bottomIntake.move_voltage(velValue);
                break;
            }

            case 2: { // outtake
                topIntake.move_voltage(-velValue);
                bottomIntake.move_voltage(-velValue);
                break;
            }

            case 3: {
                bottomIntake.move_voltage(-12000); // hi aakanksh tune left motor speed here
                topIntake.move_voltage(12000);
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

            //moved vel change to pistons.cpp

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
        }
        outtakePressed = true;
    } else {
        outtakePressed = false;
    }


    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        if (!testPressed) {

            if(intakeState == 3) { //state changes
                intakeState = 0;
            } else {
                intakeState = 3;
            }

        }
        testPressed = true;
    } else {
        testPressed = false;
    }

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
        if (!speedPressed) {

            if(!lowGoalVel) { //state changes
                lowGoalVel = true;
            } else {
                lowGoalVel = false;
            }

        }
        speedPressed = true;
    } else {
        speedPressed = false;
    }
}