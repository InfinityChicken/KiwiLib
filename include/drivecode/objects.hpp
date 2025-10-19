#include "main.h"

//motor declarations
extern pros::Motor bottomRoller;
extern pros::Motor topRoller;

extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

//piston declarations
extern pros::ADIDigitalOut littleWill;
extern pros::ADIDigitalOut descore;
extern pros::ADIDigitalOut trapdoor;
extern pros::ADIDigitalOut hood;
//extern pros::ADIDigitalOut colorPiston;

//sensor declarations
extern pros::Optical colorLeft;
extern pros::Optical colorRight;
extern pros::Distance distance;
extern pros::Imu imu;
extern pros::Rotation horizRotation;
extern pros::Rotation vertRotation;

//drivetrain declarations
extern lemlib::TrackingWheel horizOdom;
extern lemlib::TrackingWheel vertOdom;
extern lemlib::Drivetrain drivetrain;
extern lemlib::Chassis chassis;

//control declarations
extern pros::Controller controller;
