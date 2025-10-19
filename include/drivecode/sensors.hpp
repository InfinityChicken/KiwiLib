#include "main.h"
#include "objects.hpp"
#include "intake.hpp"
#include "pistons.hpp"
#include "autonomous/autonSelector.hpp"

//extern int color;
extern int blockCount;
extern bool autonOneBlockActive;
extern bool distActive;
extern bool topFilled;


void colorSortRumble();
void distIntakeStop();
void antiJam();
void autonOneBlock();