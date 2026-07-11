#include "autonomous/autonSelector.hpp"
#include "autonomous/button.hpp"
#include "pros/colors.h"
#include <cstdint>

bool colorSelected = false;
char autonColor = ' ';
int auton = -1;

int paginate = 1;

void dialog(int autonID, std::string autonName) {
    std::string selectedStr = autonName + " Selected!";
    std::string confirmedStr = autonName + " CONFIRMED!";

    char* selectedText = const_cast<char*>(selectedStr.c_str());
    char* confirmedText = const_cast<char*>(confirmedStr.c_str());

    if (auton != autonID) {
        auton = autonID;
        createLabel(NUCLEARGREEN, selectedText, 20, 180);
        
        while (pros::screen::touch_status().touch_status) {
            pros::delay(10);
        }
    }
}

void autonSelector() {
    // clear screen
    pros::screen::set_eraser(pros::c::COLOR_BLACK);
    pros::screen::erase();

    // color red button blit
    createLargeButton(RED, const_cast<char*>("RED"), 20, 20);

    // color blue button blit
    createLargeButton(BLUE, const_cast<char*>("BLUE"), 20, 140);

    colorSelected = false;

    while(!colorSelected) {
        //button 1
        if(detectSmallClick(340, 20)) {
            if (autonColor != 'R') {
                autonColor = 'R';
                createLabel(RED, const_cast<char*>("RED Selected!"), 240, 180);
                
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
                createLabel(pros::c::COLOR_RED, const_cast<char*>("RED CONFIRMED!"), 240, 180);
            }
        }

        //button 2
        if(detectSmallClick(340, 80)) {
            if (autonColor != 'B') {
                autonColor = 'B';
                createLabel(BLUE, const_cast<char*>("BLUE Selected!"), 240, 180);
                
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
                createLabel(pros::c::COLOR_BLUE, const_cast<char*>("BLUE CONFIRMED!"), 240, 180);
            }
        }
    }

    pros::delay(500);
    while(!pros::competition::is_connected()) {
        createSmallButton(pros::c::COLOR_LIGHT_GRAY, const_cast<char*>("▲"), 240, 20);
        createSmallButton(pros::c::COLOR_LIGHT_GRAY, const_cast<char*>("▼"), 240, 80);

        switch (paginate) {
            case 1:
                // auton 1 button blit
                createMediumButton(VIRIDIAN, const_cast<char*>("override"), 20, 20);

                // auton 2 button blit
                createMediumButton(VIRIDIAN, const_cast<char*>("dsun auto"), 20, 80);
            case 2:
                // auton 3 button blit
                createMediumButton(VIRIDIAN, const_cast<char*>("auton 3"), 20, 20);

                // auton 4 button blit
                createMediumButton(VIRIDIAN, const_cast<char*>("auton 4"), 20, 80);
        }

        //button 1
        if(detectMediumClick(20, 20)) {
            switch (paginate) {
                case 1:
                    dialog(1, 1, "override");
                case 2:
                    dialog(3, 3, "auton 3");
            }
        }

        //button 2
        if(detectMediumClick(20, 80)) {
            switch (paginate) {
                case 1:
                    dialog(1, 1, "dsun auto");
                case 2:
                    dialog(1, 1, "auton 3");
            }
        }

        // paginate button 1
        if(detectSmallClick(340, 20)) {
            paginate = ((paginate - 1) % 2) + 1;
            
            while (pros::screen::touch_status().touch_status) {
                pros::delay(10);
            }
        }

        // paginate button 2
        if(detectSmallClick(340, 80)) {
            paginate = ((paginate + 1) % 2) + 1;
                
            while (pros::screen::touch_status().touch_status) {
                pros::delay(10);
            }
        }
    }
}

void chooseAuton() {
    switch (auton) {
        case 1: {
            break;
        }
        case 2: {
            break;
        }
        case 3: {
            break;
        }
        case 4: {
            break;
        }
    }
}