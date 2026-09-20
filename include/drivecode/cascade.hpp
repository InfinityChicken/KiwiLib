#include "main.h"
#include "drivecode/objects.hpp"

// cascade state variable
// cascadeState = 0: sensing is OFF
// cascadeState = 1: sensing is ON
extern int cascadeState;

// boolean to track if cascade was just pressed now
// since we haven't pressed it earlier, it's off at the start
extern bool cascadePressed;

// boolean to track if the manual override is overriding
// get it? override?
extern bool manualOverride;

// boolean to track if macro is running
extern bool macroIsOn;

// chain bar stall variables
extern int currentDraw;
extern double currentVelocity;

void updateCascade();
void runCascade();
void runManual();
void macroScore();