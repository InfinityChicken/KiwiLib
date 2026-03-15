#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/timer.hpp"
#include "pros/distance.hpp"
#include "main.h"
#include "drivecode/util.hpp"

void SAWP() {
    chassis.setPose(1, -1,90);
    chassis.distanceReset('F', 'R');

    //go to matchloader
    scraperState = 1;
    wingState = 1;
    chassis.moveToPoint(48, chassis.getPose().y, 1000);
    //chassis.moveDistance(29, 1000); //prev 31.25

    chassis.turnToHeading(180, 1000);

    //reset pose
    chassis.setPose(10, -10, chassis.getPose().theta); //set quadrant and angle
    chassis.waitUntilDone();
    chassis.distanceReset('L', 'F');

    //go into matchloader
    intakeState = 3;
    chassis.moveDistance(13.5, 1000);
    pros::delay(25); //prev 50, 100
    intakeState = 0;

    //do long goal
    chassis.moveToPoint(48, -25, 1000, {.forwards = false, .minSpeed = 60});
    chassis.moveToPoint(48, -20, 1000, {.forwards = false, .maxSpeed = 90}, true);
    intakeState = 1;
    intakeState = 3;
    pros::delay(700);
    scraperState = 0;
    //intakeState = 0;

    //swing out right
    chassis.sendVoltage(4000, 250);
    chassis.swingToPoint(23.5, -21, lemlib::DriveSide::RIGHT, 1000); //prev -23
    intakeState = 3;

    //move to first mid blocks
    intakeState = 3;
    chassis.moveToPoint(23.5, -21, 1500, {}, true); //prev minspeed 40, prev -23
    chassis.waitUntil(10.5);
    scraperState = 1;
    chassis.waitUntilDone();
    scraperState = 0;

    //turn and get second blocks
    chassis.turnToPoint(-24, -17.75, 1000); //if no work then change ttp to same as mtp
    scraperState = 0;
    chassis.moveToPoint(-24, -17.75, 1500, {.minSpeed = 40}, true); //prev -19.5 y, prev -19 x, prev minspeed 40
    chassis.waitUntil(31);
    scraperState = 1;

    // score mid goal
    chassis.waitUntilDone();
    midGoalState = 1;
    chassis.turnToPoint(-11, -5, 1000, {.forwards = false});
    chassis.moveToPoint(-11, -5, 1000, {.forwards = false, .minSpeed = 60}, true); //pre minspeed 60
    chassis.waitUntil(12);
    intakeState = 2; //antijam
    pros::delay(50);
    intakeState = 1;
    pros::delay(660);

    //move to ml
    scraperState = 1;
    chassis.moveToPose(-49, -46, 230, 1500, {}, true); //prev theta 225
    intakeState = 2; //outtake to bring blocks farther down intake
    pros::delay(80);
    intakeState = 0;
    intakeState = 3;
    midGoalState = 0;

    // turn and reset
    chassis.turnToHeading(180, 1000);
    chassis.distanceReset('R', 'F');

    //do ml
    intakeState = 3;
    midGoalState = 1;
    chassis.moveDistance(13.25, 1000);
    pros::delay(25); //prev 80, 100
    midGoalState = 0;
    //intakeState = 0;

    //score long goal
    chassis.moveToPoint(-48, -25, 1000, {.forwards = false, .minSpeed = 60});
    chassis.moveToPoint(-48, -20, 1000, {.forwards = false, .maxSpeed = 90}, true);
    intakeState = 1;
    // intakeState = 2;
    // pros::delay(50);
    intakeState = 3;
}

void counterSAWP() {
    chassis.setPose(1, -1,90);
    chassis.distanceReset('F', 'R');

    //go to matchloader
    scraperState = 1;
    wingState = 1;
    chassis.moveToPoint(46, chassis.getPose().y, 1000, {.minSpeed = 40});
    chassis.turnToHeading(180, 1000, {.minSpeed = 30});

    //reset pose
    chassis.setPose(10, -10, chassis.getPose().theta); //set quadrant and angle
    chassis.waitUntilDone();
    chassis.distanceReset('L', 'F');

    //go into matchloader
    intakeState = 3;
    chassis.moveDistance(14.5, 1000); //prev 13.5
    pros::delay(10); //prev 25. 50, 100

    //move into long goal
    chassis.moveToPoint(48, -25, 1000, {.forwards = false, .minSpeed = 60});
    leftMotors.move(-50); //push into goal
    rightMotors.move(-50);

    //score long goal
    intakeState = 2;
    pros::delay(50);
    intakeState = 1;
    pros::delay(650);
    chassis.distanceReset('L', 'F');
    scraperState = 0;

    //turn out right
    chassis.sendVoltage(4000, 150);
    chassis.turnToHeading(285, 1000);
    intakeState = 3;
    chassis.distanceReset('B', 'L');

    //chain to first mid blocks
    chassis.moveToPoint(24.6, -20.6, 1000, {.minSpeed = 60}, true); //prev 23.5
    chassis.waitUntil(10.5);

    //chain to second mid blocks
    chassis.turnToPoint(-25.8, -22, 1000, {.minSpeed = 60});
    chassis.moveToPoint(-24, -22, 1500, {.minSpeed = 80}, true);
    chassis.waitUntil(30);
    scraperState = 1;
    chassis.waitUntilDone();
    scraperState = 0;
    //chassis.distanceReset('F','L'); //might mess things up

    //chain to long goal
    chassis.turnToHeading(-160, 1000, {.minSpeed = 30});
    chassis.moveToPoint(-48.5, -44, 1000);
    //chassis.turnToPoint(-46, -27, 500, {.forwards = false});
    chassis.turnToHeading(180, 500); //250 timeout
    chassis.distanceReset('R', 'F');

    //score long
    chassis.moveToPoint(-46, -27, 1000, {.forwards = false, .minSpeed = 100});
    leftMotors.move(-50); //push into goal
    rightMotors.move(-50);
    chassis.turnToHeading(180, 500, {}, true);
    intakeState = 2;
    pros::delay(50);
    intakeState = 1;
    scraperState = 1;
    pros::delay(650);

    //do ml
    chassis.distanceReset('R', 'F');
    intakeState = 3;
    chassis.moveDistance(32, 1000, {.minSpeed = 30});
    chassis.turnToHeading(180, 100);
    //chassis.moveToPose(-48, -63, 180, 1500, {.minSpeed = 30});
    pros::delay(25);

    //go to mid goal and score
    chassis.turnToHeading(180, 500);
    chassis.moveDistance(-12.5, 1000, {.forwards = false, .minSpeed = 40});
    chassis.distanceReset('R', 'F');
    midGoalState = 1;
    chassis.turnToPoint(-8, -12.8, 1000, {.forwards = false, .minSpeed = 30});
    chassis.moveToPoint(-8, -12.8, 1500, {.forwards = false, .minSpeed = 100}, true);
    chassis.waitUntil(45);
    intakeState = 2; //antijam
    pros::delay(50);
    intakeState = 1;
    pros::delay(660);
}
