#include "main.h"
#include "drivecode/objects.hpp"

//begin all tasks
void taskInit();

//set motor modes/init motors
void motorInit();

//initialize sensors
void sensorInit();

// create image from c array
void displayLogo();

// create vinish from c array
void displayVinish();

// translate rgb to uint32_t color
uint32_t translateRGB(uint8_t r, uint8_t g, uint8_t b);

// detect if button with parameters is detected
bool detectClick(int16_t x, int16_t y, int16_t dx, int16_t dy);

//screen run function
void runScreen();

//console run function
void runConsole();

//controller screen print function
void runController();