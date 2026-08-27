#include "pros/misc.h"
#include "drivecode/objects.hpp"

// initialize state variables
extern int rollerState;
extern bool rollerPressedIn;
extern bool rollerPressedOut;

extern int clawState;
extern bool clawPressed;

extern void updateRoller();
extern void updateClaw();

extern void runRoller();
extern void runClaw();