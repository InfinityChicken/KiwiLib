#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"

void dsrtest() {
    chassis.moveDistance(20, 1000, {.minSpeed = 80});
    chassis.turnToHeading(90, 500, {.earlyExitRange = 5});
    chassis.turnToHeading(180, 500, {.earlyExitRange = 5});
    chassis.turnToHeading(270, 500, {.earlyExitRange = 5});
    chassis.turnToHeading(0, 500, {.earlyExitRange = 5});
    chassis.turnToHeading(-90, 500);
    pros::delay(1000);
    chassis.turnToHeading(-90, 1000);
    chassis.moveDistance(28, 1000);
    pros::delay(500);
    chassis.distResetX('F');
    pros::delay(5000);
    chassis.distResetY('R');
}