#include "autonomous/autonomous.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "drivecode/claw.hpp"
#include "drivecode/cascade.hpp"

// TODO: Removed all the blindcoded auton code
void drc() {
    // chassis reset
    chassis.setPose(0, 0, 0);
}