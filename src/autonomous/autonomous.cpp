#include "autonomous/autonomous.hpp"

void sevenBlockLow() {
    chassis.setPose(-1,-1,0);
    chassis.distanceReset('B','R'); //dist reset to begin
    
}

void SAWP() {
    chassis.setPose(-1,-1,90);
    chassis.distanceReset('F','R');
}