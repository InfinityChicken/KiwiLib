#include "velocity.hpp"

int velValue = 12000;
bool lowGoalVel = false;

void runVelocity() {
    while(true) {
        if(!lowGoalVel) {
            if(trapdoorState == 0) {
                velValue = 12000 * 0.75;
            } else if(trapdoorState == 1) {
                if(midGoalState == 1) {
                    velValue = 12000 * 0.6;
                } else {
                    velValue = 12000;
                }
            }
        } else if(lowGoalVel) {
            velValue = 0.4 * 12000;
        }
        pros::delay(10);
    }
}