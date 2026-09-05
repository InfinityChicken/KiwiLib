#include "main.h"
#include "drivecode/objects.hpp"

extern int chainBarState;

inline int targetPos = 0;
inline int loadPos = 0;
inline int neutralPos = 0;
inline int upperScorePos = 0;
inline int lowerScorePos = 0;

void runChainBar();
void updateChainBar();