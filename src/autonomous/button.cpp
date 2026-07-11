#include "autonomous/button.hpp"

uint32_t VIRIDIAN = translateRGB(64, 130, 109);
uint32_t NUCLEARGREEN = translateRGB(187, 225, 0);
uint32_t DEEPPURPLE = translateRGB(54, 1, 63);
uint32_t RED = translateRGB(255, 107, 107);
uint32_t BLUE = translateRGB(107, 196, 255);

void createLabel(std::uint32_t boxColor, char * text,
                   std::int16_t x1, std::int16_t y1) {

    pros::screen::set_pen(boxColor);
    pros::screen::fill_rect(x1, y1, x1 + 200, y1 + 40);
    
    pros::screen::set_pen(pros::c::COLOR_WHITE);
    pros::screen::print(pros::E_TEXT_MEDIUM, x1 + 10, y1 + 10, text);        
}

void createLargeButton(std::uint32_t boxColor, char * text,
                   std::int16_t x1, std::int16_t y1) {

    pros::screen::set_pen(boxColor);
    pros::screen::fill_rect(x1, y1, x1 + 300, y1 + 60);
    
    pros::screen::set_pen(pros::c::COLOR_WHITE);
    pros::screen::print(pros::E_TEXT_MEDIUM, x1 + 140, y1 + 30, text);        
}

void createMediumButton(std::uint32_t boxColor, char * text,
                   std::int16_t x1, std::int16_t y1) {

    pros::screen::set_pen(boxColor);
    pros::screen::fill_rect(x1, y1, x1 + 300, y1 + 40);
    
    pros::screen::set_pen(pros::c::COLOR_WHITE);
    pros::screen::print(pros::E_TEXT_MEDIUM, x1 + 10, y1 + 10, text);        
}

void createSmallButton(std::uint32_t boxColor, char * text,
                   std::int16_t x1, std::int16_t y1) {

    pros::screen::set_pen(boxColor);
    pros::screen::fill_rect(x1, y1, x1 + 100, y1 + 40);
    
    pros::screen::set_pen(pros::c::COLOR_WHITE);
    pros::screen::print(pros::E_TEXT_MEDIUM, x1 + 10, y1 + 10, text);        
}

bool detectMediumClick(int16_t dx, int16_t dy) {
    pros::screen_touch_status_s_t status = pros::screen::touch_status();

    return status.touch_status &&
           (dx <= status.x && status.x <= dx + 300) &&
           (dy <= status.y && status.y <= dy + 40);
}

bool detectSmallClick(int16_t dx, int16_t dy) {
    pros::screen_touch_status_s_t status = pros::screen::touch_status();

    return status.touch_status &&
           (dx <= status.x && status.x <= dx + 100) &&
           (dy <= status.y && status.y <= dy + 40);
}