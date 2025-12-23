#include "main.h"
#include "pros/adi.hpp"

//tuning
extern float kP_lat;
extern float slew_lat;
extern float kD_lat;

extern float kP_ang;
extern float kD_ang;
extern float slew_ang;

//ports
extern int ROLLER1_PORT;
extern int ROLLER2_PORT;

//motors
extern pros::Motor roller1;
extern pros::Motor roller2;

//pistons
extern pros::adi::DigitalOut will;
extern pros::adi::DigitalOut wing;
extern pros::adi::DigitalOut longTrap;
extern pros::adi::DigitalOut midTrap;
extern pros::adi::DigitalOut odomLift;

//controller
extern pros::Controller controller;