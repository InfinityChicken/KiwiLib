// #include "autonomous/autonSelector.hpp"
// #include "pros/colors.h"
// #include "pros/screen.h"
// #include "pros/screen.hpp"
// #include "autonomous/autonomous.hpp"

// bool optionSelected = false;
// char autonColor = ' ';
// int auton = -1;


// void autonSelector() {
//     //clear screen
//     pros::screen::set_eraser(pros::c::COLOR_BLACK);
//     pros::screen::erase();

//     //button 5 printing
//     pros::screen::set_pen(pros::c::COLOR_FOREST_GREEN);
//     pros::screen::fill_rect(300, 10, 490, 50);
//     pros::screen::set_pen(pros::c::COLOR_WHITE);
//     pros::screen::print(pros::E_TEXT_MEDIUM, 310, 20, "4 Right"); //text 10 pixels below start of box
    

//     // //color buttons
//     // //red
//     // pros::screen::set_pen(pros::c::COLOR_RED);
//     // pros::screen::fill_rect(300, 10, 490, 50);
//     // pros::screen::set_pen(pros::c::COLOR_WHITE);
//     // pros::screen::print(pros::E_TEXT_MEDIUM, 310, 20, "Red"); //text 10 pixels below start of box
    
//     // //blue
//     // pros::screen::set_pen(pros::c::COLOR_BLUE);
//     // pros::screen::fill_rect(300, 70, 500, 110);
//     // pros::screen::set_pen(pros::c::COLOR_WHITE);
//     // pros::screen::print(pros::E_TEXT_MEDIUM, 310, 80, "Blue"); //text 10 pixels below start of box

//     // //cancel
//     // pros::screen::set_pen(pros::c::COLOR_FOREST_GREEN);
//     // pros::screen::fill_rect(300, 130, 500, 170);
//     // pros::screen::set_pen(pros::c::COLOR_WHITE);
//     // pros::screen::print(pros::E_TEXT_MEDIUM, 310, 140, "Cancel"); //text 10 pixels below start of box
    
    
//     //auton buttons
//     //button 1 printing
//     pros::screen::set_pen(pros::c::COLOR_FOREST_GREEN);
//     pros::screen::fill_rect(10, 10, 250, 50);
//     pros::screen::set_pen(pros::c::COLOR_WHITE);
//     pros::screen::print(pros::E_TEXT_MEDIUM, 20, 20, "4+3 Left"); //text 10 pixels below start of box

//     //button 2 printing
//     pros::screen::set_pen(pros::c::COLOR_FOREST_GREEN);
//     pros::screen::fill_rect(10, 70, 250, 110); //20 pixels below prev button
//     pros::screen::set_pen(pros::c::COLOR_WHITE);
//     pros::screen::print(pros::E_TEXT_MEDIUM, 20, 80, "7 Left");

//     //button 3 printing
//     pros::screen::set_pen(pros::c::COLOR_FOREST_GREEN);
//     pros::screen::fill_rect(10, 130, 250, 170); //20 pixels below prev button
//     pros::screen::set_pen(pros::c::COLOR_WHITE);
//     pros::screen::print(pros::E_TEXT_MEDIUM, 20, 140, "4 Left");

//     //button 4 printing
//     pros::screen::set_pen(pros::c::COLOR_FOREST_GREEN);
//     pros::screen::fill_rect(10, 190, 250, 230); //20 pixels below prev button
//     pros::screen::set_pen(pros::c::COLOR_WHITE);
//     pros::screen::print(pros::E_TEXT_MEDIUM, 20, 200, "7 Right");


//     pros::delay(500);
//     optionSelected = false;
//     while(!optionSelected) {
//         pros::screen_touch_status_s_t status = pros::screen::touch_status();
//         //std::cout<<"x: "<<status.x<<"       y: "<<status.y<<"\n";

//         //button 5 pressed
//         if(status.x>=300 && status.x<=490 && status.y>=10 && status.y<=50) {
//             optionSelected = true;
//             auton = 5;

//             pros::screen::set_pen(pros::c::COLOR_GREEN);
//             pros::screen::fill_rect(300, 10, 490, 50);
//             pros::screen::set_pen(pros::c::COLOR_WHITE);
//             pros::screen::print(pros::E_TEXT_MEDIUM, 310, 20, "4 Right Selected!");
//             pros::delay(500);
//             pros::screen::erase();
//         }

//         // //red button
//         // if(status.x>=300 && status.x<=490 && status.y>=10 && status.y<=50) {
//         //     autonColor = 'R';

//         //     //overwrite red w/ blue
//         //     pros::screen::set_pen(pros::c::COLOR_BLUE); 
//         //     pros::screen::fill_rect(300, 70, 500, 110);
//         //     pros::screen::set_pen(pros::c::COLOR_WHITE);
//         //     pros::screen::print(pros::E_TEXT_MEDIUM, 310, 80, "Blue"); //text 10 pixels below start of b
//         //     //say Red Selected
//         //     pros::screen::set_pen(pros::c::COLOR_WHITE);
//         //     pros::screen::print(pros::E_TEXT_MEDIUM, 310, 20, "Red Selected");
//         //            }

//         // //blue button
//         // if(status.x>=300 && status.x<=500 && status.y>=70 && status.y<=110) {
//         //     autonColor = 'B';

//         //     //reset red button to original            
//         //     pros::screen::set_pen(pros::c::COLOR_RED);
//         //     pros::screen::fill_rect(300, 10, 490, 50);
//         //     pros::screen::set_pen(pros::c::COLOR_WHITE);
//         //     pros::screen::print(pros::E_TEXT_MEDIUM, 310, 20, "Red");
//         //     //say Blue selected
//         //     pros::screen::set_pen(pros::c::COLOR_WHITE);
//         //     pros::screen::print(pros::E_TEXT_MEDIUM, 310, 80, "Blue Selected");
//         // }

//         // //cancel button
//         // if(status.x>=300 && status.x<=500 && status.y>=130 && status.y<=170) {
//         //     autonColor = ' ';
//         //     optionSelected = true;
//         //     pros::screen::print(pros::E_TEXT_MEDIUM, 310, 140, "Canceled!");
//         //     pros::delay(100);
//         //     pros::screen::erase();
//         // }

//         //button 1
//         if(status.x >= 10 && status.x <= 250 && status.y >= 10 && status.y <= 50) {
//             optionSelected = true;
//             auton = 1;
//             pros::screen::set_pen(pros::c::COLOR_GREEN);
//             pros::screen::fill_rect(10, 10, 250, 50);
//             pros::screen::set_pen(pros::c::COLOR_WHITE);
//             pros::screen::print(pros::E_TEXT_MEDIUM, 20, 20, "4+3 Left Selected!");
//             pros::delay(500);
//             pros::screen::erase();
//         }

//         //button 2
//         if(status.x >= 10 && status.x <= 250 && status.y >= 70 && status.y <= 110) {
//             optionSelected = true;
//             auton = 2;
//             pros::screen::set_pen(pros::c::COLOR_GREEN);
//             pros::screen::fill_rect(10, 70, 250, 110);
//             pros::screen::set_pen(pros::c::COLOR_WHITE);
//             pros::screen::print(pros::E_TEXT_MEDIUM, 20, 80, "7 Left Selected!");
//             pros::delay(500);
//             pros::screen::erase();
//         }

//         //button 3
//         if(status.x >= 10 && status.x <= 250 && status.y >= 130 && status.y <= 170) {
//             optionSelected = true;
//             auton = 3;
//             pros::screen::set_pen(pros::c::COLOR_GREEN);
//             pros::screen::fill_rect(10, 130, 250, 170);
//             pros::screen::set_pen(pros::c::COLOR_WHITE);
//             pros::screen::print(pros::E_TEXT_MEDIUM, 20, 140, "4 Left Selected!");
//             pros::delay(500);
//             pros::screen::erase();
//         }

//         //button 4
//         if(status.x >= 10 && status.x <= 250 && status.y >= 190 && status.y <= 230) {
//             optionSelected = true;
//             auton = 4;
//             pros::screen::set_pen(pros::c::COLOR_GREEN);
//             pros::screen::fill_rect(10, 190, 250, 230);
//             pros::screen::set_pen(pros::c::COLOR_WHITE);
//             pros::screen::print(pros::E_TEXT_MEDIUM, 20, 200, "7 Right Selected!");
//             pros::delay(500);
//             pros::screen::erase();
//         }
//     }

//     pros::screen::print(pros::E_TEXT_MEDIUM, 0, "Color: %c      Auton: %d", autonColor, auton);
// }

// void chooseAuton() {
//     switch(auton) {
// 			case 1: {
// 				leftSplitPush();
// 				break;
// 			}
// 			case 2: {
// 				sevenBlockPushLeft();
// 				break;
// 			}
// 			case 3: {
// 				fourBlockPushLeft();
// 				break;
// 			}
//             case 4: {
//                 sevenBlockPushRight();
//                 break;
//             }
//             case 5: {
//                 fourBlockPushRight();
//                 break;
//             }
//             case -1: {
//                 leftSplitPush();
// 				break;
//             }
//         }
//     // if(autonColor == 'R') {
// 	// 	switch(auton) {
// 	// 		case 1: {
// 	// 			longGoalLeft();
// 	// 			break;
// 	// 		}
// 	// 		case 2: {
// 	// 			longGoalRight();
// 	// 			break;
// 	// 		}
// 	// 		case 3: {
// 	// 			sawp();
// 	// 			break;
// 	// 		}
// 	// 	}
// 	// } else if(autonColor == 'B') {
// 	// 	switch(auton) {
// 	// 		case 1: {
// 	// 			longGoalLeft();
// 	// 			break;
// 	// 		}
// 	// 		case 2: {
// 	// 			longGoalRight();
// 	// 			break;
// 	// 		}
// 	// 		case 3: {
// 	// 			sawp();
// 	// 			break;
// 	// 		}
// 	// 	}
// 	// } else {
// 	// 	std::cout<<"testing\n";
// 	// 	//intakeState = 1;
// 	// 	//outtakeUntilCorrect('R', 100000);
// 	// 	//longGoalRight();
// 	// 	//skills();
// 	// }
// }