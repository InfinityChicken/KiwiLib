#include "pros/misc.h"
#include "drivecode/objects.hpp"
#include "main.h"
#include "pros/optical.hpp"
#include <iostream>
#include <cmath>
#include <vector>

extern const int toggleOpticRange;
extern int toggleState;
extern int toggleSideState;
extern int opticalTeamColor_upper;
extern int opticalTeamColor_lower;

extern bool toggleSideMacro_oncePressed;
extern bool toggleSideMacro_twicePressed;

extern char teamColor; // default red
extern bool autoToggleActive;

// upper red: 0/lower red: 330
// upper blue: 170/lower blue: 230

extern void autoToggle();
extern void updateToggleSideMacro();
extern void updateManualToggle();

extern void runToggle();
extern void runToggleSideMacro();
extern void runToggleSideMacro();