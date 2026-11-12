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

float closestGoalValue(const std::vector<float> &goaldistHeights, float distHeight) {
    // set closest value to the first value as a fallback
    float closest = goaldistHeights[0];

    // iterate through everything in goaldistHeights onwards
    for (int i = 1; i < goaldistHeights.size(); i++) {
        // if the distance from the current value of goaldistHeights is closer:
        if (std::abs(goaldistHeights[i] - distHeight) <= std::abs(closest - distHeight)) {
            // set the closest to the current value of goaldistHeights
            closest = goaldistHeights[i];
        }
    }

    return closest;
}

void updateMacroLift() {
    if (controller.get_digital(CONTROL5)) {
        if (!liftMacroPressed) {
            // if it is on turn it off
            if (liftMacroState == 1) {
                liftMacroState = 0;
            }

            // if the lift macro finishes and you press to activate score macro button monitoring
            else if (liftMacroState == 2) {
                liftMacroState = 3;
            }

            // if the button monitoring is running and you press to confirm score
            else if (liftMacroState == 3) {
                // this is score macro; it will switch to 0 after finished
                // no manual override for this though
            }

            // if it is off turn it on
            else {
                liftMacroState = 1;
            }
        }
        // lift macro was just toggled just now
        liftMacroPressed = true;

    } 
    // lift macro was not toggled just now
    else {
        liftMacroPressed = false;
    }
    pros::delay(10);
}

void macroLift() {
    while (true) {
        switch (liftMacroState) {
            // macro is off
            case 0: {
                break;
            }

            // macro is on
            case 1: {
                //Blue goal optical sensor value: 184
                //red goal optical sensor value: 00
                int currentHue = goalOptical.get_hue();
                std::vector<float> currentGoalHeights;

                if ((currentHue <= 184 + goalOpticRange && 184 - goalOpticRange <= currentHue) || // blue logic
                    (currentHue <= goalOpticRange)) {                                             // red logic
                    // if it is alliance goals set it to alliance heights
                    currentGoalHeights = allianceGoalHeights;
                } else {
                    // set to neutral goal heights
                    currentGoalHeights = neutralGoalHeights;
                }

                // while we still see pins in front of us keep moving up
                while (lemlib::mmToIn(distClaw.get_distance()) <= macroMaxDist) {
                    reversebar.move_voltage(12000);

                    // TODO REMOVE THIS TEST RUMBLE
                    controller.rumble(".");

                    // pros::delay(100);

                    if (liftMacroState == 0 || manualControl == true) {
                        // stop to terminate the macro
                        reversebar.move_voltage(0);
                        // TODO REMOVE THIS TEST RUMBLE
                        controller.rumble(" ");
                        // switch to manual control state
                        liftMacroState = 2;
                        // exit so that we're not locked
                        break;
                    }
                }
                // temp stop if we see nothing
                reversebar.move_voltage(0);

                // TODO REMOVE THIS TEST RUMBLE
                controller.rumble(" ");

                // set cascade height to current height from floor
                liftHeight = lemlib::mmToIn(distLiftHeight.get_distance());

                // run function to run lift to the closest goal value based on the set
                // currentGoalHeights based on the current liftheight plus 1 inch as
                // offset so we can actually drop it
                // TODO: UNCOMMENT THIS OUT AFTER TESTING
                // runLiftAuto(closestGoalValue(currentGoalHeights, liftHeight) + 1);

                // switch to the score macro
                liftMacroState = 2;
                // exit so that we're not locked
                break;
            }

            // macro is waiting to click to 3
            case 2: {
                pros::delay(10);
                break;
            }

            // score macro
            case 3: {
                // TODO: WRITE SCORE MACRO HERE
                // set cascade height to current height from floor
                liftHeight = lemlib::mmToIn(distLiftHeight.get_distance());

                // run function to run lift to the closest goal value based on the set
                // currentGoalHeights based on the current liftheight minus 3 inches as
                // offset so we can put it inside, then lift by 4 to go to liftheight
                // minus 1 and get out
                // TODO: UNCOMMENT THIS OUT AFTER TESTING
                // runLiftAuto(closestGoalValue(currentGoalHeights, liftHeight) - 3);
                
                // TODO: REMOVE THIS TEST MOTOR MOVEMENTS
                reversebar.move_voltage(1000);
                pros::delay(500);
                reversebar.move_voltage(0);
                // open/reverse claw
                clawState = 2;
                pros::delay(100);

                // TODO: REMOVE THIS TEST MOTOR MOVEMENTS
                reversebar.move_voltage(-1000);
                pros::delay(250);
                reversebar.move_voltage(0);
                // TODO: UNCOMMENT THIS OUT AFTER TESTING
                // runLiftAuto(closestGoalValue(currentGoalHeights, liftHeight) + 1);
                
                // set cascade height to current height from floor
                liftHeight = lemlib::mmToIn(distLiftHeight.get_distance());

                // run function to run lift to the closest goal value based on the set
                // currentGoalHeights based on the current liftheight minus 3 inches as
                // offset so we can put it inside, then lift by 4 to go to liftheight
                // minus 1 and get out
                // TODO: UNCOMMENT THIS OUT AFTER TESTING
                // runLiftAuto(0);

                // TODO: REMOVE THIS TEST MOTOR MOVEMENTS
                reversebar.move_voltage(12000);
                pros::delay(1000);
                reversebar.move_voltage(0);

                // switch to the score macro
                liftMacroState = 0;
                // exit so that we're not locked
                break;
            }
        }
        
        pros::delay(10);
    }
}

void runLiftAuto(float liftTarget) {
    // set a constant value for accepted error range, 0.25
    const float errorRange = 0.25;
    // TODO set a value for liftError of what we want error to be until reaching target
    const float setLiftError = 0;
    float error = 0;

    // while the error is greater than the acceptable error range
    while (true) {
        // set the lift height to the value we pull from the lift height dist sensor
        liftHeight = lemlib::mmToIn(distLiftHeight.get_distance());
        // set error to the difference between the target and the current height
        if ((liftTarget - liftHeight) < setLiftError) {
            float error = liftTarget - liftHeight;
        }
        else {
            float error = setLiftError;
        }

        if (std::abs(error) < errorRange) {
            // force stop the reverse bar's power because error will still produce a power
            // which may still be running, so we can stop the motor here
            reversebar.move_velocity(0);

            // exit function
            return;
        }

        // lift motion limits
        // if it is above max or below min and error is not stopping,
        // force stop the lift in order to prevent damaging the lift
        if (liftHeight >= maxLiftHeight && error > 0 ||
            liftHeight <= minLiftHeight && error < 0) {
            reversebar.move_velocity(0);

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
        reversebar.move_voltage(power / 127 * 12000);

        pros::delay(10);
    }
}