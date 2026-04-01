#include "main.h"
#include "pros/misc.h"
#include "drivecode/intake.hpp"

int intakeState = 0;

bool intakePressed = false;
bool outtakePressed = false;
//bool speedPressed = false;
//bool testPressed = false;
bool lowSpeedPressed = false;
bool midGoalPressed = false;
bool bottomPressed = false;
static int vel() {
    if (lowSpeedMode) {
        return 9000;
    } else {
        return 12000;
    }
}
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

            case BOTTOM_ONLY: {
                topIntake.move_voltage(0);
                midIntake.move_voltage(0);
                bottomIntake.move_voltage(-12000); 
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
    //y mid goal
   if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
        if (!midGoalPressed) {
            if (intakeState == 3) {
                intakeState = 0;
                controller.rumble("");
            } else {
                intakeState = 2;
                pros::delay(100);
                intakeState = 3;
                while(intakeState == 3){
                    controller.rumble("...");
                }
            }
        }
        midGoalPressed = true;
    } else {
        midGoalPressed = false;
    }
 

    //down
      if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        if (!bottomPressed){
            if (intakeState == BOTTOM_ONLY){
            intakeState = STOPPED;
        } else {
            intakeState = BOTTOM_ONLY;
            intakeLiftState = 0;
        }
        }
        bottomPressed = true;
    } else {
        bottomPressed = false;
    }

    
     if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        if (!lowSpeedPressed) {
            lowSpeedMode = !lowSpeedMode;
        }
        lowSpeedPressed = true;
    } else {
        lowSpeedPressed = false;
    }

}