#include "main.h"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

// initialize state variables
extern bool cascadePressed;
extern int cascadeState;

extern bool chainBarPressed;
extern int chainBarState;

extern bool resetPressed;
extern int resetState;

extern bool switchPressed;
// control type variable for cascade control switch
extern int controlType;

// chain bar/cascade pid target variable
extern std::int32_t chainBarPID_target;
extern std::int32_t cascadePID_target;

extern float chainBarLoad;
extern float chainBarScore;
extern float cascadeIncrement;

extern int incrementWorks;

// chainBarEasy is a function made just to simplify code
// so we can just call this instead of doing so multiple times, 
// especially in detailed commands such as pinFromWall.cpp
void chainBarEasy(float target);

void updateCascade();
void updateChainBar();
void updateCascadeFunctions();

void runCascade();