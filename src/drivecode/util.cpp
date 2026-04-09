#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "drivecode/util.hpp"

void motorInit() {
    topIntake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    midIntake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    bottomIntake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

//sensor settings
void sensorInit() {}

//begin all tasks
void taskInit() {
    pros::Task intakeTask(runIntake, "intake task");
    pros::Task pistonTask(runPistons, "piston task");
    pros::Task screenTask(runScreen, "screen task");
    // pros::Task controllerTask(runController, "controller task");
    // pros::Task consoleTask(runConsole, "console task");
}

//brain task
void runScreen() {
    while(true) {
        lemlib::Pose pose = chassis.getPose();

        pros::screen::print(pros::E_TEXT_MEDIUM, 1, "X: %.3f", pose.x);
        pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Y: %.3f", pose.y);
        pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Theta: %.3f", pose.theta);
        // pros::screen::print(pros::E_TEXT_MEDIUM, 4, "top wattage: %.3f", topIntake.get_power());
        // pros::screen::print(pros::E_TEXT_MEDIUM, 5, "bottom wattage: %.3f", bottomIntake.get_power());
        // pros::screen::print(pros::E_TEXT_MEDIUM, 6, "front left dist: %.3f", distFrontLeft.get_distance()/25.4);
        // pros::screen::print(pros::E_TEXT_MEDIUM, 7, "front right dist: %.3f", distFrontRight.get_distance()/25.4);
        // pros::screen::print(pros::E_TEXT_MEDIUM, 8, "back dist: %.3f", distBack.get_distance()/25.4);
        // pros::screen::print(pros::E_TEXT_MEDIUM, 9, "left dist: %.3f", distLeft.get_distance()/25.4);
        // pros::screen::print(pros::E_TEXT_MEDIUM, 10, "right dist: %.3f", distRight.get_distance()/25.4);


        // pros::screen::print(pros::E_TEXT_MEDIUM, 4, "left front: %.3f", leftMotors.get_position(0));
        // pros::screen::print(pros::E_TEXT_MEDIUM, 5, "left mid: %.3f", leftMotors.get_position(1));
        // pros::screen::print(pros::E_TEXT_MEDIUM, 6, "left back: %.3f", leftMotors.get_position(2));
        // pros::screen::print(pros::E_TEXT_MEDIUM, 7, "right front: %.3f", rightMotors.get_position(0));
        // pros::screen::print(pros::E_TEXT_MEDIUM, 8, "right mid: %.3f", rightMotors.get_position(1));
        // pros::screen::print(pros::E_TEXT_MEDIUM, 9, "right back: %.3f", rightMotors.get_position(2));
        
        pros::delay(50);
    }
}

//console task
void runConsole() {
    while(true) {
        lemlib::Pose pose = chassis.getPose();

        // std::cout<<"X: "<<std::to_string(pose.x)<<"\n";
        // std::cout<<"Y: "<<std::to_string(pose.y)<<"\n";
        // std::cout<<"Theta: "<<std::to_string(pose.theta)<<"\n";

        // std::cout<<drivetrain.leftMotors->get_voltage()<<"\n";
        // std::cout<<drivetrain.rightMotors->get_voltage()<<"\n\n";


        // std::cout<<"limit switch: "<<std::to_string(limitSwitch.get_value())<<"\n";
        // std::cout<<"front dist: "<<std::to_string(distFront.get_distance()/25.4)<<"\n";

        pros::delay(50);
    }
}

bool buttonPressed = false;
void PIDTuning(int mode, float amount) {
    if(mode == 0) { //mode 0 is angular
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            if (!buttonPressed) {
                chassis.setPose(0,0,0);
                chassis.turnToHeading(amount,5000);
            }
            buttonPressed = true;
        } else {
            buttonPressed = false;
        }
    } else if (mode == 1) { //mode 1 is lateral
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            if (!buttonPressed) {
                chassis.setPose(0,0,0);
                chassis.moveToPoint(0,amount,5000);
                chassis.turnToHeading(90, 1000);
            }
            buttonPressed = true;
        } else {
            buttonPressed = false;
        }
    }
}

bool leftPressed = false;
void distResetTesting(char xDir, char yDir) {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        if (!buttonPressed) {

            chassis.distanceReset(xDir, yDir);

        }
        buttonPressed = true;
    } else {
        buttonPressed = false;
    }
}
