#include "lemlib/chassis/chassis.hpp"
#include <climits>
#include "pros/distance.hpp"
#include "pros/misc.h"
#include "pros/motor_group.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"

// placeholder names
extern pros::controller_digital_e_t CONTROL1;
extern pros::controller_digital_e_t CONTROL2;
extern pros::controller_digital_e_t CONTROL3;
extern pros::controller_digital_e_t CONTROL4;

extern pros::controller_digital_e_t CONTROL5;
extern pros::controller_digital_e_t CONTROL6;
extern pros::controller_digital_e_t CONTROL7;
extern pros::controller_digital_e_t CONTROL8;

extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

extern pros::Motor claw;

extern pros::MotorGroup lift;

extern pros::Distance distClaw;
extern pros::Distance distLiftHeight;
extern pros::Optical goalOptical;

extern pros::Rotation liftRotation;

extern pros::Motor toggle;
extern pros::Optical toggleOptical;

extern pros::Distance distFront;
extern pros::Distance distBack;
extern pros::Distance distLeft;
extern pros::Distance distRight;

extern pros::Rotation horizRotation;
extern pros::Rotation vertRotation;
extern lemlib::TrackingWheel horizOdom;
extern lemlib::TrackingWheel vertOdom;

extern pros::Imu imu;

extern lemlib::OdomSensors odomSensorsDrive;

extern lemlib::Drivetrain drivetrain;

extern lemlib::ControllerSettings lateralController;
extern lemlib::ControllerSettings angularController;

extern lemlib::DistanceSensors distSensors;

extern pros::Controller controller;

extern lemlib::Chassis chassis;

extern lemlib::PID liftPID;