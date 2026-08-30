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
// Buttons on the controller that control assigned subsystems
pros::controller_digital_e_t rollerControlIn = pros::E_CONTROLLER_DIGITAL_R1;
pros::controller_digital_e_t rollerControlOut = pros::E_CONTROLLER_DIGITAL_R2;
pros::controller_digital_e_t cascadeUpControl = pros::E_CONTROLLER_DIGITAL_L1;
pros::controller_digital_e_t cascadeDownControl = pros::E_CONTROLLER_DIGITAL_L2;

pros::controller_digital_e_t cascadeResetControl = pros::E_CONTROLLER_DIGITAL_DOWN;
pros::controller_digital_e_t cascadeSwitchControl = pros::E_CONTROLLER_DIGITAL_RIGHT;


pros::controller_digital_e_t chainBarControl = pros::E_CONTROLLER_DIGITAL_Y;
pros::controller_digital_e_t clawControl = pros::E_CONTROLLER_DIGITAL_B;

// TODO: Add actual drivetrain motor ports
// drivetrain
pros::Motor leftFront (0, pros::MotorGearset::blue);
pros::Motor leftBack (0, pros::MotorGearset::green);

pros::Motor rightFront (0, pros::MotorGearset::blue);
pros::Motor rightBack (0, pros::MotorGearset::green);

// 55w 5.5w motorstack
// pros::MotorGroup leftMotors({0, 0, 0});
// pros::MotorGroup rightMotors({0, 0, 0});

// 44w
pros::MotorGroup leftMotors({-0, 0}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({0, -0}, pros::MotorGearset::blue);

// TODO: Add actual intake motor ports
// rollerClaw
pros::Motor rollerClaw(0, pros::MotorGearset::blue); // 5.5w

// TODO: Add actual cascade ports and rotation
// TODO: Change motor gearsets to actual used (these are for testing)
// cascade and chainbar motors
pros::MotorGroup cascade({0, 0, 0, 0}, pros::MotorGearset::blue);

pros::Motor chainBar (0, pros::MotorGearset::green); // 5.5 w

// TODO: Add actual cascade sensor ports
// cascade distance sensor for macro
pros::Distance distCascade(0);
pros::Distance distCascadeEasy(0);

// chain bar/cascade rotation sensors
pros::Rotation chainBarRotation(0);
pros::Rotation cascadeRotation(0);

// TODO: Add actual claw ports
// piston claw
pros::adi::DigitalOut pistonClaw(0);
pros::adi::DigitalOut pistonFlip(0);

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
pros::vision_signature_s_t redSig = pros::Vision::signature_from_utility(0, 
                                                                       0, 
                                                                       0, 
                                                                      0, 
                                                                       0, 
                                                                       0, 
                                                                      0, 
                                                                       2.5, 
                                                                        0);

pros::vision_signature_s_t blueSig = pros::Vision::signature_from_utility(0, 
                                                                       0, 
                                                                       0, 
                                                                      0, 
                                                                       0, 
                                                                       0, 
                                                                      0, 
                                                                       2.5, 
                                                                        0);

pros::vision_signature_s_t yellowSig = pros::Vision::signature_from_utility(0, 
                                                                       0, 
                                                                       0, 
                                                                      0, 
                                                                       0, 
                                                                       0, 
                                                                      0, 
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

// chain bar pid
lemlib::PID chainBarPID(5,
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

// cascade pid
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