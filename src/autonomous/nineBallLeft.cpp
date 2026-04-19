#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"

//hi this is aakanksh im doing it
void nineBallLeft() {
    
    //dist reset
    chassis.setPose(-1, -1, 0);
    chassis.distanceReset('L', 'B');

    //block grab 3
    intakeState = 3;
    wingState = 1;
    chassis.moveToPoint(-22.5, -26.5, 1000, {.minSpeed = 127, .earlyExitRange = 2}, true);
    chassis.waitUntil(17);
    scraperState = 1;
    chassis.waitUntilDone();

    //block grab 2
    scraperState = 0;
    chassis.turnToPoint(-48, -12, 1000, {.minSpeed = 60, .earlyExitRange = 4});
    chassis.moveToPoint(-48, -12, 1000, {}, true);
    chassis.waitUntil(10); //tune
    scraperState = 1;

    //go to long
    chassis.moveToPoint(1, 1, 1);


}   