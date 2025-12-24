#include "main.h"
#include "drivecode/intake.hpp"
#include "drivecode/objects.hpp"
#include "drivecode/pistons.hpp"


int intakeState = 0;
int velValue = 12000;

bool onePressed = false;
bool twoPressed = false;
bool threePressed = false;
bool fourPressed = false;

void runIntake() {
    while (true) {
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
                roller1.move_velocity(-velValue * 0.75);
                roller2.move_velocity(-velValue * 0.75);
                break;
            }

            case 3: { // intake 75%
                roller1.move_velocity(velValue * 0.75);
                roller2.move_velocity(velValue * 0.75);
                break;
            }


        };
    };
};

void updateIntake() {

    // L1 to intake -- intake speed 75% (intakeState == 3) if midTrapState == 1
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        if (!onePressed) {
            onePressed = true;
            if (midTrapState == 1) {
                intakeState = 3;
            } else {
                intakeState = 1;
            }
        }
    } else {
        onePressed = false;
        intakeState = 0;
    }


    // L2 Outtake
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        if (!twoPressed) {
            twoPressed = true;
            intakeState = 2;
        } else {
            twoPressed = false;
            intakeState = 0;
        }
    }
}