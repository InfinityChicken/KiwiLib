#include "autonomous/autonomous.hpp"

void fourRight(){
    chassis.setPose(1, -1, 180);
    chassis.distanceReset('L', 'F');
    scraperState = 0;

    //wing
    chassis.moveDistance(4, 1000, {.minSpeed = 100});
    chassis.swingToHeading(340, lemlib::DriveSide::RIGHT, 1000, {.direction = lemlib::AngularDirection::CW_CLOCKWISE, .minSpeed = 100, .earlyExitRange = 10, .coast = false});
    chassis.turnToHeading(5, 1000, {.direction = lemlib::AngularDirection::CW_CLOCKWISE, .minSpeed = 30, .earlyExitRange = 6}); //prev 4
    chassis.moveToPoint(34, -17, 1000, {.minSpeed = 100});
    intakeState = 0;

    //move to ml
    pros::delay(3000);
    wingState = 1;
    trapdoorState = 0;
    intakeState = 1;
    chassis.turnToPoint(27.5, -31, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 5});
    chassis.moveToPoint(27.5, -31, 1000, {.forwards = false});
    chassis.swingToHeading(180, lemlib::DriveSide::RIGHT, 1000, {.direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE, .coast = false});
    chassis.turnToHeading(180, 1000);
    chassis.setPose(1, -1, chassis.getPose().theta);
    chassis.distanceReset('L', 'F');
    scraperState = 1;
    chassis.moveToPoint(47.5, -56, 1000, {.minSpeed = 127 * 0.4});
    chassis.sendVoltage(12000 * 0.4, 700);

    //go to low goal
    chassis.moveDistance(-7, 1000);
    chassis.distanceReset('L', 'F');
    scraperState = 0;
    chassis.turnToPoint(10, -14, 1000);
    chassis.moveToPose(10, -14, 315, 2000, {.minSpeed = 100, .earlyExitRange = 20});
    chassis.moveToPose(10, -14, 315, 2000, {.maxSpeed = 30});
    intakeState = 2;

}