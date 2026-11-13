#include "pros/misc.h"
#include "drivecode/objects.hpp"
#include "main.h"
#include "pros/optical.hpp"
#include <iostream>
#include <cmath>
#include <vector>

// // TODO: MODIFY THESE BASED ON ACTUAL ROBOT OR DISTANCE FROM CAD
// extern const int macroMaxDist;
// extern const int goalOpticRange;

extern const float maxLiftHeight;
extern const float minLiftHeight;

// extern std::vector<float> allianceGoalHeights;
// extern std::vector<float> neutralGoalHeights;

extern float liftTarget;
extern const float initialHeight;

extern int manualLiftState;
extern bool manualControl;

extern float closestGoalValue(const std::vector<float> &goaldistHeights, float distHeight);
extern void updatePidLift();
extern void updateManualLift();
extern void runPidLift();
extern void runLift();
extern void runLiftAuto(float liftTarget);