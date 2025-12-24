#include "main.h"
#include "pros/adi.hpp"

//motor declarations
extern pros::Motor roller1;
extern pros::Motor roller2;
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

//piston declarations
extern pros::adi::DigitalOut scraper;
extern pros::adi::DigitalOut wing;
extern pros::adi::DigitalOut trapdoor;
extern pros::adi::DigitalOut midGoal;
extern pros::adi::DigitalOut odomLift;


//sensor declarations
extern pros::Imu imu;
extern pros::Rotation horizRotation;

//drivetrain declarations
extern lemlib::TrackingWheel horizOdom;
extern lemlib::Drivetrain drivetrain;
extern lemlib::Chassis chassis;

//control declarations
extern pros::Controller controller;
