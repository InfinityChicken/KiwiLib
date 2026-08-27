#include "pros/misc.h"
#include "drivecode/objects.hpp"

// initialize state variables
extern int rollerState;
extern bool rollerPressedIn;
extern bool rollerPressedOut;

extern int flipState;
extern bool flipPressed;

extern int clawState;
extern bool clawPressed;

extern void updateRoller();
extern void updateClaw();
extern void updateFlip();

extern void runRoller();
extern void runClaw();
extern void runFlip();