#include "lemlib/chassis/chassis.hpp"
#include <climits>
#include "pros/abstract_motor.hpp"
#include "pros/distance.hpp"
#include "pros/misc.h"
#include "pros/motor_group.hpp"
#include "pros/rotation.hpp"
#include "pros/vision.hpp"

// TODO: CONTROLS
// controls
extern pros::controller_digital_e_t rollerControlIn;
extern pros::controller_digital_e_t rollerControlOut;
extern pros::controller_digital_e_t cascadeUpControl;
extern pros::controller_digital_e_t cascadeDownControl;

extern pros::controller_digital_e_t clawControl;
extern pros::controller_digital_e_t cascadeResetControl;

extern pros::controller_digital_e_t chainBarControl;
extern pros::controller_digital_e_t cascadeSwitchControl;

// TODO: Add actual drivetrain motor ports
// drivetrain
// 55w 5.5w motorstack or 44w
extern pros::Motor leftFront;
extern pros::Motor leftBack;
extern pros::Motor rightFront;
extern pros::Motor rightBack;
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

// TODO: Add actual intake motor ports
// rollerClaw
extern pros::Motor rollerClaw; // 5.5w

// TODO: Add actual cascade ports and rotation
// TODO: Change motor gearsets to actual used (these are for testing)
// cascade and chainbar motors
extern pros::MotorGroup cascade;
extern pros::Motor chainBar; // 5.5 w

// TODO: Add actual cascade sensor ports
// cascade distance sensor for macro
extern pros::Distance distCascade;

// chain bar/cascade rotation sensors
extern pros::Rotation chainBarRotation;
extern pros::Rotation cascadeRotation;

// TODO: Add actual claw ports
// piston claw
extern pros::adi::DigitalOut pistonClaw;
extern pros::adi::DigitalOut pistonFlip;

// TODO: Add actual distance sensor ports
// distance sensors for dsr
extern pros::Distance distFrontLeft;
extern pros::Distance distFrontRight;
extern pros::Distance distBack;
extern pros::Distance distLeft;
extern pros::Distance distRight;
extern pros::Distance distCascadeEasy;

// TODO: Add actual vision sensor ports
// vision sensors for colour sort
extern pros::Vision vision;

// TODO: Add actual odometry ports
// odometry sensors for chassis
extern pros::Rotation horizRotation;
extern pros::Imu imu;

// TODO: Retune color if ever needed
// color signatures for vision sensor
extern pros::vision_signature_s_t redSig;

extern pros::vision_signature_s_t blueSig;

extern pros::vision_signature_s_t yellowSig;

// odom objects
extern lemlib::TrackingWheel horizOdom;

// odom sensors
extern lemlib::OdomSensors odomSensorsDrive;

// drivetrain
extern lemlib::Drivetrain drivetrain;

// lateral pid controller
extern lemlib::ControllerSettings lateralController;

// angular pid controller
extern lemlib::ControllerSettings angularController;

// distance sensors
extern lemlib::DistanceSensors distSensors;

// controller
extern pros::Controller controller;

// chassis
extern lemlib::Chassis chassis;

// chain bar pid
extern lemlib::PID chainBarPID;

// cascade pid
extern lemlib::PID cascadePID;

// anti tip pid
extern lemlib::PID antiTipPID;