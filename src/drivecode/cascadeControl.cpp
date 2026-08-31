#include "drivecode/cascade.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

void updateCascadeManual() {
    // cascade up
    if (controller.get_digital_new_press(cascadeUpControl)) {
        if (cascadeState != 1) {
            // cascade up
            cascadeState = 1;
        }
        else {
            // cascade stop
            cascadeState = 0;
        }
    }

    // cascade down
    else if (controller.get_digital_new_press(cascadeDownControl)) {
        if (cascadeState != 2) {
            // cascade down
            cascadeState = 2;
        }
        else {
            // cascade stop
            cascadeState = 0;
        }
    }

}

void updateCascadeIncremental() {
    // cascade up
    if (controller.get_digital_new_press(cascadeDownControl)) {
        if (cascadeState != 3) {
            cascadeState = 3;
        }
        else {
            cascadeState = 0;
        }
    }

    // cascade down
    else if (controller.get_digital_new_press(cascadeUpControl)) {
        if (cascadeState != 4) {
            cascadeState = 4;
        }
        else {
            cascadeState = 0;
        }
    }
}

void runCascadeManual() {
    switch (cascadeState) {
        // manual cascade stop
        case 0: {
            cascade.move_velocity(0);
        }
        
        // manual cascade up
        case 1: {
            cascade.move_velocity(600);
            chainBarPID_target = chainBarScore;
            break;
        }

        // manual cascade down
        case 2: {
            cascade.move_velocity(-600);
            chainBarPID_target = chainBarScore;
            break;
        }
    }
}

void runCascadeIncremental() {
    switch (cascadeState) {
        // incremental cascade stop
        case 0: {
            cascadePID_target = cascadePID_target;
        }

        // incremental cascade up
        case 1: {
            cascadePID_target += cascadeIncrement;
            incrementWorks = 1;
            pros::delay(100);
            incrementWorks = 0;
            cascadeState = 0;
            break;
        }

        // incremental cascade down
        case 2: {
            cascadePID_target -= cascadeIncrement;
            incrementWorks = 1;
            pros::delay(100);
            incrementWorks = 0;
            cascadeState = 0;
            break;
        }
    }
    
    // calculate error and move voltage based on the error voltage
    float cascadePIDOut = cascadePID.update(cascadePID_target - cascade.get_position(), true);
    cascade.move_voltage(cascadePIDOut);
}