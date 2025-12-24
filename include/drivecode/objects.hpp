#include "main.h"
#include "pros/adi.hpp"


//ports
extern int ROLLER1_PORT;
extern int ROLLER2_PORT;

//kP, kD, and slew for tuning easy
extern float kP_lat;
extern float kD_lat;
extern float slew_lat;

extern float kP_ang;
extern float kD_ang;
extern float slew_ang;

//motor declarations
extern pros::Motor roller1;
extern pros::Motor roller2;
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

//piston declarations
extern pros::adi::DigitalOut will;
extern pros::adi::DigitalOut wing;
extern pros::adi::DigitalOut longTrap;
extern pros::adi::DigitalOut midTrap;
extern pros::adi::DigitalOut odomLift;


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
