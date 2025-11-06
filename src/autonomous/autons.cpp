#include "autonomous/autons.hpp"
#include "pros/rtos.hpp"
#include <math.h>

void leftNew() {
    //three blocks
    chassis.turnToPoint(-6.23, 22.3, 1000);
    intakeState = 3;
    chassis.moveDistance(10, 1000, {.minSpeed = 80, .earlyExitRange = 3}); //motion chain for speed
    chassis.moveToPoint(-6.23, 22.3, 1000, {.maxSpeed = 25});

    //mid goal
    chassis.turnToPoint(1.28, 32.5, 1000); //42 degrees
    chassis.moveToPoint(1.28, 32.5, 1000);
    trapdoorState = 1;
    intakeState = 1;
    pros::delay(1500);
    intakeState = 0;

    //back up and go to match loader
    chassis.moveToPoint(-31.5, 6.9, 2500, {.forwards = false});
    chassis.turnToPoint(-30.25, -6.6, 1000);
    trapdoorState = 0;
    littleWillState = 1;
    intakeState = 3;
    chassis.moveToPoint(-30.25, -15, 2500, {.maxSpeed = 25});
    pros::delay(250); 

    //score long goal
    chassis.moveToPoint(-30.25, 2.3, 1000, {.forwards = false});
    littleWillState = 0;
    hoodState = 1;
    chassis.turnToPoint(-30.25, 13.8, 1000);
    chassis.moveToPoint(-30.25, 13.8, 1000);
    trapdoorState = 1;
    intakeState = 1;

}

void rightNew() {
    //three blocks
    chassis.turnToPoint(6.23, 22.3, 1000);
    intakeState = 3;
    chassis.moveDistance(10, 1000, {.minSpeed = 80, .earlyExitRange = 3}); //motion chain for speed
    chassis.moveToPoint(6.73, 25, 1000, {.maxSpeed = 25});

    //mid goal
    chassis.turnToPoint(-1.78, 35, 1000); //42 degrees
    chassis.moveToPoint(-1.78, 35, 1000);
    velValue = 12000*0.7;
    intakeState = 2;
    pros::delay(1750);
    intakeState = 0;
    velValue = 12000;

    //back up and go to match loader
    chassis.moveToPoint(32.5, 6.9, 2250, {.forwards = false});
    chassis.turnToPoint(31, -6.6, 1000);
    trapdoorState = 0;
    littleWillState = 1;
    intakeState = 3;
    chassis.moveToPoint(30.8, -9, 2000, {.maxSpeed = 25});
    // pros::delay(100);
    // chassis.moveDistance(5, 750, {.maxSpeed = 25});
    pros::delay(250); //750

    //score long goal
    chassis.moveToPoint(30.8, 2.3, 1000, {.forwards = false, .maxSpeed = 80});
    littleWillState = 0;
    hoodState = 1;
    chassis.turnToPoint(30.3, 13.8, 1000);
    chassis.moveToPoint(30.3, 13.8, 1000);
    trapdoorState = 1;
    intakeState = 1;

}

void sawpNew() {
    //go to matchloader
    chassis.moveToPoint(0, 27, 1000);
    littleWillState = 1;
    intakeState = 1; //usually 3
    chassis.turnToHeading(90, 850);
    //chassis.turnToPoint(6.2, 30, 1000);
    chassis.moveToPoint(6.2, 30, 500);
    chassis.moveToPoint(8, 30, 500, {.maxSpeed = 25});
    pros::delay(100);

    //back up and score long goal
    chassis.moveToPoint(-4.78, 30, 500, {.forwards = false});
    intakeState = 3;
    littleWillState = 0;
    hoodState = 1; 
    chassis.turnToPoint(-15.5, 31.65, 850); //TODO: tune perchance
    chassis.moveToPoint(-15.5, 31.65, 500, {.minSpeed = 30}, true);
    chassis.turnToHeading(-90, 500, {}, true);
    pros::delay(150);
    trapdoorState = 1;
    intakeState = 1;
    pros::delay(1250); //750 -> 1250 3:29 tues nov 4
    intakeState = 0;
    
    //move back, turn
    chassis.moveDistance(-14, 850, {.forwards = false});
    chassis.turnToPoint(-37, -3.2, 650);
    intakeState = 3;

    //move to three
    chassis.moveDistance(10, 1000, {.maxSpeed = 127, .minSpeed = 90, .earlyExitRange = 1}, false);
    chassis.moveDistance(5, 1000, {.maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 1}, false);
    chassis.moveToPoint(-37, -3.2, 1250, {.maxSpeed = 55}, true);
    pros::delay(1200); //TODO: required so that the weird intake thing doesn't happen idk why...
    velValue = 12000*0.8;
    intakeState = 2;
    pros::delay(1000);
 
    //go to other blocks
    intakeState = 3;
    hoodState = 0;
    trapdoorState = 0;
    chassis.moveToPoint(-28.4, 5.9, 500, {.forwards = false});
    chassis.turnToPoint(-28.34, -21.13, 1000);
    chassis.moveToPoint(-28.34, -21.13, 750, {.minSpeed = 60, .earlyExitRange = 3}); //TODO: early exit range
    chassis.moveToPoint(-28.34, -31.8, 500, {.maxSpeed = 35});

    //mid goal
    //chassis.turnToPoint(-34.9,-31.1, 1000);
    chassis.turnToHeading(-47, 1000);
    //chassis.moveToPoint(-36, -29.7, 1000, {}, true);    // trapdoorState = 1;
    chassis.moveDistance(5, 1000, {.minSpeed = 40});
    //pros::delay(100);
    trapdoorState = 1;
    intakeState = 1;
}

// void longGoalLeft() {
//    //go to 3 blocks
//    chassis.turnToHeading(-17, 1000);
//    intakeState = 3; //one ball
//    //intakeState = 1; //4 ball
//    chassis.moveToPoint(-7.5, 25.4,1500, {.maxSpeed = 40});
//    pros::delay(100);
//    intakeState = 0; //uncomment for one ball

//    //go to mid goal
//    chassis.turnToHeading(42, 1000);
//    chassis.moveToPoint(1, 33.95, 1500);
//    chassis.turnToHeading(42, 1000);
//    trapdoorState = 1; 
//     //pros::delay(100);
//    intakeState = 1;
//    pros::delay(450); // 1500 all balls //450 auton one ball 
//    intakeState = 5;
//    pros::delay(250);
//    intakeState = 0;
//    trapdoorState = 0;
//     pros::delay(150);


//    // driving reverse to the matchload
//    chassis.moveToPoint(-32, 1.8, 1250, {.forwards=false});
//    chassis.waitUntilDone();
//    //trapdoorState = 0; //only for 4 on mid
//    littleWillState = 1;
//    chassis.turnToHeading(182, 1000);
//    chassis.waitUntilDone();
//    intakeState = 3;
   
//    // driving into the matchloader
//    chassis.moveToPoint(-32.5, -10, 1500, {.maxSpeed = 100}); //TODO: og y -14 (zach)
//    //chassis.moveToPoint(-32, -8, 500, {.forwards = false});
//    pros::delay(400); // wait to intake //TODO: might have to tune if we only want 3

   
//    //back up from match loader
//    chassis.moveToPoint(-31, 0.4, 1000, {.forwards = false, .maxSpeed = 90});
//    chassis.waitUntilDone();
//    hoodState = 1;
//    littleWillState = 0;

   
//    //turn to long goal and score
//    trapdoorState = 1;
//    pros::delay(500);
//    chassis.turnToHeading(-4, 1000);
//    chassis.waitUntilDone();
//    chassis.moveToPoint(-32, 21, 1500, {.maxSpeed = 60}); //og 17 (zach)
//    chassis.waitUntilDone();
//    chassis.turnToHeading(3, 500);
//    hoodState = 1;
//    intakeState = 1;

// //    while(true) { //TODO: what is this - zach
// //     if(autonColor == 'R') {
// //         if(200 < colorLeft.get_hue() && colorLeft.get_hue() < 240 || 200 < colorRight.get_hue() && colorRight.get_hue() < 240) {
// //             intakeState = 0;
// //         }
// //     } else if(autonColor == 'B') {
// //         if(0 < colorLeft.get_hue() && colorLeft.get_hue() < 25 || 0 < colorRight.get_hue() && colorRight.get_hue() < 25) {
// //             intakeState = 0;
// //         }
// //     }
// //    }

// }

// void longGoalRight() {
//    //go to 3 blocks
//    chassis.turnToHeading(17, 1000);
//    intakeState = 3;
//    chassis.moveToPoint(7.5, 25.4, 1500, {.maxSpeed = 40});
//    pros::delay(250);
//    //intakeState = 0;

//    //go to mid low goal
//    chassis.turnToHeading(-42.9, 1000);
//    chassis.moveToPoint(-1.27, 33.95, 1500, {.maxSpeed=80});
//    chassis.waitUntilDone();
//    intakeState = 2;
//    pros::delay(1500);
//    intakeState = 3;
//    pros::delay(250);

//    // driving reverse to the matchload
//    chassis.moveToPoint(31, 4.9, 1250, {.forwards=false});
//    chassis.waitUntilDone();
//    trapdoorState = 0; //only for 4 on mid
//    littleWillState = 1;
//    chassis.turnToHeading(182, 1100);
//    chassis.waitUntilDone();
//    intakeState = 3;
   
//    // driving into the matchloader vfggg
//    chassis.moveToPoint(31.5, -10, 1000, {.maxSpeed = 100});
//    pros::delay(500);

//    //back up from match loader
//    chassis.moveToPoint(31, 0.4, 1000, {.forwards = false, .maxSpeed = 90});
//    chassis.waitUntilDone();
//    hoodState = 1;
//    littleWillState = 0;
   
//    //turn to long goal and score
//    trapdoorState = 1;
//    pros::delay(500);
//    chassis.turnToHeading(0, 1000);
//    chassis.waitUntilDone();
//    chassis.moveToPoint(32.7, 14.41, 1500, {.maxSpeed = 60}); //og 17 (zach)
//    chassis.waitUntilDone();
//    intakeState = 2;
//    pros::delay(100);
//    hoodState = 1;
//    intakeState = 1;
// //STOPPED HERE



//    /* //TODO: thingy ad;jf
//    // driving reverse to the matchload
//    chassis.moveToPoint(30.5, 2, 2000, {.forwards=false});
//    chassis.waitUntilDone();
//    littleWillState = 1;
//    chassis.turnToHeading(-180, 1300);
//    chassis.waitUntilDone();
//    intakeState = 3;
   
//    // driving into the matchloader
//    chassis.moveToPoint(30.5, -10, 1250, {.maxSpeed = 100}); //TODO: og x 32.5
//    //pros::delay(250); // wait to intake

//    //back up from match loader
//    chassis.moveToPoint(30.5, 0.4, 1000, {.forwards = false, .maxSpeed = 90});
//    chassis.waitUntilDone();
//    pros::delay(100);
//    hoodState = 1;
//    littleWillState = 0;

   
//    //turn to long goal and score
//    trapdoorState = 1;
//    pros::delay(500);
//    chassis.turnToHeading(4, 1000);
//    chassis.waitUntilDone();
//    chassis.moveToPoint(31, 16.51, 1000, {.maxSpeed = 40});
//    chassis.turnToHeading(-4, 1000);
//    chassis.waitUntilDone();
//    hoodState = 1;
//    intakeState = 1;

//    while(true) {
//     if(autonColor == 'R') {
//         if(200 < colorLeft.get_hue() && colorLeft.get_hue() < 240 || 200 < colorRight.get_hue() && colorRight.get_hue() < 240) {
//             intakeState = 0;
//         }
//     } else if(autonColor == 'B') {
//         if(0 < colorLeft.get_hue() && colorLeft.get_hue() < 25 || 0 < colorRight.get_hue() && colorRight.get_hue() < 25) {
//             intakeState = 0;
//         }
//     }
//    }
//     */

// }

// void skills() {
//     //go to match loader
//     littleWillState = 1;
//     intakeState = 3;
//     chassis.moveToPoint(0,27.5, 1000);
//     chassis.turnToHeading(91, 1000);
//     chassis.moveToPoint(4, 27.5, 1000, {.minSpeed = 50});
//     chassis.moveToPoint(10, 27.5, 500, {.maxSpeed = 60});
//     pros::delay(1750); //750 perfect

//     //go back and score long goal
//     chassis.moveToPoint(-4, 30, 500, {.forwards = false, .maxSpeed = 90});
//     intakeState = 0;
//     littleWillState = 0;
//     hoodState = 1;
//     trapdoorState = 1;
//     chassis.turnToHeading(-83, 750, {.maxSpeed = 90});
//     chassis.moveToPoint(-16, 30, 1000, {.minSpeed = 50});
//     intakeState = 1;
//     pros::delay(2500);

//     //go to low
//     chassis.moveToPoint(-1.97, 31.6, 500, {.forwards = false});
//     chassis.turnToHeading(-130, 500);
//     intakeState = 3;
//     chassis.moveToPoint(-27.5, 4.7, 1000, {.maxSpeed = 40});
//     chassis.moveToPoint(-37, -3.1, 2000, {.maxSpeed = 40});
//     pros::delay(1000);
//     velValue = 12000*0.8;
//     intakeState = 2;
//     velValue = 12000;
//     pros::delay(1500);

//     //other blocks
//     chassis.moveToPoint(-25.3, 10.1, 500, {.forwards = false});
//     intakeState = 3;
//     hoodState = 0;
//     chassis.turnToHeading(180, 500);
//     chassis.moveToPoint(-28, -18, 1000, {.minSpeed = 60});
//     chassis.moveToPoint(-28, -40, 2000, {.maxSpeed = 25}); 
//     pros::delay(500);

//     //score mid
//     chassis.turnToHeading(-45, 1000);
//     chassis.moveToPoint(-36, -32, 1000);
//     //pros::delay(500);
//     intakeState = 1;
//     trapdoorState = 1;
//     pros::delay(1500);

//     //other match loader
//     chassis.moveToPoint(3.3, -65.2, 2000, {.forwards = false});
//     trapdoorState = 0;
//     intakeState = 3;
//     littleWillState = 1;
//     chassis.turnToHeading(90, 1000);
//     chassis.moveToPoint(7, -65, 1000, {.minSpeed = 50});
//     chassis.moveToPoint(11, -65, 500, {.maxSpeed = 60});
//     pros::delay(1750);

//     //long goal
//     chassis.moveToPoint(-2.17, -64.2, 1000, {.forwards = false});
//     intakeState = 0;
//     littleWillState = 0;
//     hoodState = 1;
//     trapdoorState = 1;
//     chassis.turnToHeading(-90, 1000);
//     chassis.moveToPoint(-13.7, -64, 1000);
//     intakeState = 1;
//     pros::delay(2500);

//     //park
//     chassis.moveToPoint(-2, -64, 1000, {.forwards = false});
//     chassis.turnToHeading(135, 1000);
//     intakeState = 0;
//     chassis.moveToPose(-4.1, -14.95, -90, 5000, {.forwards = false, .lead = 0.8});
//     pros::delay(500);
//     chassis.moveToPoint(20, -16, 2000, {.forwards = false, .minSpeed = 127});
//     chassis.moveToPoint(20, -16, 2000, {.forwards = false, .minSpeed = 127});
    

// }

// void sawp() {
//     //go to match loader
//     littleWillState = 1;
//     intakeState = 3;
//     chassis.moveToPoint(0,27, 1000);
//     chassis.turnToHeading(91, 1000);
//     chassis.moveToPoint(2.75, 25, 1000, {.minSpeed = 40}); 
//     chassis.moveToPoint(6, 27.5, 250, {.minSpeed = 80});
//     pros::delay(500); //750 perfect

//     //go back and score long goal
//     chassis.moveToPoint(-4, 30, 500, {.forwards = false, .maxSpeed = 90});
//     intakeState = 0;
//     littleWillState = 0;
//     hoodState = 1;
//     trapdoorState = 1;
//     chassis.turnToHeading(-83, 750, {.maxSpeed = 90});
//     chassis.moveToPoint(-16, 30, 1000, {.minSpeed = 50});
//     intakeState = 1;
//     pros::delay(1500);

//     //go to low
//     chassis.moveToPoint(-1.97, 31.6, 500, {.forwards = false});
//     chassis.turnToHeading(-130, 500);
//     intakeState = 3;
//     chassis.moveToPoint(-29.6, 2.9, 1000, {.maxSpeed = 40});
//     chassis.moveToPoint(-35.5, -1.6, 1000);
//     pros::delay(100);
//     velValue = 12000*0.8;
//     intakeState = 2;
//     velValue = 12000;
//     pros::delay(1000);

//     //other blocks
//     chassis.moveToPoint(-25.3, 10.1, 500, {.forwards = false});
//     intakeState = 3;
//     hoodState = 0;
//     chassis.turnToHeading(180, 500);
//     chassis.moveToPoint(-28, -18, 1000, {.minSpeed = 80});
//     chassis.moveToPoint(-28, -38.4, 500, {.maxSpeed = 40}); 

//     //score mid
//     chassis.turnToHeading(-45, 1000);
//     intakeState = 1;
//     chassis.moveToPoint(-36, -32, 1000);
//     pros::delay(100);
//     trapdoorState = 1;

// }

// void sawpLow() {
//     //go to match loader
//     littleWillState = 1;
//     intakeState = 3;
//     chassis.moveToPoint(0,28.5, 1000);
//     chassis.turnToHeading(89, 750);
//     chassis.moveToPoint(4, 28.5, 1000, {.minSpeed = 50});
//     pros::delay(750);

//     //go back and score long goal
//     chassis.moveToPoint(-6, 29.5, 500, {.forwards = false, .maxSpeed = 100});
//     intakeState = 0;
//     littleWillState = 0;
//     hoodState = 1;
//     trapdoorState = 1;
//     chassis.turnToHeading(-83, 750, {.maxSpeed = 90});
//     chassis.moveToPoint(-16, 29.5, 1000, {.minSpeed = 50});
//     intakeState = 1;
//     pros::delay(1500);

//     //go to low
//     chassis.moveToPoint(-1.97, 31.6, 500, {.forwards = false});
//     chassis.turnToHeading(-125, 500);
//     intakeState = 3;
//     chassis.moveToPoint(-29.6, 2.9, 1000, {.maxSpeed = 40});
//     chassis.moveToPoint(-36.9, -1.6, 1000);
//     pros::delay(250);
//     velValue = 12000*0.8;
//     intakeState = 2;
//     velValue = 12000;
//     pros::delay(1000);

//     //other blocks
//     chassis.moveToPoint(-26.2, 9.1, 500, {.forwards = false});
//     intakeState = 3;
//     chassis.turnToHeading(180, 500);
//     chassis.moveToPoint(-29, -18, 1000, {.minSpeed = 80});
//     chassis.moveToPoint(-29, -38.4, 500, {.maxSpeed = 40}); 

//     //long goal
//     chassis.turnToHeading(90, 500);
//     chassis.moveToPose(-16, -64.8, -90, 2000, {.lead = 0.5});
//     chassis.moveToPoint(-18, -65, 1000);
//     intakeState = 1;

// }

// void sawpMid() {
//     //go to match loader
//     littleWillState = 1;
//     intakeState = 3;
//     chassis.moveToPoint(0,28.5, 1000);
//     chassis.turnToHeading(88, 750);
//     chassis.moveToPoint(6, 30, 1000, {.minSpeed = 50});
//     pros::delay(400);

//     //go back and score long goal
//     chassis.moveToPoint(-6, 29.5, 500, {.forwards = false, .maxSpeed = 100});
//     intakeState = 1;
//     littleWillState = 0;
//     chassis.turnToHeading(-81, 1000);
//     hoodState = 1;
//     chassis.moveToPoint(-16, 31, 1000, {.minSpeed = 50});
//     trapdoorState = 1;
//     pros::delay(750); //all blocks 1500
//     intakeState = 0;
//     trapdoorState = 0;

//     //get first clump of blocks
//     chassis.moveToPoint(-1.97, 31.6, 500, {.forwards = false});
//     chassis.turnToHeading(-125, 500);
//     hoodState = 0;
//     intakeState = 3;
//     chassis.moveToPoint(-15, 18.7, 500, {.minSpeed = 80});
//     chassis.moveToPoint(-27, 6.7, 1000, {.maxSpeed = 40}); 
//     pros::delay(100);

//     // get second clump of blocks
//     chassis.turnToHeading(180, 500);
//     chassis.moveToPoint(-27, -18, 1000, {.minSpeed = 80});
//     chassis.moveToPoint(-27, -36, 500, {.maxSpeed = 40});
//     pros::delay(100); 

//     //mid goal
//     chassis.turnToHeading(-45, 1000);
//     chassis.moveToPoint(-34.8, -30.52, 1000);
//     trapdoorState = 1;
//     intakeState = 1;
//     pros::delay(250); //750 for 3 blocks
//     intakeState = 0;
//     trapdoorState = 0;

//     //long goal
//     chassis.moveToPoint(2.8, -64.2, 2000, {.forwards = false});
//     hoodState = 1;
//     chassis.turnToHeading(-87, 500);
//     chassis.moveToPoint(-16, -63.3, 1000);
//     trapdoorState = 1;
//     intakeState = 1;
// }