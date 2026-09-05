#include "main.h"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

extern int chainBarState;

// positions, tune
extern int targetPos;
extern int loadPos;
extern int neutralPos;
extern int upperScorePos;
extern int lowerScorePos;

void runChainBar();
void updateChainBar();