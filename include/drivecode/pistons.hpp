#pragma once

#include "main.h"
#include "drivecode/objects.hpp"

// flip state
// 0 = yellow, 1 = red, 2 = blue
extern int flipState;
extern bool flipManualOverride;
extern bool flipTogglePressed;

extern char targetColor;
extern char detectedColor;

extern int clawRotateState;
extern int clawCloseState;

extern bool clawRotatePressed;
extern bool clawClosePressed;

void updateFlip();
void runFlip();
void updatePistons();
void runPistons();