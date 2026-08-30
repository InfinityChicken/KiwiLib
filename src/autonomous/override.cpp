#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void override() {
    // beginning turn
    // intakeState = 1;

    chassis.setPose(1, -1, 90);
    chassis.distanceReset('R', 'F');

    // get the first pin
    chassis.moveToPoint(94, -64, 750, {.minSpeed = 80, .earlyExitRange = 0.4});
    chassis.moveToPoint(110, -54, 750);

    // turn to the next pin and get it
    chassis.turnToHeading(-45, 650);
    chassis.moveToPoint(95, -32, 1500, {.minSpeed = 80});

    //go to the quart
    chassis.turnToHeading(-87, 600);
    chassis.moveDistance(27, 1000, {.minSpeed = 110, .earlyExitRange = 2});
    chassis.moveDistance(20, 1000, {.maxSpeed = 50, .minSpeed = 40});
    // chassis.moveToPoint(50, -32, 800, {.maxSpeed = 50, .minSpeed = 40});
    
    // in the event it turns away from 90 consistently this is to adjust it
    chassis.turnToHeading(-90, 1000);

    chassis.moveDistance(-10, 750, {.forwards = false, .minSpeed = 95});

    // wait a bit to calibrate
    pros::delay(350);

    // go to the wall to distreset
    chassis.turnToHeading(-60, 800);
    chassis.moveDistance(52, 1000, {.minSpeed = 90, .earlyExitRange = 0.5});

    // turn to a bit tilted to get more clearance
    chassis.turnToHeading(5, 600);

    // reset distance sensor 
    chassis.distanceReset('L', 'B');

    // move to pin
    chassis.moveDistance(24.5, 1000);
    chassis.turnToHeading(-90, 600);

    // get le pin because france and align to the line based on the grid
    chassis.moveDistance(6, 300, {.minSpeed = 80});
    chassis.moveDistance(-32, 300, {.forwards = false, .minSpeed = 80});

    // align to line
    chassis.turnToHeading(130, 850, {.direction = AngularDirection::CW_CLOCKWISE});
    pros::delay(500);

    // // move to center
    // chassis.moveToPoint(100, 0, 1000, {.maxSpeed = 80, .minSpeed = 50, .earlyExitRange = 1});
    // chassis.turnToHeading(133, 850);
    // chassis.moveToPoint(124, -24, 1000, {.minSpeed = 100});

    // // Code here was previously used to move to center
    // // zcheng has decreed that don't do this.
    // go to the center 
    chassis.moveDistance(36, 1500, {.maxSpeed = 90, .minSpeed = 80, .earlyExitRange = 2});

    // previously used to make sure robot was fully aligned
    // chassis.turnToHeading(133, 850, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .earlyExitRange = 1});

    chassis.moveDistance(15, 1500, {.minSpeed = 110});
}