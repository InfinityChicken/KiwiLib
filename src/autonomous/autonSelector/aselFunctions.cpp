// #include "autonomous/aselFunctions.hpp"

// // definitions of color codes used in autonSelector
// uint32_t VIRIDIAN = translateRGB(64, 130, 109);
// uint32_t NUCLEARGREEN = translateRGB(187, 225, 0);
// uint32_t DEEPPURPLE = translateRGB(54, 1, 63);
// uint32_t RED = translateRGB(255, 107, 107);
// uint32_t BLUE = translateRGB(107, 196, 255);

// // function to translate rgb color into uint32_t color
// uint32_t translateRGB(uint8_t r, uint8_t g, uint8_t b){
//     return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
// }

// // function to create a dialog with given data
// void createLabel(std::uint32_t boxColor, char * text,
//                    std::int16_t x1, std::int16_t y1) {

//     pros::screen::set_pen(boxColor);
//     pros::screen::fill_rect(x1, y1, x1 + 210, y1 + 40);
    
//     pros::screen::set_pen(pros::c::COLOR_WHITE);
//     pros::screen::print(pros::E_TEXT_MEDIUM, x1 + 10, y1 + 10, text);        
// }

// // function to create a large button
// void createLargeButton(std::uint32_t boxColor, char * text,
//                    std::int16_t x1, std::int16_t y1) {

//     pros::screen::set_pen(boxColor);
//     pros::screen::fill_rect(x1, y1, x1 + 300, y1 + 60);
    
//     pros::screen::set_pen(pros::c::COLOR_WHITE);
//     pros::screen::print(pros::E_TEXT_MEDIUM, x1 + 140, y1 + 30, text);        
// }

// // function to create a medium button
// void createMediumButton(std::uint32_t boxColor, char * text,
//                    std::int16_t x1, std::int16_t y1) {

//     pros::screen::set_pen(boxColor);
//     pros::screen::fill_rect(x1, y1, x1 + 300, y1 + 40);
    
//     pros::screen::set_pen(pros::c::COLOR_WHITE);
//     pros::screen::print(pros::E_TEXT_MEDIUM, x1 + 10, y1 + 10, text);        
// }

// // function to create an auton button
// void createAutonButton(std::uint32_t boxColor, char * text, char * description1, char * description2,
//                    std::int16_t x1, std::int16_t y1) {

//     pros::screen::set_pen(boxColor);
//     pros::screen::fill_rect(x1, y1, x1 + 380, y1 + 60);
    
//     pros::screen::set_pen(pros::c::COLOR_WHITE);
//     pros::screen::print(pros::E_TEXT_MEDIUM, x1 + 10, y1 + 10, text);        
//     pros::screen::print(pros::E_TEXT_SMALL, x1 + 10, y1 + 30, description1);
//     pros::screen::print(pros::E_TEXT_SMALL, x1 + 10, y1 + 40, description2);
// }

// // function to create a small button
// void createSmallButton(std::uint32_t boxColor, char * text,
//                    std::int16_t x1, std::int16_t y1) {

//     pros::screen::set_pen(boxColor);
//     pros::screen::fill_rect(x1, y1, x1 + 50, y1 + 30);
    
//     pros::screen::set_pen(pros::c::COLOR_WHITE);
//     pros::screen::print(pros::E_TEXT_SMALL, x1 + 5, y1 + 5, text);        
// }

// // function to detect a touchscreen click of a large button
// bool detectLargeClick(int16_t dx, int16_t dy) {
//     pros::screen_touch_status_s_t status = pros::screen::touch_status();

//     return status.touch_status &&
//            (dx <= status.x && status.x <= dx + 300) &&
//            (dy <= status.y && status.y <= dy + 60);
// }

// // function to detect a touchscreen click of a medium button
// bool detectMediumClick(int16_t dx, int16_t dy) {
//     pros::screen_touch_status_s_t status = pros::screen::touch_status();

//     return status.touch_status &&
//            (dx <= status.x && status.x <= dx + 300) &&
//            (dy <= status.y && status.y <= dy + 40);
// }

// // function to detect a touchscreen click of an auton button
// bool detectAutonClick(int16_t dx, int16_t dy) {
//     pros::screen_touch_status_s_t status = pros::screen::touch_status();

//     return status.touch_status &&
//            (dx <= status.x && status.x <= dx + 380) &&
//            (dy <= status.y && status.y <= dy + 60);
// }

// // function to detect a touchscreen click of a small button
// bool detectSmallClick(int16_t dx, int16_t dy) {
//     pros::screen_touch_status_s_t status = pros::screen::touch_status();

//     return status.touch_status &&
//            (dx <= status.x && status.x <= dx + 100) &&
//            (dy <= status.y && status.y <= dy + 40);
// }

// // function to create a line that is visible unlike 1 px lines
// void drawLine(int x0, int y0, int x1, int y1, int thickness) {
//     for (int i = 0; i < thickness; i++) {
//         // Offset each line slightly perpendicular to the main line
//         pros::screen::draw_line(x0 + i, y0, x1 + i, y1);
//     }
// }