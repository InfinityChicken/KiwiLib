#include "main.h"
#include "objects.hpp"

// initialize state variables
extern bool cascadePressed;
extern int cascadeState;

extern bool chainBarPressed;
extern int chainBarState;

extern bool resetPressed;
extern int resetState;

// control type variable for cascade control switch
extern int controlType;

// chain bar pid target variable
extern std::int32_t chainBarPID_target;

extern void updateCascade();
extern void updateChainBar();
extern void runCascade();