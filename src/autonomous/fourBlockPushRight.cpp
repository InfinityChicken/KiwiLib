#include "autonomous/autonomous.hpp"

void fourBlockPushRight() {
    //dsr
    chassis.setPose(1, -1, 0);
    chassis.distanceReset('R', 'B');

    //block grab
    intakeState = 1;
    chassis.moveToPoint(28, -24, 1000, {}, true);
    chassis.waitUntilWithin(5, 24, 24);
    scraperState = 1;  
}