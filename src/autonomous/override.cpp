#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void override() {
    // chassis.setPose(0, 0, 0);
    // chassis.distanceReset('R', 'F');
    
    leftMotors.move_voltage(-9000+3000);
    rightMotors.move_voltage(-9000-3000);
}