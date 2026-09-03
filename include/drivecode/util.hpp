// #include "main.h"
// #include "pros/misc.h"
// #include "pros/misc.hpp"
// #include "pros/motors.h"
// #include "pros/rtos.hpp"
#include "drivecode/objects.hpp"
// #include "sdcard/sdmain.hpp"
#include "drivecode/claw.hpp"
#include "drivecode/cascade.hpp"
#include "drivecode/pinFromWall.hpp"
#include "drivecode/toggle.hpp"
#include "drivecode/objects.hpp"
// #include "pros/screen.h"

// initialize motors
extern void motorInit();

// sensor settings
extern void sensorInit();

// begin all tasks
extern void taskInit();

// function to print motor voltages given a line to start on
extern void printMotorVoltages(int line);

// print screen task
extern void runScreen();

// gamepad task
extern void runConsole();