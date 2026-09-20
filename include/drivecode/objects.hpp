#include "main.h"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/optical.hpp"

// controls
extern pros::controller_digital_e_t intakeControl;
extern pros::controller_digital_e_t outtakeControl;
extern pros::controller_digital_e_t cascadeControl;
extern pros::controller_digital_e_t clawRotateControl;

extern pros::controller_digital_e_t clawCloseControl;
extern pros::controller_digital_e_t manualCascadeControlUp;
extern pros::controller_digital_e_t manualCascadeControlDown;
extern pros::controller_digital_e_t manualChainBarControlUp;
extern pros::controller_digital_e_t manualChainBarControlDown;
extern pros::controller_digital_e_t colorSwitchControl;

// drivetrain
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

// intake
extern pros::Motor intake; // 5.5w

// cascade and chainbar motors
extern pros::Motor cascadeL;
extern pros::Motor cascadeR;
extern pros::Motor chainBar;

// cascade rotation sensor for macro
extern pros::Rotation cascadeRotation;

// cascade distance sensor for macro
extern pros::Distance distCascade;

// piston claw
extern pros::adi::DigitalOut pistonClawRotate;
extern pros::adi::DigitalOut pistonClawClose;

// distance sensors for dsr
extern pros::Distance distFrontLeft;
extern pros::Distance distFrontRight;
extern pros::Distance distBack;
extern pros::Distance distLeft;
extern pros::Distance distRight;

// vision sensors for colour
extern pros::Vision vision;

// odometry sensors for chassis
extern pros::Rotation horizRotation;
extern pros::Imu imu;

// color signatures for vision sensor
extern pros::vision_signature_s_t yellowSig;
extern pros::vision_signature_s_t redSig;
extern pros::vision_signature_s_t blueSig;

//drivetrain declarations
extern lemlib::TrackingWheel horizOdom;
extern lemlib::Drivetrain drivetrain;
extern lemlib::Chassis chassis;

//control declarations
extern pros::Controller controller;

// cascade rotation pid
extern lemlib::PID cascadePID;