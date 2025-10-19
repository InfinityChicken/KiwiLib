#include "sensors.hpp"
#include "pros/misc.h"

//color sort RUMBLE 
bool autonOneBlockActive = false;

//int color = 0;

int blockCount = 0;
int target = 3;

void colorSortRumble() {
    while(true) {    
        bool getItOutOfHere = false;
        bool colorDetected = false;
        //std::cout<<colorLeft.get_hue()<<"\n";

        if(autonColor == 'R') { //score red, sort blue
            if(200 < colorLeft.get_hue() && colorLeft.get_hue() < 240 || 200 < colorRight.get_hue() && colorRight.get_hue() < 240) {
                getItOutOfHere = true;
            } else {
                getItOutOfHere = false;
            }
        }
            
        else if(autonColor == 'B') { //score blue, sort red
            if(0 < colorLeft.get_hue() && colorLeft.get_hue() < 25 || 0 < colorRight.get_hue() && colorRight.get_hue() < 25) {
                getItOutOfHere = true;
            } else {
                getItOutOfHere = false;
            }
        }

        if(getItOutOfHere) {
            controller.rumble("---");
        }

        pros::delay(10);
    }
}

void distIntakeStop() {
    // bool blockDetected = false;

    int count = 0;

    while(true) {
        if(trapdoorState == 0 && intakeState == 1) {
            if(distance.get_distance() > 0 && distance.get_distance() < 51) {
                count++;

                if(count == 20) {
                    intakeState = 3;
                    count = 0;
                }

            }
        } else {
            count = 0;
        }

        // if(trapdoorState == 1){
        //     if(distance.get_distance() > 0 && distance.get_distance() < 76) {
        //         std::cout<<"dist threshold reached"<<"\n";
        //         if(!blockDetected) {
        //             std::cout<<"added block"<<"\n";
        //             blockDetected = true;
        //             blockCount++;
        //             if (blockCount >= target) {
        //                 intakeState = 3;     
        //                 std::cout<<"intake stop"<<"\n";
        //             }
        //         }
        //     } else {
        //         blockDetected = false;
        //     }

        // } else {  
        //     blockCount = 0;
        //     blockDetected = false;                          
        // }

        pros::delay(10);
    }
}

void antiJam() {

    int prevIntakeState = 0;
    int count = 0;

    while(true) {

        if(prevIntakeState != intakeState) { //if intake state changes, delay so no startup errors
            pros::delay(500); //TODO: ma
        }

        if(bottomRoller.get_actual_velocity() < 10) { //if vel low, do the thing
            prevIntakeState = intakeState; //record current intake state
            intakeState = 2; //outtake for 100ms
            pros::delay(100);
            intakeState = prevIntakeState; //return to old state
        }

        prevIntakeState = intakeState; //update intake state

        pros::delay(10);
    }
}


void autonOneBlock() {
    bool blockDetected = false;
    bool currentBlock = false;
    while(autonOneBlockActive) {
        bool inRange = colorLeft.get_proximity() > 0 && colorLeft.get_proximity() < 75 || colorRight.get_proximity() > 0 && colorRight.get_proximity() < 75;
        if(inRange) {
            if(!blockDetected) {
                blockDetected = true;
                currentBlock = true;
                if(currentBlock)
                    intakeState = 0;
            }
        } else {
            blockDetected = false;
        }

        pros::delay(10);
    }
}



// bool colorPressed;
// bool colorDetected;
// int color = 0;

// void updateColorSort() {
//     if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
//         if(!colorPressed) { //if the button is pressed
//             color++; //add color state by increment of 1
//             if(autonColor == 3) { //if 3, run fuction, 
//                 color = 0; // off
//             }
//         }
//         colorPressed = true; //run function
//     } else {
//         colorPressed = false; //if not, dont run function
//     }
// }

// // function to update color sort (so like switch color from red to blue to no sort)


// //function to run color sort
// /*detect the color of the block using hue values.
// Red sort: extend the piston to push out red, keep blue
// Blue: extend piston to push out blue, keep red

// when the hue value is between a certain range (red)
//     extend the piston (set piston state)
//     retract piston immediately
// */

// void runColorSort(){
//     while(true) {
//         if(autonColor == 0) {
//             pros::delay(10);
//             continue;
//         }
        
//         if(autonColor == 1) { //score red, sort blue
//             if(200 < colorLeft.get_hue() && colorLeft.get_hue() < 240 || 200 < colorRight.get_hue() && colorRight.get_hue() < 240) {
//                 if(!colorDetected) {
//                     colorDetected = true;
                    
//                     colorPistonState = 1;
//                     colorPistonState = 0;
//                 }
                
//             } 
//             else {
//                     colorDetected = false;
//                 }    
        
//         }
            
//         if(autonColor == 2) { //score blue, sort red
//             if(0 < colorLeft.get_hue() && colorLeft.get_hue() < 25 || 0 < colorRight.get_hue() && colorRight.get_hue() < 25) {
//                 if(!colorDetected) {
//                     colorDetected = true;
                    
//                     colorPistonState = 1;
//                     colorPistonState = 0;
//                 }
//             }
//             else {
//                     colorDetected = false;
//                 }
//         }
//     }
// }