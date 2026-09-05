// #include "drivecode/pinfromwall.hpp"
// #include "drivecode/cascade.hpp"
// #include "pros/misc.h"
// #include "drivecode/objects.hpp"

// // initialize state variables
// int pinWallState = 0;

// static float chainBarPinWallDown = 0.00;
// static float chainBarPinWallRemove = 0.00;

// static float cascadePinWallRemove = 0.00;

// void runPinFromWall() {
//     while (true) {
//         switch (pinWallState){
//             case 0: {
//                 break;
//             }
//             case 1: {
//                 resetState = 1;
//                 rollerClaw.move_voltage(9000);
                
//                 pistonClaw.set_value(1);
//                 chainBarEasy(chainBarPinWallDown);
//                 pistonClaw.set_value(0);
//                 chainBarEasy(chainBarPinWallRemove);

//                 // cascade go up to cascadePinWallRemove
//                 // cascade reset
//                 // chain bar reset

//                 // to run it only once
//                 pinWallState = 0;
//             }
//         }

//         pros::delay(10);
//     }
// }