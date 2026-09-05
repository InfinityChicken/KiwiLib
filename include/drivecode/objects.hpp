#include "lemlib/chassis/chassis.hpp"
#include <climits>
// #include "pros/abstract_motor.hpp"
#include "pros/distance.hpp"
#include "pros/misc.h"
#include "pros/motor_group.hpp"
#include "pros/rotation.hpp"

// Buttons on the controller that control assigned subsystems
extern pros::controller_digital_e_t cbUpControl;
extern pros::controller_digital_e_t cbDownControl;
extern pros::controller_digital_e_t cascadeUpControl;
extern pros::controller_digital_e_t cascadeDownControl;

extern pros::controller_digital_e_t rollerInControl;
extern pros::controller_digital_e_t clawControl;

extern pros::controller_digital_e_t toggleControl;

extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

extern pros::Motor rollerClaw;

extern pros::MotorGroup cascadeFulls;
extern pros::Motor cascadeHalf;
extern pros::Motor chainBar;

extern pros::Distance distCascade;

extern pros::Rotation chainBarRotation;
extern pros::Rotation cascadeRotation;

extern pros::adi::DigitalOut pistonClaw;
extern pros::adi::DigitalOut pistonToggle;

extern pros::Distance distFrontLeft;
extern pros::Distance distFrontRight;
extern pros::Distance distBack;
extern pros::Distance distLeft;
extern pros::Distance distRight;

extern pros::Rotation horizRotation;
extern pros::Imu imu;

extern lemlib::TrackingWheel horizOdom;

extern lemlib::OdomSensors odomSensorsDrive;

extern lemlib::Drivetrain drivetrain;

extern lemlib::ControllerSettings lateralController;
extern lemlib::ControllerSettings angularController;

extern lemlib::DistanceSensors distSensors;

extern pros::Controller controller;

extern lemlib::Chassis chassis;

extern lemlib::PID chainBarPID;
extern lemlib::PID cascadePID;