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

std::string line;

int prevX, prevY;
bool hasPrev = false;

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

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);

        int x, y;
        if (!(ss >> x >> y))
            continue;

        // 20 pixels for every 12 inches
        // x ~~inches~~ * 20 pixels / 12 ~~inches~~, inches cancels out
        // i love dimensional analysis
        if (hasPrev) {
            int screenX1 = 20 + prevX * 20 / 12;
            int screenY1 = 220 - prevY * 20 / 12;

            int screenX2 = 20 + x * 20 / 12;
            int screenY2 = 220 - y * 20 / 12;

            pros::screen::set_pen(NUCLEARGREEN);
            pros::screen::draw_line(screenX1 + 20, screenY1 + 100, screenX2 + 140, screenY2 + 220);
        }

        prevX = x;
        prevY = y;
        hasPrev = true;
    }
}