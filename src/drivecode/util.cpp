#include "drivecode/util.hpp"
#include "drivecode/objects.hpp"
#include "autonomous/autonSelector.hpp"
#include "drivecode/sensors.hpp"
#include <iostream>


//motor brake modes
void motorInit() {
    bottomRoller.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    topRoller.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
}

void sensorInit() {
    colorLeft.set_led_pwm(100);
    colorRight.set_led_pwm(100);
}

//begin all tasks
void taskInit() {
    pros::Task intakeTask(runIntake, "intake task");
    pros::Task consoleTask(runConsole, "console task");
    pros::Task pistonTask(runPistons, "piston task");
    pros::Task colorTask(colorSortRumble, "color task");
    pros::Task distanceTask(distIntakeStop, "distance task");
    pros::Task screenTask(runScreen, "screen task");
    pros::Task controllerTask(runController, "controller task");
    pros::Task autonFunctTask(autonOneBlock, "auton task");
    //pros::Task antiJamTask(antiJam, "antijam task");

}

//brain task
void runScreen() {

    while(true) {
        lemlib::Pose pose = chassis.getPose();
        pros::screen::print(pros::E_TEXT_MEDIUM, 1, "x: %.3f", pose.x);
        pros::screen::print(pros::E_TEXT_MEDIUM, 2, "y: %.3f", pose.y);
        pros::screen::print(pros::E_TEXT_MEDIUM, 3, "heading: %.3f", pose.theta);
        pros::screen::print(pros::E_TEXT_MEDIUM, 4, "top wattage: %.3f", topRoller.get_power());
        pros::screen::print(pros::E_TEXT_MEDIUM, 5, "bottom wattage: %.3f", bottomRoller.get_power());
        pros::screen::print(pros::E_TEXT_MEDIUM, 6, "Left Color: %.3f", colorLeft.get_hue());
        //pros::screen::print(pros::E_TEXT_MEDIUM, 7, "Right Color: %.3f", colorRight.get_hue());
        //pros::screen::print(pros::E_TEXT_MEDIUM, 7, "distance: %.3f", distance.get_confidence());
        //pros::screen::print(pros::E_TEXT_MEDIUM, 8, "odom rotations: %.3f", vertRotation.get_position()/36000.0);
        //pros::screen::print(pros::E_TEXT_MEDIUM, 8, "blockCount: %.3f", blockCount);


        pros::delay(50);
    }
}

//console task
void runConsole() {

    while(true) {
        lemlib::Pose pose = chassis.getPose();

        // std::cout<<"distance: "<<distance.get_distance()<<"\n";
        // std::cout<<"block count: "<<blockCount<<"\n\n";


        // std::cout<<"X: "<<std::to_string(pose.x)<<"\n";
        // std::cout<<"Y: "<<std::to_string(pose.y)<<"\n";
        // std::cout<<"Theta: "<<std::to_string(pose.theta)<<"\n";
        // std::cout<<"left color: "<<colorLeft.get_hue()<<"\n\n";

        pros::delay(500);

        
    }
}

void runController() {
    while (true) {
        if(velValue == 12000)
            controller.set_text(0, 0, "100%");
        else if(velValue == 12000 * 0.85)
            controller.set_text(0, 0, "85%");
    }
}