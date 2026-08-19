#include "main.h"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "drivecode/objects.hpp"
#include "sdcard/sdmain.hpp"
#include "drivecode/claw.hpp"
#include "drivecode/cascade.hpp"

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
// void runController();