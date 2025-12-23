#include "main.h"
#include <climits>


int ROLLER1_PORT = 0;
int ROLLER2_PORT = 0;

float kP_lat = 0;
float slew_lat = 0;
float kD_lat = 0;

float kP_ang = 0;
float kD_ang = 0;
float slew_ang = 0;

// MOTORS
pros::Motor roller1(ROLLER1_PORT, pros::MotorGearset::blue);
pros::Motor roller2(ROLLER2_PORT, pros::MotorGearset::blue);

// PISTONS
pros::adi::DigitalOut will ('B');
pros::adi::DigitalOut wing ('D');
pros::adi::DigitalOut longTrap ('C');
pros::adi::DigitalOut midTrap ('A');
pros::adi::DigitalOut odomLift ('F');

//control definitions
pros::Controller controller(pros::E_CONTROLLER_MASTER);



