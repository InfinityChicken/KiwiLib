#include "main.h"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "drivecode/objects.hpp"
#include "sdcard/sdmain.hpp"
#include "drivecode/claw.hpp"
#include "drivecode/cascade.hpp"
#include "drivecode/pinFromWall.hpp"

extern void motorInit();

//sensor settings
extern void sensorInit();

//begin all tasks
extern void taskInit();

extern void printMotorVoltages(int line);

//brain task
extern void runScreen();

//console task
extern void runConsole();