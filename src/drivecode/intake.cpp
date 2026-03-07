#include "main.h"
#include "pros/misc.h"
#include "drivecode/intake.hpp"

int intakeState = 0;

bool intakePressed = false;
bool outtakePressed = false;
bool speedPressed = false;
bool testPressed = false;
bool switchPressed = false;
bool scoringPressed = false;
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
                bottomIntake.move_voltage(12000);

                if(midGoalState == 1) {
                    topIntake.move_voltage(12000 * 0.60);
                } else {
                    topIntake.move_voltage(12000);
                }

                break;
            }

            case 2: { // outtake
                topIntake.move_voltage(-12000);
                bottomIntake.move_voltage(-12000);
                break;
            }

            case 3: {
                topIntake.move_voltage(0);
                bottomIntake.move_voltage(12000); // hi aakanksh tune left motor speed here
                break;
            }
        }

        pros::delay(10);
    }
}

void updateIntake() {
   
    //l1 intake storing
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        if (!intakePressed) {

            if(intakeState == 3) { //state changes
                intakeState = 0;
            } else {
                intakeState = 3;
            }
        }
        intakePressed = true;
    } else {
        intakePressed = false;
    }

    // r2 scoring
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        if (!scoringPressed){
            intakeState = 2;
            pros::delay(100);
        }
        intakeState = 1;
        scoringPressed = true;
    } else if (intakeState == 1) {
        intakeState = 0;
        scoringPressed = false;
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


    // if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
    //     if (!testPressed) {

    //         if(intakeState == 3) { //state changes
    //             intakeState = 0;
    //         } else {
    //             intakeState = 3;
    //         }

    //     }
    //     testPressed = true;
    // } else {
    //     testPressed = false;
    // }

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