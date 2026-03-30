#include "main.h"
#include "objects.hpp"
#include "pistons.hpp"

enum IntakeStates {STOPPED, LONG_GOAL, OUTTAKE, MID_GOAL};

extern int intakeState;

void updateIntake();
void runIntake();