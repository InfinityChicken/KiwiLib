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
pros::controller_digital_e_t cbUpControl = pros::E_CONTROLLER_DIGITAL_R1;
pros::controller_digital_e_t cbDownControl = pros::E_CONTROLLER_DIGITAL_R2;
pros::controller_digital_e_t cascadeUpControl = pros::E_CONTROLLER_DIGITAL_L1;
pros::controller_digital_e_t cascadeDownControl = pros::E_CONTROLLER_DIGITAL_L2;

pros::controller_digital_e_t rollerInControl = pros::E_CONTROLLER_DIGITAL_Y;
pros::controller_digital_e_t clawControl = pros::E_CONTROLLER_DIGITAL_B;

pros::controller_digital_e_t toggleControl = pros::E_CONTROLLER_DIGITAL_DOWN;

// TODO: Add actual drivetrain motor ports
pros::MotorGroup leftMotors({-0, 0}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({0, -0}, pros::MotorGearset::blue);

// TODO: Add actual intake motor ports
pros::Motor rollerClaw(5, pros::MotorGearset::green);

// TODO: Add actual cascade ports and rotation
// cascade and chainbar motors
pros::MotorGroup cascadeFulls({0, 0}, pros::MotorGearset::blue);
pros::Motor cascadeHalf(0, pros::MotorGearset::green); // 5.5 w
pros::Motor chainBar (0, pros::MotorGearset::red);

// TODO: Add actual cascade sensor ports
// cascade distance sensor for macro
pros::Distance distCascade(0);

// chain bar/cascade rotation sensors
pros::Rotation chainBarRotation(0);
pros::Rotation cascadeRotation(0);

// TODO: Add actual claw ports
// pistons
pros::adi::DigitalOut pistonClaw('A');
pros::adi::DigitalOut pistonToggle('A');

// TODO: Add actual distance sensor ports
// distance sensors for dsr
pros::Distance distFrontLeft(0);
pros::Distance distFrontRight(0);
pros::Distance distBack(0);
pros::Distance distLeft(0);
pros::Distance distRight(0);

// TODO: Add actual odometry ports
// odometry sensors for chassis
pros::Rotation horizRotation(0);
pros::Imu imu(0);

// odom objects
lemlib::TrackingWheel horizOdom(
    &horizRotation, 
    2.75,
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

//TODO: ADD ACTUAL VALUES
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
                         true
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
                         true
                         // sign flip reset boolean
);