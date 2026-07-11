#include "autonomous/autonSelector.hpp"
#include "autonomous/button.hpp"
#include "pros/colors.h"
#include <cstdint>

bool optionSelected = false;
bool colorSelected = false;
char autonColor = ' ';
int auton = -1;

uint32_t VIRIDIAN = translateRGB(64, 130, 109);
uint32_t NUCLEARGREEN = translateRGB(187, 225, 0);
uint32_t DEEPPURPLE = translateRGB(54, 1, 63);
uint32_t RED = translateRGB(255, 107, 107);
uint32_t BLUE = translateRGB(107, 196, 255);

void autonSelector() {
    // clear screen
    pros::screen::set_eraser(pros::c::COLOR_BLACK);
    pros::screen::erase();

    // auton 1 button blit
    createAutonButton(VIRIDIAN, pros::c::COLOR_WHITE, "override", 20, 20);

    // auton 2 button blit
    createAutonButton(VIRIDIAN, pros::c::COLOR_WHITE, "dsun auto", 20, 80);


    // color red button blit
    createColorButton(RED, pros::c::COLOR_WHITE, "RED", 340, 20);

    // color blue button blit
    createColorButton(BLUE, pros::c::COLOR_WHITE, "BLUE", 340, 80);

    pros::delay(500);
    optionSelected = false;
    while(!optionSelected) {
        //button 1
        if(detectAutonClick(20, 20)) {
            if (auton != 1) {
                auton = 1;
                createButton(NUCLEARGREEN, pros::c::COLOR_WHITE, "override selected", 20, 180);
                
                while (pros::screen::touch_status().touch_status) {
                    pros::delay(10);
                }
            }
            else {
                while (!pros::screen::touch_status().touch_status) {
                    pros::delay(10);
                }
                
                optionSelected = true;
                auton = 1;
                createButton(DEEPPURPLE, pros::c::COLOR_WHITE, "override CONFIRMED", 20, 180);
            }
        }

        //button 2
        if(detectAutonClick(20, 80)) {
            if (auton != 2) {
                auton = 2;
                createButton(NUCLEARGREEN, pros::c::COLOR_WHITE, "dsun auto selected", 20, 180);
                
                while (pros::screen::touch_status().touch_status) {
                    pros::delay(10);
                }
            }
            else {
                while (!pros::screen::touch_status().touch_status) {
                    pros::delay(10);
                }
                
                optionSelected = true;
                auton = 2;
                createButton(DEEPPURPLE, pros::c::COLOR_WHITE, "dsun auto CONFIRMED", 20, 180);
            }
        }
    }


    
    colorSelected = false;
    while(!colorSelected) {
        //button 1
        if(detectColorClick(340, 20)) {
            if (autonColor != 'R') {
                autonColor = 'R';
                createButton(RED, pros::c::COLOR_WHITE, "RED Selected", 240, 180);
                
                while (pros::screen::touch_status().touch_status) {
                    pros::delay(10);
                }
            }
            else {
                while (!pros::screen::touch_status().touch_status) {
                    pros::delay(10);
                }
                
                colorSelected = true;
                autonColor = 'R';
                createButton(pros::c::COLOR_RED, pros::c::COLOR_WHITE, "RED CONFIRMED", 240, 180);
            }
        }

        //button 2
        if(detectColorClick(340, 80)) {
            if (autonColor != 'B') {
                autonColor = 'B';
                createButton(BLUE, pros::c::COLOR_WHITE, "BLUE SELECTED", 240, 180);
                
                while (pros::screen::touch_status().touch_status) {
                    pros::delay(10);
                }
            }
            else {
                while (!pros::screen::touch_status().touch_status) {
                    pros::delay(10);
                }
                
                colorSelected = true;
                autonColor = 'B';
                createButton(pros::c::COLOR_BLUE, pros::c::COLOR_WHITE, "BLUE CONFIRMED", 240, 180);
            }
        }
    }
}

void chooseAuton() {
    switch(auton) {
			case 1: {
				override();
				break;
			}
			case 2: {
				dsunauto();
				break;
			}
        }
}