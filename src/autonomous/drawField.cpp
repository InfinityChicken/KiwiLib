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

int xCurr, yCurr, xPrev, yPrev, theta, d;

// Embedded drawing data
const char* drawingData[] = {
    // override
    "START 120 0 0\n"
    "MOVETOPOINT 24 12\n"
    "TURNTOHEADING 90\n"
    "MOVEDISTANCE 18\n"
    "TURNTOHEADING 45\n"
    "MOVETOPOINT 36 30\n"
    "TURNTOHEADING 180\n"
    "MOVEDISTANCE 24\n"
    "TURNTOHEADING 270\n"
    "MOVETOPOINT 12 48\n"
    "TURNTOHEADING 0\n"
    "MOVEDISTANCE 30\n"
    "TURNTOHEADING 135\n"
    "MOVETOPOINT 48 24\n"
    "MOVEDISTANCE 15\n"
    "TURNTOHEADING 315\n"
    "MOVEDISTANCE 20\n",

    // dsun auto
    ""
};

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

    // draw the drivers
    pros::screen::fill_circle(160, 150, 7);
    pros::screen::fill_circle(160, 170, 7);

    // Parse embedded drawing data
    std::istringstream drawingStream(drawingData[auton]);

    // Read the data line by line
    while (std::getline(drawingStream, line)) {
        // detect the command used
        if (findCommand(line) == "START") {
            xCurr = findValue(line, 0);
            yCurr = findValue(line, 1);
            xPrev = findValue(line, 0);
            yPrev = findValue(line, 1);
            theta = findValue(line, 2);
        }
        else if (findCommand(line) == "SETPOSE") {
            xCurr = findValue(line, 0);
            yCurr = findValue(line, 1);
            theta = findValue(line, 2);
        }
        else if (findCommand(line) == "TURNTOHEADING") {
            theta = findValue(line, 0);
        }
        else if (findCommand(line) == "MOVEDISTANCE") {
            d = findValue(line, 0);
            xCurr = d * (std::acos(theta));
            yCurr = d * (std::asin(theta));
        }
        else if (findCommand(line) == "MOVETOPOINT") {
            xCurr = findValue(line, 0);
            yCurr = findValue(line, 1);
        }
        else if (findCommand(line) == "MOVETOPOSE") {
            xCurr = findValue(line, 0);
            yCurr = findValue(line, 1);
            theta = findValue(line, 2);
        }
        
        if (findCommand(line) == "START") {
            pros::screen::set_pen(autonColor == 'R' ? RED : BLUE);
            pros::screen::fill_circle(20 + xCurr, 100 + yCurr, 8);
        }

        else {
            pros::screen::set_pen(autonColor == 'R' ? pros::c::COLOR_RED : pros::c::COLOR_BLUE);
            drawLine(20 + xPrev, 100 + yPrev, 20 + xCurr, 100 + yCurr, 3);
            xPrev = xCurr;
            yPrev = yCurr;
        }
    }
}