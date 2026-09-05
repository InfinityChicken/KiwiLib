#include "drivecode/cascade.hpp"

//set controlType to 1 if you want to use pid
//cascade pid currently inaccessible in driver

//float cascadeTarget = heights[0]; //initializes at neutral

bool cbUpPressed = false;
bool cbDownPressed = false;
int controlType = 0; 

void cascadeManual() {
    if (controller.get_digital(cascadeUpControl)) {
        cascadeFulls.move_velocity(600);
        cascadeHalf.move_velocity(200);
    }
    
    else if (controller.get_digital(cascadeDownControl)) {
        cascadeFulls.move_velocity(-600);
        cascadeHalf.move_velocity(-200);
    }
}

void runCascadeAuto() {
    // adjust PID target positions based on chainbar states
    while(true) {
        if(controlType != 1) { //disabled
            pros::delay(10);
            continue;
        }

        float pos = lemlib::mmToIn(distCascade.get_distance());
        float error = cascadeTarget - pos;
        float power = cascadePID.update(error, true);

        if(std::abs(power) > 127) {
            if(power < 0) power = -127;
            else power = 127;
        }

        float blueRPM = power / 127 * 600;
        float greenRPM = power / 127 * 200;

        cascadeFulls.move_velocity(blueRPM);
        cascadeHalf.move_velocity(greenRPM);
        pros::delay(10);
    }
}