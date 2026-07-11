#include "autonomous/autonSelector.hpp"
#include "autonomous/button.hpp"
#include "pros/colors.h"

// indicator if the color was confirmed
bool colorSelected = false;
// auton color that is running
char autonColor = ' ';

// auton that was chosen
int auton = -1;

// pagination for auton selection
int paginate = 1;

// function that displays the confirmation state of the current autonomous
void dialog(int autonID, std::string autonName) {
    // string manipulation
    std::string selectedStr = autonName + " Selected!";
    std::string confirmedStr = autonName + " CONFIRMED!";

    // conversion to char* due to pros formatting
    char* selectedText = const_cast<char*>(selectedStr.c_str());
    char* confirmedText = const_cast<char*>(confirmedStr.c_str());

    // showing which auton is currently selected
    // only changed if your auton id was actually changed (ex. selecting a new auton)
    if (auton != autonID) {
        auton = autonID;

        // create a new dialog box
        createLabel(NUCLEARGREEN, selectedText, 20, 180);
        
        // // wait until next press, originally used for confirmation code
        // while (pros::screen::touch_status().touch_status) {
        //     pros::delay(10);
        // }
    }
}

// function that contains the auton selector process
void autonSelector() {
    // clear screen
    pros::screen::set_eraser(pros::c::COLOR_BLACK);
    pros::screen::erase();

    // create large button for red alliance
    createLargeButton(RED, const_cast<char*>("RED"), 20, 20);

    // create large button for blue alliance
    createLargeButton(BLUE, const_cast<char*>("BLUE"), 20, 140);

    // set color selected to false as we have not yet confirmed what color we're using
    colorSelected = false;

    // loops while you haven't confirmed your choice
    while(!colorSelected) {
        // TODO: Convert detectSmallClick (previously used in older version) to detectLargeClick

        // button 1 (red)
        // if a click is detected in the range that it occupies
        if(detectSmallClick(340, 20)) { // TODO
            // only changes if it hasn't been red
            if (autonColor != 'R') {
                // set the color to red temporarily
                autonColor = 'R';

                // create dialog box with red selected but not confirmed
                createLabel(RED, const_cast<char*>("RED Selected!"), 240, 180);
                
                // wait until we actually release
                while (pros::screen::touch_status().touch_status) {
                    pros::delay(10);
                }
            }
            else {
                // wait until click again
                while (!pros::screen::touch_status().touch_status) {
                    pros::delay(10);
                }
                
                // confirms that we have selected a choice
                colorSelected = true;

                // confirms that we have selected red
                autonColor = 'R';

                // create dialog box with red confirmed and locked
                createLabel(pros::c::COLOR_RED, const_cast<char*>("RED CONFIRMED!"), 240, 180);
            }
        }

        // button 2 (blue)
        // if a click is detected in the range that it occupies
        if(detectSmallClick(340, 80)) { // TODO
            // only changes if it hasn't been blue
            if (autonColor != 'B') {
                // set the color to blue temporarily
                autonColor = 'B';

                // reate dialog box with blue selected but not confirmed
                createLabel(BLUE, const_cast<char*>("BLUE Selected!"), 240, 180);
                
                // wait until we actually release
                while (pros::screen::touch_status().touch_status) {
                    pros::delay(10);
                }
            }
            else {
                // wait until click again
                while (!pros::screen::touch_status().touch_status) {
                    pros::delay(10);
                }
                
                // confirms that we have selected a choice
                colorSelected = true;

                // confirms that we have selected red
                autonColor = 'B';

                // create dialog box with blue confirmed and locked
                createLabel(pros::c::COLOR_BLUE, const_cast<char*>("BLUE CONFIRMED!"), 240, 180);
            }
        }
    }

    // loops while the match hasn't started yet so you can change it midway through your set up
    while(!pros::competition::is_connected()) {
        // create small buttons for pagination on the right side
        createSmallButton(pros::c::COLOR_LIGHT_GRAY, const_cast<char*>("▲"), 240, 20);
        createSmallButton(pros::c::COLOR_LIGHT_GRAY, const_cast<char*>("▼"), 240, 80);

        // depending on which page we are paginated at
        switch (paginate) {
            // auton 1/auton 2
            case 1:
                // create medium button for override button
                createMediumButton(VIRIDIAN, const_cast<char*>("override"), 20, 20);

                // create medium button for dsun auto button
                createMediumButton(VIRIDIAN, const_cast<char*>("dsun auto"), 20, 80);
                
            // auton 3/auton 4
            case 2:
                // create medium button for auton 3
                createMediumButton(VIRIDIAN, const_cast<char*>("auton 3"), 20, 20);

                // create medium button for auton 4
                createMediumButton(VIRIDIAN, const_cast<char*>("auton 4"), 20, 80);
        }

        // if a button is detected on the top button
        if(detectMediumClick(20, 20)) {
            // depending on which page we are paginated at:
            switch (paginate) {
                // page one will result in the button for auton 1
                case 1:
                    // create auton specific dialog that selects override
                    dialog(1, "override");

                // page two will result in the button for auton 3
                case 2:
                    // create auton specific dialog that selects auton 3
                    dialog(3, "auton 3");
            }
        }

        // if a button is detected on the bottom button
        if(detectMediumClick(20, 80)) {
            // depending on which page we are paginated at:
            switch (paginate) {
                // page two will result in the button for auton 2
                case 1:
                    // create auton specific dialog that selects dsun auto 
                    dialog(2, "dsun auto");
                    
                // page two will result in the button for auton 4
                case 2:
                    // create auton specific dialog that selects auton 4
                    dialog(4, "auton 4");
            }
        }

        // detect if the top paginate button was clicked
        if(detectSmallClick(340, 20)) {
            // set paginate to the button that was above it, loops if exceeds bounds
            paginate = ((paginate - 1) % 2) + 1;
            
            // wait for release so that you do not trigger it while your finger is down infinitely
            while (pros::screen::touch_status().touch_status) {
                pros::delay(10);
            }
        }

        // detect if the bottom paginate button was clicked
        if(detectSmallClick(340, 80)) {
            // set paginate to the button that was below it, loops if exceeds bounds
            paginate = ((paginate + 1) % 2) + 1;
                
            // wait for release so that you do not trigger it while your finger is down infinitely
            while (pros::screen::touch_status().touch_status) {
                pros::delay(10);
            }
        }
    }
}

// function to index the selected auton to the actual auton
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