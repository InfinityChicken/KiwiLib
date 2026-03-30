#include "main.h"
#include "pros/misc.h"
#include "drivecode/intake.hpp"

int intakeState = 0;

bool intakePressed = false;
bool outtakePressed = false;
//bool speedPressed = false;
//bool testPressed = false;
//bool switchPressed = false;
bool midGoalPressed = false;

void runIntake() {
    while (true) {
        //MUST CHANGE VELVALUE TO CHANGE SPEED
        switch(intakeState) {
            case STOPPED: { // intake off
                topIntake.move_voltage(0);
                midIntake.move_voltage(0);
                bottomIntake.move_voltage(0);
                break;
            }
            
            case LONG_GOAL: { // intake 100%
                topIntake.move_voltage(12000);
                midIntake.move_voltage(12000);
                bottomIntake.move_voltage(12000);
                break;
            }

            case OUTTAKE: { // outtake
                topIntake.move_voltage(-12000);
                midIntake.move_voltage(-12000);
                bottomIntake.move_voltage(-12000);
                break;
            }

            case MID_GOAL: { //mid goal
                topIntake.move_voltage(-12000);
                midIntake.move_voltage(12000);
                bottomIntake.move_voltage(12000); 
                break;
            }
        }

        pros::delay(10);
    }
}

void updateIntake() {
   
    //l1 long goal scoring
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        if (!intakePressed) {

            if(intakeState == 1) { //state changes
                intakeState = 0;
            } else {
                intakeState = 1;
            }
        }
        intakePressed = true;
    } else {
        intakePressed = false;
    }

    // y mid goal
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
        if (!midGoalPressed) {

            if(intakeState == 3) { //state changes
                intakeState = 0;
            } else {
                intakeState = 2;
                pros::delay(100);
                intakeState = 3;
            }
        }
        midGoalPressed = true;
    } else {
        midGoalPressed = false;
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

    // if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
    //     if (!speedPressed) {

    //         if(!lowGoalVel) { //state changes
    //             lowGoalVel = true;
    //         } else {
    //             lowGoalVel = false;
    //         }

    //     }
    //     speedPressed = true;
    // } else {
    //     speedPressed = false;
    // }

}