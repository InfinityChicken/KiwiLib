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
float multiplier = 1.0;

float kP = kP_ang;
float kD = kD_ang;
float slew = slew_ang;

void pidTuning() {
    //PID updates

    // x: cycle between lateral and angular testing
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
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
        } 
    } else {
        xPressed = false;
    }

    //left: 
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
        if(!leftPressed) {
            leftPressed = true;
            if(multiplier == 1) {
                multiplier = 10;
            } else if(multiplier == 10) {
                multiplier = 0.1;
            } else {
                multiplier = 1;
            }
        } 
    } else {
        leftPressed = false;
    }
    
    //up: increment
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
        if(!upPressed) {
            upPressed = true;
            switch(selectionMode) {
                case 1: {
                    kP = kP + multiplier;
                    std::cout<<"kP: "<<kP<<"\n";
                    break;
                }

                case 2: {
                    kD = kD + multiplier;
                    std::cout<<"kD: "<<kD<<"\n";
                    break;
                }

                case 3: {
                    slew = slew + multiplier;
                    std::cout<<"slew: "<<slew<<"\n";
                    break;
                }

            }
        } 
    } else {
        upPressed = false;
    }

    //up: decrement
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        if(!downPressed) {
            downPressed = true;
            switch(selectionMode) {
                case 1: {
                    kP = kP - multiplier;
                    std::cout<<"kP: "<<kP<<"\n";
                    break;
                }

                case 2: {
                    kD = kD - multiplier;
                    std::cout<<"kD: "<<kD<<"\n";
                    break;
                }

                case 3: {
                    slew = slew - multiplier;
                    std::cout<<"slew: "<<slew<<"\n";
                    break;
                }

            }
            
        } 
    } else {
        downPressed = false;
    }

    //right: cycle value being tuned
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

    //FOR LATERAL:
    if(pidmode == 1) {

        //l1: 12 inches forward
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            if(!l1Pressed) {
                l1Pressed = true;

                chassis.setPose(0, 0, 0);
                chassis.moveToPoint(0, 12,3000);
                std::cout<<"Movement run, ending coord: "<<chassis.getPose().y<<"\n";
            }
        } else {
            l1Pressed = false;
        }

        //l2: 24 inches forward
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            if(!l2Pressed) {
                l2Pressed = true;

                chassis.setPose(0, 0, 0);
                chassis.moveToPoint(0, 24, 3000);
                std::cout<<"Movement run, ending coord: "<<chassis.getPose().y<<"\n";
            }
        } else {
            l2Pressed = false;
        }

        //r1: 36 inches forward
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            if(!r1Pressed) {
                r1Pressed = true;

                chassis.setPose(0, 0, 0);
                chassis.moveToPoint(0, 36, 3000);
                std::cout<<"Movement run, ending coord: "<<chassis.getPose().y<<"\n";
            }
        } else {
            r1Pressed = false;
        }

        //r2: 48 inches forward
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            if(!r2Pressed) {
                r2Pressed = true;

                chassis.setPose(0, 0, 0);
                chassis.moveToPoint(0, 48, 3000);
                std::cout<<"Movement run, ending coord: "<<chassis.getPose().y<<"\n";
            }
        } else {
            r2Pressed = false;
        }

        //a: move to (0, 0)
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) { //move to start
            if(!aPressed) {
                aPressed = true;

                chassis.setPose(0, 0, 0);
                chassis.moveToPoint(0, 0, 3000, {.forwards = false});
                std::cout<<"Movement run, ending coord: "<<chassis.getPose().y<<"\n";
            }
        } else {
            aPressed = false;
        }
    } 

    //FOR ANGULAR:
    else if(pidmode == 2) {
        //l1: turn 45
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) { //45
            if(!l1Pressed) {
                l1Pressed = true;

                chassis.setPose(0, 0, 0);
                chassis.turnToHeading(45, 3000);
                std::cout<<"Movement run, ending heading: "<<chassis.getPose().theta<<"\n";
            }
        } else {
            l1Pressed = false;
        }

        //l2: turn 90
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { //90
            if(!l2Pressed) {
                l2Pressed = true;

                chassis.setPose(0, 0, 0);
                chassis.turnToHeading(90, 3000);
                std::cout<<"Movement run, ending heading: "<<chassis.getPose().theta<<"\n";
            }
        } else {
            l2Pressed = false;
        }


        //r1: turn 180
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { //180
            if(!r1Pressed) {
                r1Pressed = true;

                chassis.setPose(0, 0, 0);
                chassis.turnToHeading(180, 3000);
                std::cout<<"Movement run, ending heading: "<<chassis.getPose().theta<<"\n";
            }
        } else {
            r1Pressed = false;
        }

        // //r2: does not do anything since it goes from 0 to 0
        // if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) { //0
        //     if(!yPressed) {
        //         yPressed = true;

        //         chassis.setPose(0, 0, 0);
        //         chassis.turnToHeading(0, 2000);
        //         std::cout<<"Movement run, ending heading: "<<chassis.getPose().theta<<"\n";
        //     }
        // } else {
        //     yPressed = false;
        // }
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