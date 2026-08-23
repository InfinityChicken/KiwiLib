#include "main.h"
#include "objects.hpp"

// initialize state variables
extern bool rollerPressed;
int rollerState;

extern int flipState;
bool flipPressed;

extern int clawState;
bool clawPressed;

// initialize update state functions
void updateRoller();
void updateFlip();
void updateClaw();

// initialize run fuctions
void runRoller();
void runFlip();
void runClaw();