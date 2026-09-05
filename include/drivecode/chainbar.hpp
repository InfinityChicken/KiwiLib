#include "main.h"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

//
extern int chainBarState;

// positions, tune
extern int loadPos;
extern int neutralPos;
extern int upperScorePos;
extern int lowerScorePos;

// cascade variables??
// extern float chainBarLoad;
// extern float chainBarScore;
// extern float cascadeIncrement;

// extern int incrementWorks;
// extern float cascadeHeight;

// extern float pinDimension;
// extern float stackDimension;

// extern int heightConstant;
// extern int currentLevel;
// extern int targetInches;
// chainBarEasy is a function made just to simplify code
// so we can just call this instead of doing so multiple times, 
// especially in detailed commands such as pinFromWall.cpp
void chainBarEasy(float target);

void updateCascade();
void updateChainBar();
void updateCascadeFunctions();

void runCascade();
void cascadeEasy();