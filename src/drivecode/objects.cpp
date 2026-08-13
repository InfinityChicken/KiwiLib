#include "lemlib/chassis/chassis.hpp"
#include <climits>
#include "objects.hpp"
#include "drivecode/util.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/distance.hpp"
#include "pros/misc.h"
#include "pros/motor_group.hpp"
#include "pros/rotation.hpp"

// TODO: CONTROLS
// controls
pros::controller_digital_e_t rollerControl = pros::E_CONTROLLER_DIGITAL_L1;
// pros::controller_digital_e_t outtakeControl = pros::E_CONTROLLER_DIGITAL_L2;
// pros::controller_digital_e_t cascadeControl = pros::E_CONTROLLER_DIGITAL_R1;
// pros::controller_digital_e_t clawRotateControl = pros::E_CONTROLLER_DIGITAL_R2;

// pros::controller_digital_e_t clawCloseControl = pros::E_CONTROLLER_DIGITAL_A;
// pros::controller_digital_e_t manualCascadeControlUp = pros::E_CONTROLLER_DIGITAL_A;
// pros::controller_digital_e_t manualCascadeControlDown = pros::E_CONTROLLER_DIGITAL_A;
// pros::controller_digital_e_t manualChainBarControlUp = pros::E_CONTROLLER_DIGITAL_A;
// pros::controller_digital_e_t manualChainBarControlDown = pros::E_CONTROLLER_DIGITAL_A;
// pros::controller_digital_e_t colorSwitchControl = pros::E_CONTROLLER_DIGITAL_A;

// TODO: Add actual drivetrain motor ports
// drivetrain
// 55w 5.5w motorstack
pros::MotorGroup leftMotors({0, 0, 0}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({-0, -0, -0}, pros::MotorGearset::blue);

// 44w
// pros::MotorGroup leftMotors({0, 0}, pros::MotorGearset::blue);
// pros::MotorGroup rightMotors({-0, -0}, pros::MotorGearset::blue);

// TODO: Add actual intake motor ports
// rollerClaw
pros::Motor rollerClaw(2, pros::MotorGearset::blue); // 5.5w

// TODO: Add actual cascade ports and rotation
// TODO: Change motor gearsets to actual used (these are for testing)
// cascade and chainbar motors
pros::Motor cascadeL (0, pros::MotorGearset::blue);
pros::Motor cascadeR (0, pros::MotorGearset::blue);
pros::Motor chainBar (0, pros::MotorGearset::green); // 5.5 w

// TODO: Add actual cascade sensor ports
// cascade rotation sensor for macro
pros::Rotation cascadeRotation(0);

// cascade distance sensor for macro
pros::Distance distCascade(0);

// TODO: Add actual claw ports
// piston claw
pros::adi::DigitalOut pistonClawRotate(0);
pros::adi::DigitalOut pistonClawClose(0);

// TODO: Add actual distance sensor ports
// distance sensors for dsr
pros::Distance distFrontLeft(0);
pros::Distance distFrontRight(0);
pros::Distance distBack(0);
pros::Distance distLeft(0);
pros::Distance distRight(0);

// TODO: Add actual vision sensor ports
// vision sensors for colour sort
pros::Vision vision(0);

// TODO: Add actual odometry ports
// odometry sensors for chassis
pros::Rotation horizRotation(0);
pros::Imu imu(0);

// TODO: Retune color if ever needed
// color signatures for vision sensor
pros::vision_signature_s_t redSig = pros::Vision::signature_from_utility(1, 
                                                                       9341, 
                                                                       12549, 
                                                                      10945, 
                                                                       -1999, 
                                                                       -745, 
                                                                      -1372, 
                                                                       2.5, 
                                                                        0);

pros::vision_signature_s_t blueSig = pros::Vision::signature_from_utility(2, 
                                                                       -4353, 
                                                                       -3559, 
                                                                      -3956, 
                                                                       6299, 
                                                                       7737, 
                                                                      7018, 
                                                                       2.5, 
                                                                        0);

pros::vision_signature_s_t yellowSig = pros::Vision::signature_from_utility(3, 
                                                                       593, 
                                                                       1227, 
                                                                      910, 
                                                                       -4851, 
                                                                       -4147, 
                                                                      -4499, 
                                                                       2.5, 
                                                                        0);

// odom objects
lemlib::TrackingWheel horizOdom(
    &horizRotation, 
    2,
    0
);

// odom sensors
lemlib::OdomSensors odomSensorsDrive(
    nullptr,
    nullptr,
    &horizOdom,
    nullptr,
    &imu
);


// drivetrain
lemlib::Drivetrain drivetrain(
    &leftMotors,
    &rightMotors,
    11.44,
    3.25,
    450,
    60 
    //radius multiplier for movetopose angular constraint. more horizontaldrift allows more aggressive drifting
);

// lateral pid controller
lemlib::ControllerSettings lateralController(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular pid controller
lemlib::ControllerSettings angularController(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// distance sensors
lemlib::DistanceSensors distSensors(distFrontLeft, -4.13, 5.27,
                                    distBack, 2.99, 4.66,
                                    distLeft, 2.04, 4.80,
                                    distRight, -3.18, 4.80);

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// chassis
lemlib::Chassis chassis(
    drivetrain,
    lateralController,
    angularController,
    odomSensorsDrive,
    distSensors
);

// cascade rotation PID
lemlib::PID cascadePID(5,
                         // proportional gain (kP)
                         0.01,
                         // integral gain (kI)
                         20,
                         // derivative gain (kD)
                         5,
                         // antiwindup
                         false
                         // sign flip reset boolean
);