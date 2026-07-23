#include "autonomous/autonSelector.hpp"
#include "autonomous/button.hpp"
#include "autonomous/drawField.hpp"
#include "pros/colors.h"
#include "pros/misc.hpp"
#include "pros/screen.h"
#include "pros/screen.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

std::string line;

int x, y, theta;

int findValue(std::string line, int index) {
    size_t first_space = line.find(' ');
    if (first_space == std::string::npos)
        throw std::out_of_range("No values found.");

    std::stringstream ss(line.substr(first_space + 1));

    int value;
    for (int i = 0; i <= index; i++) {
        if (!(ss >> value))
            throw std::out_of_range("Index out of range.");
    }

    return value;
}

std::string findCommand(std::string line) {
    size_t firstSpace = line.find(' ');
    std::string command = line.substr(0, firstSpace);

    return command;
}

void drawField(int auton) {
    pros::screen::set_pen(pros::c::COLOR_GREY);
    pros::screen::fill_rect(20, 100, 140, 220);

    pros::screen::set_pen(pros::c::COLOR_DARK_GREY);

    std::ifstream inputFile("/drawings/" + std::to_string(auton) +".txt");

    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 6; col++) {
            if ((row + col) % 2 == 0) {
                int x1 = 20 + col * 20;
                int y1 = 100 + row * 20;

                pros::screen::fill_rect(x1, y1, x1 + 20, y1 + 20);
            }
        }
    }

    // create driver position little box
    if (autonColor == 'R') {
        // set color to red if on red side
        pros::screen::set_pen(RED);
    } else if (autonColor == 'B') {
        // set color to red if on blue side
        pros::screen::set_pen(BLUE);
    } else {
        // error handling: set color to nuclear green if invalid color, just in case
        pros::screen::set_pen(NUCLEARGREEN);
    }

    // draw the driver
    pros::screen::fill_rect(160, 165, 180, 185);
    pros::screen::fill_rect(160, 135, 180, 155);

    // Read the file line by line
    while (std::getline(inputFile, line)) {
        // detect the command used
        if (findCommand(line) == "TURNTOHEADING") {
            theta = 0;
        }
        else if (findCommand(line) == "MOVEDISTANCE") {
            break;
        }
        else if (findCommand(line) == "MOVETOPOINT") {
            break;
        }
        else if (findCommand(line) == "MOVETOPOSE") {
            break;
        }
    }

    // Close the file stream
    inputFile.close();
}