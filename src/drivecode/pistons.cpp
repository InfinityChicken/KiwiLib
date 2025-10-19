#include "drivecode/pistons.hpp"
#include "drivecode/intake.hpp"
#include <iostream>

int littleWillState = 0;
int descoreState = 0;
int trapdoorState = 0;
int hoodState = 0;

bool littleWillPressed = false;
bool descorePressed = false;
bool trapPressed = false;
bool hoodPressed = false;

void updatePistons() {
    //little will
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) { //b
        if(!littleWillPressed) {
            littleWillPressed = true;
            if(littleWillState == 0) {
                littleWillState = 1;
                hoodState = 0;
                trapdoorState = 0;
            } else if(littleWillState == 1){
                littleWillState = 0;
                hoodState = 1;
            }
        } 
    } else {
        littleWillPressed = false;
    }

    //descore
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) { //right
        if(!descorePressed) {
            descorePressed = true;
            if(descoreState == 0) {
                descoreState = 1;
            } else if (descoreState == 1){
                descoreState = 0;
            }
        }
    } else {
        descorePressed = false;
    }

    //pivoting hood
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { //right
        if(!hoodPressed) {
            hoodPressed = true;
            if(hoodState == 0) {
                hoodState = 1;
            } else if (hoodState == 1){
                hoodState = 0;
            }
        }
    } else {
        hoodPressed = false;
    } 

    //trapdoor
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) { //right
        if(!trapPressed) {
            trapPressed = true;
            if(trapdoorState == 0) {
                trapdoorState = 1;
            } else if (trapdoorState == 1){
                trapdoorState = 0;
            }
        }
    } else {
        trapPressed = false;
    }
}

void runPistons() {

    while(true) {
        //little will
        if(littleWillState == 0) {
            littleWill.set_value(false);
            //velValue = 12000;
        } else if(littleWillState == 1) {
            littleWill.set_value(true);
            //velValue = 12000 * 0.6;
        } 
        
        //descore
        if(descoreState == 0) {
            descore.set_value(false);
        } else if(descoreState == 1) {
            descore.set_value(true);
        }

        //hood
        if(hoodState == 0) {
            hood.set_value(false);
        } else if(hoodState == 1) {
            hood.set_value(true);
        }

        //trapdoor
        if(trapdoorState == 0) {
            trapdoor.set_value(false);
        } else if(trapdoorState == 1) {
            trapdoor.set_value(true);
        }

        pros::delay(10);
    }
}