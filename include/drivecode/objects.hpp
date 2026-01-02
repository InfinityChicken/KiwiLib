#include "main.h"
#include "pros/adi.hpp"
#include "pros/distance.hpp"

//motor declarations
extern pros::Motor leftIntake;
extern pros::Motor rightIntake;
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
extern pros::adi::DigitalIn limitSwitch;
extern pros::Distance distanceRight;
extern pros::Distance distanceLeft;
extern pros::Distance distanceFront;

//drivetrain declarations
extern lemlib::TrackingWheel horizOdom;
extern lemlib::Drivetrain drivetrain;
extern lemlib::Chassis chassis;

//control declarations
extern pros::Controller controller;
