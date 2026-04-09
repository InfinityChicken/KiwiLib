#include "main.h"
#include "objects.hpp"
#include "pistons.hpp"

// enum IntakeStates {STOPPED, LONG_GOAL, OUTTAKE, MID_GOAL, BOTTOM_ONLY};

extern int intakeState;
extern bool lowSpeedMode;
void updateIntake();
void runIntake();