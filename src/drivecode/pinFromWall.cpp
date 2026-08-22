#include "drivecode/pinfromwall.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

// initialize state variables
int pinWallState = 0;


void runpinFromWall() {
    while (true) {
        switch (pinWallState){
            case 0: {
                break;
            }
            case 1: {
                resetState = 1
                rollerClaw.move_voltage(9000);
                cascade.move(600);

                pros::delay(200);
            }
        }
    
        // calculate error and move voltage based on the error voltage
        float chainbarPIDOut = chainBarPID.update(chainBarPID_target - chainBarRotation.get_position(), true);
        chainBar.move_voltage(chainbarPIDOut);

        pros::delay(10);
    }
}