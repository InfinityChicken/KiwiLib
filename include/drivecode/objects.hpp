#include "lemlib/chassis/chassis.hpp"
#include <climits>
#include "pros/distance.hpp"
#include "pros/misc.h"
#include "pros/motor_group.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"

extern pros::controller_digital_e_t clawButton;
extern pros::controller_digital_e_t clawSpinToggle;

extern pros::controller_digital_e_t liftUp;
extern pros::controller_digital_e_t liftDown;

extern pros::controller_digital_e_t CONTROL5;
extern pros::controller_digital_e_t CONTROL6;

extern pros::controller_digital_e_t toggleClockwise;
extern pros::controller_digital_e_t toggleCounterClockwise;

extern pros::controller_digital_e_t driveModeToggle;

extern pros::controller_digital_e_t liftFullDown;

extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

extern pros::Motor claw;

extern pros::MotorGroup lift;

extern pros::Motor toggle;

extern pros::Distance distClaw;
extern pros::Distance distLiftHeight;
extern pros::Optical goalOptical;

extern pros::Optical toggleOptical;

extern pros::Distance distFront;
extern pros::Distance distBack;
extern pros::Distance distLeft;
extern pros::Distance distRight;

extern pros::Rotation horizRotation;
extern pros::Rotation vertRotation;
extern pros::Imu imu;


// ODOM

extern lemlib::TrackingWheel horizOdom;
extern lemlib::TrackingWheel vertOdom;

extern lemlib::OdomSensors odomSensorsDrive;

extern lemlib::Drivetrain drivetrain;

extern lemlib::ControllerSettings lateralController;

extern lemlib::ControllerSettings angularController;

extern lemlib::DistanceSensors distSensors;

extern pros::Controller controller;

extern lemlib::Chassis chassis;

extern lemlib::PID liftPID;



// make the down arrow set the PID target to all the way down and the PIDs are underconditionied, set manual var to be true, make it go down to initial height