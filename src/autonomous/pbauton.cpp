#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void pbauton() {
    // beginning turn
    // intakeState = 1;

    chassis.moveDistance(3, 500);
    chassis.turnToHeading(90, 1000);

    chassis.setPose(1, -1, 90);
    chassis.distanceReset('R', 'F');

    return;

    // get the first pin
    chassis.moveToPoint(94, -64, 1000, {.minSpeed = 100, .earlyExitRange= 1.5});
    chassis.moveToPoint(109, -54, 1000, {.minSpeed = 70, .earlyExitRange= 1});

    // turn to the next pin and get it
    chassis.turnToHeading(-42, 500, {.minSpeed = 70, .earlyExitRange = 1.5});
    chassis.moveToPoint(93, -29, 1000, {.minSpeed = 70, .earlyExitRange= 1.5});

    //go to the quart
    chassis.turnToHeading(-97, 500, {.earlyExitRange = 1});
    chassis.moveToPoint(67.5, -27, 1500, {.minSpeed = 80, .earlyExitRange= 2});
    chassis.moveToPoint(47.5, -27, 1500, {.minSpeed = 80, .earlyExitRange= 2});

    // in the event it turns away from 90 consistently this is to adjust it
  //  chassis.turnToHeading(-90, 1000);

    chassis.moveToPoint(40.5,-27,1500,{.earlyExitRange = 1.5});
    chassis.moveDistance(-10, 1000, {.forwards = false,.earlyExitRange = 1.5});

    // wait a bit to calibrate
   // pros::delay(350);
    chassis.moveToPoint(12, -8, 1000,{.minSpeed = 70, .earlyExitRange = 1});

    // reset distance sensor 
    chassis.distanceReset('L', 'B');
pros::delay(100);
    // get pin near wall
    chassis.turnToHeading(-29,1000);
    chassis.moveDistance(24, 1000);
    chassis.turnToHeading(27, 500,{.earlyExitRange = 1});

    // align to diagonal
    chassis.moveDistance(31,1000, {.earlyExitRange= 1});
    chassis.turnToHeading(130, 500, {.earlyExitRange = 1});

    // get first pin, then second
    chassis.moveDistance(28, 1000, {.minSpeed = 90,.earlyExitRange = 2});
    chassis.moveDistance(30, 1000, { .minSpeed = 90, .earlyExitRange = 1});
}