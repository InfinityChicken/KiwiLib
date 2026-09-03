#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "drivecode/claw.hpp"
#include "drivecode/cascade.hpp"

void drc() {
    // chassis reset
    chassis.setPose(0, 0, 0);

    // claw close so pin doesn't fall
    clawState = 0;
    pros::delay(100); // wait for claw to close

    // flip toggle (2x)
    for (int i = 0; i < 2; i++) {
        chassis.moveToPoint(0, 0, 1000);
        chassis.moveToPoint(0, 0, 1000);
    }

    // move to goal
    chassis.moveToPoint(0.,0,1000, {.minSpeed = 100, .earlyExitRange = 3});
    chassis.turnToHeading(180, 1000, {.minSpeed = 100, .earlyExitRange = 20});
    chassis.moveToPose(0, 0, 225, 1000, {.minSpeed = 80});

    // score pin
    clawState = 0; // claw open
    pros::delay(100); // wait for claw to open
    chainBarState = 1; // chain bar score
    // cascade up?
    chainBarState = 0; // chain bar load state
    // cascade down?

    // align with cup on wall
    rollerState = 1; // roller claw start rolling
    chassis.moveToPose(0, 0, 180, 1000, {.minSpeed = 80});
    clawState = 0; // claw open

    // move & grab claw
    // slow down near the target drastically
    chassis.moveToPoint(0, 0, 1000, {.minSpeed = 80, .earlyExitRange = 2});
    chassis.moveToPoint(0, 0, 1000, {.maxSpeed = 80});
    clawState = 1; // claw close
    pros::delay(100); // wait for claw to close
    
    // move to goal
    chassis.moveDistance(20, 1000);

    // score pin
    clawState = 0; // claw open
    pros::delay(100); // wait for claw to open
    chainBarState = 1; // chain bar score
    // cascade up?
    chainBarState = 0; // chain bar load state
    // cascade down?

    // move out of small area to matchload area
    chassis.moveDistance(10, 1000, {.minSpeed = 90, .earlyExitRange = 3});
    chassis.turnToHeading(90, 1000, {.minSpeed = 100, .earlyExitRange = 10});
    chassis.moveToPoint(0, 0, 1000);
}