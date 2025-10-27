#include "main.h"
#include "pros/adi.hpp"

//kP, kD, and slew for tuning easy
extern float kP_lat;
extern float kD_lat;
extern float slew_lat;

extern float kP_ang;
extern float kD_ang;
extern float slew_ang;

//motor declarations
extern pros::Motor bottomRoller;
extern pros::Motor topRoller;
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

//piston declarations
extern pros::adi::DigitalOut littleWill;
extern pros::adi::DigitalOut descore;
extern pros::adi::DigitalOut trapdoor;
extern pros::adi::DigitalOut hood;
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
