#include "main.h"
#include "objects.hpp"

// initialize state variables
extern bool rollerPressed;
extern int rollerState;

extern int flipState;
extern bool flipPressed;

extern int clawState;
extern bool clawPressed;

// initialize update state functions
void updateRoller();
void updateFlip();
void updateClaw();

// initialize run fuctions
void runRoller();
void runFlip();
void runClaw();

void runClawRoller();