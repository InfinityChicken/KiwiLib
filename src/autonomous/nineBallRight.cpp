#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"

//hi this is aakanksh im doing it
void nineBallRight() {
    
    //dist reset
    chassis.setPose(1, -1, 0);
    chassis.distanceReset('R', 'B');


}   