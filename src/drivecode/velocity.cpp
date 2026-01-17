#include "velocity.hpp"

int velValue = 12000;
bool lowGoalVel = false;
int midGoalSpeed = 12000 * 0.6;

void runVelocity() {
    while(true) {
        if(!lowGoalVel) {
            if(trapdoorState == 0) {
                velValue = 12000 * 0.8;
            } else if(trapdoorState == 1) {
                if(midGoalState == 1) {
                    velValue = midGoalSpeed;
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