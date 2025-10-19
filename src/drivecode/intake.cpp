#include "drivecode/intake.hpp"
#include "drivecode/pistons.hpp"
#include "drivecode/sensors.hpp"
#include "autonomous/autonSelector.hpp"

int intakeState = 0;

int velValue = 12000;
bool velButtonPressed = false;

bool onePressed = false;
bool twoPressed = false;
bool threePressed = false;
bool fourPressed = false;
bool distPressed = false;

int velState = 0;

void runIntake() {
    while(true) {
        switch(intakeState) {
            case 0: { //stop intake
                bottomRoller.move_voltage(0);
                topRoller.move_voltage(0);
                break;
            }

            case 1: { //run intake
                bottomRoller.move_voltage(velValue);
                topRoller.move_voltage(velValue);
                break; 
            }

            case 2: { //outtake
                bottomRoller.move_voltage(-velValue);
                topRoller.move_voltage(-velValue);
                break;
            }

            case 3: { //intake only bottom
                bottomRoller.move_voltage(velValue);
                topRoller.move_voltage(0);
                break;
            }
             case 4: { //intake only top
                bottomRoller.move_voltage(0);
                topRoller.move_voltage(velValue);
                break;
            }
            case 5: { //outtake only top
                bottomRoller.move_voltage(0);
                topRoller.move_voltage(-velValue);
            }
        }

        pros::delay(10);
        
    }
}

void updateIntake() {
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) { //left, macro 
        hoodState = 1;
        littleWillState = 0;
    }

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) { //a, stop all intake, state 0
        intakeState = 0;
    }

    // if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) { //l1, long goal (indexer outtake), state 1
    //     if(!distPressed) {
    //         distPressed = true;

    //         if (distActive) {
    //             distActive = false;
    //             topFilled = false;
    //         } else {
    //             distActive = true;
    //         }
            
    //     } 
    // } else {
    //     distPressed = false;
    // }

    
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) { //l1, long goal (indexer outtake), state 1
        if(!onePressed) {
            onePressed = true;

            if (intakeState == 1) {
                intakeState = 0;
            } else {
                velValue = 12000;
                intakeState = 1;
            }

            
        } 
    } else {
        onePressed = false;
    }
    
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { //l2, mid goal (indexer outtake), state 2
        if(!twoPressed) {
            twoPressed = true;
            if (intakeState == 2) {
                intakeState = 0;
            } else {
                velValue = 12000;
                intakeState = 2;
            }
        }
    } else {
        twoPressed = false;
    }
    
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) { //r1, low goal (standard), state 3
        if(!threePressed) {
            threePressed = true;
            if (intakeState == 3) {
                intakeState = 0;
            } else {
                velValue = 12000 * 0.85;
                intakeState = 3;
            }
        }
    } else {
        threePressed = false;
    }

    // if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) { //r2, load intake, state 4
    //     if(!fourPressed) {
    //         fourPressed = true;
    //         if (intakeState == 4) {
    //             intakeState = 0;
    //         } else {
    //             intakeState = 4;
    //         }
    //     }
    // } else {
    //     fourPressed = false;
    // }
        

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) { //toggle voltage
        if(!velButtonPressed) {
            velButtonPressed = true;
            if(velState == 0) {
                velValue = 12000 * 0.85;
                velState = 1;
            } else if(velState == 1) {
                velValue = 12000;
                velState = 0;
            }
        }
    } else {
        velButtonPressed = false;
    }
}