#include "autonomous/autonSelector.hpp"
#include "autonomous/button.hpp"
#include "pros/colors.h"
#include "pros/misc.hpp"
#include "pros/screen.h"
#include "pros/screen.hpp"

// indicator if the color was confirmed
bool colorSelected = false;
// auton color that is running
char autonColor = ' ';

// auton that was chosen
int auton = -1;

// pagination for auton selection
int paginate = 0;

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
    pros::screen::print(pros::E_TEXT_MEDIUM, 1, "X: %.3f", pros::competition::is_disabled());

    while (pros::competition::is_disabled()) {
        // clear screen
        pros::screen::set_eraser(pros::c::COLOR_BLACK);
        pros::screen::erase();

        // create large button for red alliance
        createLargeButton(RED, const_cast<char*>("RED"), 20, 20);

        // create large button for blue alliance
        createLargeButton(BLUE, const_cast<char*>("BLUE"), 20, 100);

        // set color selected to false as we have not yet confirmed what color we're using
        colorSelected = false;

        // loops while you haven't confirmed your choice
        while(pros::competition::is_disabled() && !colorSelected) {
            // TODO: Convert detectSmallClick (previously used in older version) to detectLargeClick

            // button 1 (red)
            // if a click is detected in the range that it occupies
            if(detectLargeClick(20, 20)) {
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
            if(detectLargeClick(20, 100)) {
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
                    createLabel(pros::c::COLOR_BLUE, const_cast<char*>("BLUE CONFIRMED!"), 260, 180);
                }
            }
        }

        // clear screen
        pros::screen::set_eraser(pros::c::COLOR_BLACK);
        pros::screen::erase();

        // loops while the match hasn't started yet so you can change it midway through your set up
        while(pros::competition::is_disabled()) {
            if (autonColor == 'R') {
                createLabel(pros::c::COLOR_RED, const_cast<char*>("RED CONFIRMED!"), 260, 180);
            }

            else {
                createLabel(pros::c::COLOR_BLUE, const_cast<char*>("BLUE CONFIRMED!"), 260, 180);
            }

            
            // create small buttons for pagination on the right side
            createSmallButton(pros::c::COLOR_LIGHT_GRAY, const_cast<char*>("^"), 420, 20);
            createSmallButton(pros::c::COLOR_LIGHT_GRAY, const_cast<char*>("v"), 420, 120);

            // depending on which page we are paginated at
            switch (paginate) {
                // auton 1/auton 2
                case 0:
                    // create medium button for override button
                    createAutonButton(VIRIDIAN, 
                        const_cast<char*>("override"), 
                        const_cast<char*>("mooncer's auton"), 
                        const_cast<char*>("our first auton on the worlds bot"), 
                        20, 20);

                    // create medium button for dsun auto button
                    createAutonButton(VIRIDIAN, 
                        const_cast<char*>("dsun auto"), 
                        const_cast<char*>("dsun's bad auton"),  
                        const_cast<char*>("really do not trust a psychopath"),  
                        20, 100);
                    break;
                // auton 3/auton 4
                case 1:
                    // create medium button for auton 3
                    createAutonButton(VIRIDIAN, 
                        const_cast<char*>("auton 3"), 
                        const_cast<char*>("i have the urge to put norrel's face"), 
                        const_cast<char*>("here, hello norrel"), 
                        20, 20);

                    // create medium button for auton 4
                    createAutonButton(VIRIDIAN, 
                        const_cast<char*>("auton 4"), 
                        const_cast<char*>("hi vinish"), 
                        const_cast<char*>("vinish is a cool guy"), 
                        20, 100);
                    break;
            }

            // if a button is detected on the top button
            if(detectAutonClick(20, 20)) {
                // depending on which page we are paginated at:
                switch (paginate) {
                    // page one will result in the button for auton 1
                    case 0:
                        // create auton specific dialog that selects override
                        dialog(1, "override");
                        break;

                    // page two will result in the button for auton 3
                    case 1:
                        // create auton specific dialog that selects auton 3
                        dialog(3, "auton 3");
                        break;
                }
            }

            // if a button is detected on the bottom button
            if(detectAutonClick(20, 100)) {
                // depending on which page we are paginated at:
                switch (paginate) {
                    // page two will result in the button for auton 2
                    case 0:
                        // create auton specific dialog that selects dsun auto 
                        dialog(2, "dsun auto");
                        break;
                    
                    // page two will result in the button for auton 4
                    case 1:
                        // create auton specific dialog that selects auton 4
                        dialog(4, "auton 4");
                        break;
                }
            }

            // detect if the top paginate button was clicked
            if(detectSmallClick(420, 20)) {
                // set paginate to the button that was above it, loops if exceeds bounds
                paginate = abs(((paginate - 1) % 2));
                
                // wait for release so that you do not trigger it while your finger is down infinitely
                while (pros::screen::touch_status().touch_status) {
                    pros::delay(10);
                }
            }

            // detect if the bottom paginate button was clicked
            if(detectSmallClick(420, 120)) {
                // set paginate to the button that was below it, loops if exceeds bounds
                paginate = abs(((paginate + 1) % 2));
                    
                // wait for release so that you do not trigger it while your finger is down infinitely
                while (pros::screen::touch_status().touch_status) {
                    pros::delay(10);
                }
            }

            pros::delay(10);
        }
    }

    // clear screen
    pros::screen::set_eraser(pros::c::COLOR_BLACK);
    pros::screen::erase();
}

// function to index the selected auton to the actual auton
void runAuton() {
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