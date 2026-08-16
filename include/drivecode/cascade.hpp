#include "main.h"
#include "objects.hpp"

// initialize state variables
extern bool cascadePressed;
extern int cascadeState;

extern bool chainBarPressed;
extern int chainBarState;

extern bool resetPressed;
extern int resetState;

// chain bar pid target variable
extern std::int32_t chainBarPID_target;

extern void updateCascade();
extern void updateChainBar();
extern void runCascade();