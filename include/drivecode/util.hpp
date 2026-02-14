#include "main.h"
#include "intake.hpp"
#include "pistons.hpp"
#include "sensors.hpp"
#include "drivecode/objects.hpp"
#include "velocity.hpp"

//begin all tasks
void taskInit();

//set motor modes/init motors
void motorInit();

//initialize sensors
void sensorInit();

//screen run function
void runScreen();

//console run function
void runConsole();

//controller screen print function
void runController();

extern bool interrupt;