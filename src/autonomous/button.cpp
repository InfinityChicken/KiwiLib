#include "autonomous/button.hpp"

void createButton(std::uint32_t boxColor, std::uint32_t textColor,
                   char * text,
                   std::int16_t x1, std::int16_t y1) {

    pros::screen::set_pen(boxColor);
    pros::screen::fill_rect(x1, y1, x1 + 200, y1 + 40);
    pros::screen::set_pen(textColor);
    pros::screen::print(pros::E_TEXT_MEDIUM, x1 + 10, y1 + 10, text);        
}

void createAutonButton(std::uint32_t boxColor, std::uint32_t textColor,
                   char * text,
                   std::int16_t x1, std::int16_t y1) {

    pros::screen::set_pen(boxColor);
    pros::screen::fill_rect(x1, y1, x1 + 300, y1 + 40);
    pros::screen::set_pen(textColor);
    pros::screen::print(pros::E_TEXT_MEDIUM, x1 + 10, y1 + 10, text);        
}

void createColorButton(std::uint32_t boxColor, std::uint32_t textColor,
                   char * text,
                   std::int16_t x1, std::int16_t y1) {

    pros::screen::set_pen(boxColor);
    pros::screen::fill_rect(x1, y1, x1 + 100, y1 + 40);
    pros::screen::set_pen(textColor);
    pros::screen::print(pros::E_TEXT_MEDIUM, x1 + 10, y1 + 10, text);        
}

bool detectAutonClick(int16_t dx, int16_t dy) {
    pros::screen_touch_status_s_t status = pros::screen::touch_status();

    return status.touch_status &&
           (dx <= status.x && status.x <= dx + 300) &&
           (dy <= status.y && status.y <= dy + 40);
}

bool detectColorClick(int16_t dx, int16_t dy) {
    pros::screen_touch_status_s_t status = pros::screen::touch_status();

    return status.touch_status &&
           (dx <= status.x && status.x <= dx + 100) &&
           (dy <= status.y && status.y <= dy + 40);
}