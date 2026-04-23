#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"

//hi this is aakanksh im doing it
void counterSAWP() {
    
    //dist reset
    chassis.setPose(1, -1, 90);
    chassis.distanceReset('F', 'R');

    //move to and do ml
    wingState = 1;
    scraperState = 1;
    //chassis.moveToPoint(40, chassis.getPose().y, 1000, {.minSpeed = 127, .earlyExitRange = 10});
    chassis.moveToPoint(45.5, chassis.getPose().y, 1000, {.maxSpeed = 60});
    chassis.turnToHeading(180, 1000);
    intakeState = 1;
    chassis.moveDistance(6, 1000, {.minSpeed = 127 * 0.5}); //prev 9
    chassis.sendVoltage(6000, 600);
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('L', 'F');

    //score long
    chassis.moveToPoint(47.5, -25, 1000, {.forwards = false, .minSpeed = 90}); //prev minspeed 100
    intakeState = 3;
    trapdoorState = 1;
    chassis.sendVoltage(-12000 * 0.4, 900); //prev voltage 50%, prev time 850, 700
    chassis.setPose(1, -1, chassis.getPose().theta);
    chassis.distanceReset('L', 'F');
    
    //swing
    trapdoorState = 0;
    scraperState = 0;
    chassis.turnToHeading(-85, 750);
    chassis.distanceReset('B', 'L');
    intakeState = 1; //TODO; change back to state=1
    chassis.moveToPoint(24, -24, 1000, {.minSpeed = 60, .earlyExitRange = 2}, true);
    chassis.waitUntil(14);
    // scraperState = 1;
    chassis.distanceReset('B', 'L');
    chassis.moveToPoint(-24, -24, 1500, {.minSpeed = 60, .earlyExitRange = 4}, true);
    chassis.waitUntil(12); 
    scraperState = 0;
    chassis.waitUntil(40); //prev 43, 44
    scraperState = 1;

    //go to long
    chassis.turnToPoint(-42, -60, 1000, {.minSpeed = 30, .earlyExitRange = 4});
    intakeState = 1;
    chassis.moveToPoint(-45.5, -50, 1000, {.minSpeed = 60, .earlyExitRange = 4});
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('R', 'F');
    chassis.moveToPoint(-47.5, -25, 1000, {.forwards = false, .minSpeed = 80, .earlyExitRange = 4});
    intakeState = 3;
    trapdoorState = 1;
    chassis.sendVoltage(-12000 * 0.3, 1200);
    chassis.setPose(-1, -1, chassis.getPose().theta);
    chassis.distanceReset('R', 'F');

    //go to ml
    trapdoorState = 0;
    chassis.turnToHeading(180, 1000);
    chassis.moveToPoint(-46, -56, 1000, {.minSpeed = 60, .earlyExitRange = 4});
    //chassis.turnToHeading(180, 1000);
    //chassis.moveDistance(4, 1000, {.minSpeed = 127 * 0.5});
    chassis.sendVoltage(6000, 550); //prev 400
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('R', 'F');

    //go to mid goal
    chassis.moveDistance(-7, 500, {.forwards = false, .minSpeed = 80, .earlyExitRange = 3});
    chassis.distanceReset('R', 'F');
    chassis.turnToHeading(218, 500, {.minSpeed = 80, .earlyExitRange = 3});
    chassis.moveToPose(-13, -9.7, 220, 2000, {.forwards = false, .lead = 0.45, .minSpeed = 80}); //blindcode from x=-10
    chassis.moveDistance(-10, 500, {.forwards = false});
    chassis.turnToHeading(225, 500, {}, true);
    scraperState = 0;
    intakeState = 4;



}   