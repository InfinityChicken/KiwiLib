// #include "autonomous/autonSelector.hpp"
// #include <cstdint>

// // definitions of color codes used in autonSelector
// extern uint32_t VIRIDIAN;
// extern uint32_t NUCLEARGREEN;
// extern uint32_t DEEPPURPLE;
// extern uint32_t RED;
// extern uint32_t BLUE;

// // function to translate rgb to uint32_t color
// uint32_t translateRGB(uint8_t r, uint8_t g, uint8_t b);

// // detect if button with parameters is detected
// bool detectClick(int16_t x, int16_t y, int16_t dx, int16_t dy);

// // function to create a dialog with given data
// extern void createLabel(std::uint32_t boxColor, 
//                    char * text,
//                    std::int16_t x1, std::int16_t y1);

// // function to create a large button
// extern void createLargeButton(std::uint32_t boxColor, 
//                    char * text,
//                    std::int16_t x1, std::int16_t y1);

// // function to create a medium button
// extern void createMediumButton(std::uint32_t boxColor, 
//                    char * text,
//                    std::int16_t x1, std::int16_t y1);

// // function to create an auton button
// extern void createAutonButton(std::uint32_t boxColor, char * text, char * description1, char * description2,
//                    std::int16_t x1, std::int16_t y1);

// // function to create a small button
// extern void createSmallButton(std::uint32_t boxColor, 
//                    char * text,
//                    std::int16_t x1, std::int16_t y1);

// // function to detect a touchscreen click of a large button
// extern bool detectLargeClick(int16_t dx, int16_t dy);

// // function to detect a touchscreen click of an auton button
// extern bool detectAutonClick(int16_t dx, int16_t dy);

// // function to detect a touchscreen click of a medium button
// extern bool detectMediumClick(int16_t dx, int16_t dy);

// // function to detect a touchscreen click of a small button
// extern bool detectSmallClick(int16_t dx, int16_t dy);

// // function to create a line that is visible unlike 1 px lines
// extern void drawLine(int x0, int y0, int x1, int y1, int thickness);