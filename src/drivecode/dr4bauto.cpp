#include "main.h"
#include "drivecode/dr4b.hpp"
#include "drivecode/claw.hpp"

// TODO: MODIFY THESE BASED ON ACTUAL ROBOT OR DISTANCE FROM CAD
const int macroMaxDist = 5;
const int goalOpticRange = 30;

// max/min lift heights and liftheight is in dr4b.cpp

// std::vector<float> allianceGoalHeights = {3.25,10,17,23,30,37.5,43.5,47};
// std::vector<float> neutralGoalHeights = {5.77,12.5,19,26,32.5,39.5,46,49.5};
// slight issue with the 49.5 is that we may not be allowed to go that far because we go up
// higher than 50in after 1 inch extra height

bool liftMacroPressed = false;
int liftMacroState = 0;
float liftTarget;
const float initialHeight = 0; //in inches TODO: UPDATE
const int interval = 10; //in inches

// float closestGoalValue(const std::vector<float> &goaldistHeights, float distHeight) {
//     // set closest value to the first value as a fallback
//     float closest = goaldistHeights[0];

//     // iterate through everything in goaldistHeights onwards
//     for (int i = 1; i < goaldistHeights.size(); i++) {
//         // if the distance from the current value of goaldistHeights is closer:
//         if (std::abs(goaldistHeights[i] - distHeight) <= std::abs(closest - distHeight)) {
//             // set the closest to the current value of goaldistHeights
//             closest = goaldistHeights[i];
//         }
//     }

//     return closest;
// }

float updateTarget(bool up) {
    if(up) {
        return (lemlib::mmToIn(distLiftHeight.get_distance())-initialHeight+interval)/interval;
    } else {
        return (lemlib::mmToIn(distLiftHeight.get_distance())-initialHeight)/interval;
    }
}

void updatePidLift() {
    //if you are holding it then accelerate to full speed once you let go snap to the next target
    if (controller.get_digital(CONTROL5)) {
        manualLiftState = 1;
        liftTarget = updateTarget(true);
        manualControl = false;
    } 
    // if lift manual down pressed
    else if (controller.get_digital(CONTROL6)) {
        manualLiftState = 2;
        liftTarget = updateTarget(false);
        manualControl = false;
    } 
    // lift manual was not toggled
    else {
        manualLiftState = 0;
        manualControl = false;
    }
}

void runPidLift() {
    // set a constant value for accepted error range, 0.25
    const float errorRange = 0.25;
    // TODO set a value for liftError of what we want error to be until reaching target
    const float setLiftError = 0;
    float error = 0;

    // while the error is greater than the acceptable error range
    while (!manualControl) { 
        // set the lift height to the value we pull from the lift height dist sensor
       float liftHeight = lemlib::mmToIn(distLiftHeight.get_distance());
        // set error to the difference between the target and the current height
        if ((liftTarget - liftHeight) < setLiftError) {
            error = liftTarget - liftHeight;
        }
        else {
            error = setLiftError;
        }

        if (std::abs(error) < errorRange) {
            // force stop the reverse bar's power because error will still produce a power
            // which may still be running, so we can stop the motor here
            lift.move_velocity(0);

            // exit function
            return;
        }

        // lift motion limits
        // if it is above max or below min and error is not stopping,
        // force stop the lift in order to prevent damaging the lift
        if (liftHeight >= maxLiftHeight && error > 0 ||
            liftHeight <= minLiftHeight && error < 0) {
            lift.move_velocity(0);

            // exit function
            return;
        }

        // feed in error to the pid to have a value
        float power = liftPID.update(error, true);

        // if power is over/under 127/-127 set to 127/-127 as a bound
        if (std::abs(power) > 127) {
            if (power < 0) {
                // set bounds to -127
                power = -127;
            }
            else {
                // set bounds to 127
                power = 127;
            }
        }

        // move lift based on a calculated power
        lift.move_voltage(power / 127 * 12000);

        pros::delay(10);
    }
}