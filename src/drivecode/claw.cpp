#include "drivecode/claw.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

// initialize state variables
int rollerState = 0;
bool rollerPressed = false;

int flipState = 0;
bool flipPressed = false;

// void updateRoller() {
//     // if roller control intake is pressed
//     if (controller.get_digital(rollerControlIn)) {
//         if (!rollerPressed) {
//             rollerState = 0;
//         }
//         // roller was just toggled just now
//         rollerPressed = true;

//     }

//     // if roller control score is pressed
//     if (controller.get_digital(rollerControlOut)) {
//         if (!rollerPressed) {
//             rollerState = 1;







//         }
//         // roller was just toggled just now
//         rollerPressed = true;

//     }

//     // roller was not toggled just now
//     else {
//         rollerPressed = false;
//     }
// }

// void updateFlip() {
//     // if flip control is pressed
//     if (controller.get_digital(clawFlipControl)) {
//         if (!flipPressed) {
//             flipState = (flipState + 1) % 2;
//         }
//         // flip was just toggled just now
//         flipPressed = true;

//     }
//     // flip was not toggled just now
//     else {
//         flipPressed = false;
//     }
// }

// void runRoller() {
//     while (true) {
//         // based on our roller state, we toggle it on or off
//         switch (rollerState) {
//             // intaking
//             case 0:
//                 rollerClaw.move_relative(100, 600);
//                 break;
//             // outtaking
//             case 1:
//                 rollerClaw.move_relative(-100, 600);
//                 break;
//         }

//         pros::delay(10);
//     }
// }

// void runFlip() {
//     while (true) {
//         // based on our flip state, we toggle it 180 or 0
//         switch (flipState) {
//             // 0
//             case 0:
//                 pistonFlip.set_value(false);
//                 break;
//             // 180
//             case 1:
//                 pistonFlip.set_value(true);
//                 break;
//         }

//         pros::delay(10);
//     }
// }