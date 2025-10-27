#include "autonomous/pidTuning.hpp"
#include "pros/misc.h"

bool upPressed = false;
bool downPressed = false;
bool rightPressed = false;
bool leftPressed = false;

bool xPressed = false;
bool aPressed = false;
bool yPressed = false;
bool bPressed = false;

bool l1Pressed = false;
bool l2Pressed = false;
bool r1Pressed = false;
bool r2Pressed = false;

int selectionMode = 0; //1 is kP, 2 is kD, 3 is slew
int pidmode = 1; //1 is lateral, 2 is angular
float multiplier = 1;

float kP = kP_lat;
float kD = kD_lat;
float slew = slew_lat;

void pidTuning() {
    //PID updates

    // pidmode == 2 means angular
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
        if(!xPressed) {
            xPressed = true;
            if(pidmode == 1) {
                pidmode = 2;
                
                kP = kP_ang;
                kD = kD_ang;
                slew = slew_ang;
            } else if(pidmode == 2) {
                pidmode = 1;

                kP = kP_lat;
                kD = kD_lat;
                slew = slew_lat;
            }
        } else {
            xPressed = false;
        }
    }

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
        if(!leftPressed) {
            leftPressed = true;
            if(multiplier == 1) {
                multiplier = 10;
            } else if(multiplier == 10) {
                multiplier = 0.1;
            } else if(multiplier == 0.1) {
                multiplier = 1;
            }
        } else {
            xPressed = false;
        }
    }
    
    //increment
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
        if(!upPressed) {
            upPressed = true;
            switch(selectionMode) {
                case 1: {
                    kP = kP + multiplier * 0.1;
                    std::cout<<"kP: "<<kP<<"\n";
                    break;
                }

                case 2: {
                    kD = kD + multiplier * 0.1;
                    std::cout<<"kD: "<<kD<<"\n";
                    break;
                }

                case 3: {
                    slew = slew + multiplier * 0.1;
                    std::cout<<"slew: "<<slew<<"\n";
                    break;
                }

            }
        } 
    } else {
        upPressed = false;
    }

    //decrement
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        if(!downPressed) {
            downPressed = true;
            switch(selectionMode) {
                case 1: {
                    kP = kP - multiplier * 0.1;
                    std::cout<<"kP: "<<kP<<"\n";
                    break;
                }

                case 2: {
                    kD = kD - multiplier * 0.1;
                    std::cout<<"kD: "<<kD<<"\n";
                    break;
                }

                case 3: {
                    slew = slew - multiplier * 0.1;
                    std::cout<<"slew: "<<slew<<"\n";
                    break;
                }

            }
            
        } 
    } else {
        downPressed = false;
    }

    //cycle tune value
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        if(!rightPressed) {
            rightPressed = true;

            selectionMode++;

            if (selectionMode == 4) {
                selectionMode = 1;
                std::cout<<selectionMode<<"\n";
            }
        }
    } else {
        rightPressed = false;
    }

    //move 12 inches
if(pidmode == 1){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) { //l1, long goal (indexer outtake), state 1
        if(!l1Pressed) {
            l1Pressed = true;

            chassis.setPose(0, 0, 0);
            chassis.moveToPoint(0, 12, 10000);
            std::cout<<"Movement run, ending coord: "<<chassis.getPose().y<<"\n";
        }
    } else {
        l1Pressed = false;
    }

    //move 24 inches
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { //l1, long goal (indexer outtake), state 1
        if(!l2Pressed) {
            l2Pressed = true;

            chassis.setPose(0, 0, 0);
            chassis.moveToPoint(0, 24, 10000);
            std::cout<<"Movement run, ending coord: "<<chassis.getPose().y<<"\n";
        }
    } else {
        l2Pressed = false;
    }


    //move 36 inches
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { //l1, long goal (indexer outtake), state 1
        if(!r1Pressed) {
            r1Pressed = true;

            chassis.setPose(0, 0, 0);
            chassis.moveToPoint(0, 36, 10000);
            std::cout<<"Movement run, ending coord: "<<chassis.getPose().y<<"\n";
        }
    } else {
        r1Pressed = false;
    }

    //move 48 inches
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) { //l1, long goal (indexer outtake), state 1
        if(!r2Pressed) {
            r2Pressed = true;

            chassis.setPose(0, 0, 0);
            chassis.moveToPoint(0, 48, 10000);
            std::cout<<"Movement run, ending coord: "<<chassis.getPose().y<<"\n";
        }
    } else {
        r2Pressed = false;
    }

    // --------- Move back ---------
// move back to start 
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) { //l1, long goal (indexer outtake), state 1
        if(!aPressed) {
            aPressed = true;

            chassis.setPose(0, 0, 0);
            chassis.moveToPoint(0, 0, 10000, {.forwards = false});
            std::cout<<"Movement run, ending coord: "<<chassis.getPose().y<<"\n";
        }
    } else {
        aPressed = false;
    }


} else if(pidmode == 2) {
    // turn 45
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) { //l1, long goal (indexer outtake), state 1
        if(!l1Pressed) {
            l1Pressed = true;

            chassis.setPose(0, 0, 0);
            chassis.turnToHeading(45, 1000);
            std::cout<<"Movement run, ending heading: "<<chassis.getPose().theta<<"\n";
        }
    } else {
        l1Pressed = false;
    }

    //turn 90
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { //l1, long goal (indexer outtake), state 1
        if(!l2Pressed) {
            l2Pressed = true;

            chassis.setPose(0, 0, 0);
            chassis.turnToHeading(90, 1000);
            std::cout<<"Movement run, ending heading: "<<chassis.getPose().theta<<"\n";
        }
    } else {
        l2Pressed = false;
    }


    //turn 180
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { //l1, long goal (indexer outtake), state 1
        if(!r1Pressed) {
            r1Pressed = true;

            chassis.setPose(0, 0, 0);
            chassis.turnToHeading(180, 2000);
            std::cout<<"Movement run, ending heading: "<<chassis.getPose().theta<<"\n";
        }
    } else {
        r1Pressed = false;
    }

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) { //l1, long goal (indexer outtake), state 1
        if(!yPressed) {
            yPressed = true;

            chassis.setPose(0, 0, 0);
            chassis.turnToHeading(0, 2000);
            std::cout<<"Movement run, ending heading: "<<chassis.getPose().theta<<"\n";
        }
    } else {
        yPressed = false;
    }



}

    if(pidmode == 1) {
        kP_lat = kP;
        kD_lat = kD;
        slew_lat = slew;
    } else if(pidmode == 2) {
        kP_ang = kP;
        kD_ang = kD;
        slew_ang = slew;
    }

    

    controller.set_text(0, 0, "select: "+std::to_string(selectionMode)+", mode:"+std::to_string(pidmode));
    
}