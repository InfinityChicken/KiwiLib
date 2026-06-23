#include "lemlib/chassis/chassis.hpp"
#include <climits>
#include "objects.hpp"
#include "drivecode/util.hpp"
#include "pros/distance.hpp"

//pistons
pros::adi::DigitalOut scraper('B');
pros::adi::DigitalOut wing('D');
pros::adi::DigitalOut trapdoor('F');
pros::adi::DigitalOut intakeLift('C');
pros::adi::DigitalOut midDescore('E');

//intake
pros::Motor topIntake(-14, pros::MotorGearset::green);
pros::Motor midIntake(-9, pros::MotorGearset::green);
pros::Motor bottomIntake(8, pros::MotorGearset::blue);

//drive motors
pros::MotorGroup leftMotors({-10, -16, 19}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({1, -4, 3}, pros::MotorGearset::blue);

//sensors
pros::Imu imu(6);
pros::Optical color(18);
pros::Rotation horizRotation(7);
pros::Distance distRight(13);
pros::Distance distLeft(20);
pros::Distance distFront(15);
pros::Distance distBack(11);

//odom objects
lemlib::TrackingWheel horizOdom(
    &horizRotation, 
    2,
    0
);

//odom sensors
lemlib::OdomSensors odomSensorsDrive(
    nullptr,
    nullptr,
    &horizOdom,
    nullptr,
    &imu
);


//drivetrain
lemlib::Drivetrain drivetrain(
    &leftMotors,
    &rightMotors,
    11.44,
    3.25,
    450,
    60 //radius multiplier for movetopose angular constraint. more horizontaldrift allows more aggressive drifting
);

//controller settings
lemlib::ControllerSettings lateralController(
    64,                           //kP
    0,                         //kI
    50,                           //kD    
    10,                   //windup range
    1,                    //small error
    100,           //small error timeout
    3,                    //large error 
    500,           //large error timeout
    20                           //slew
);

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

//distance sensors
lemlib::DistanceSensors distSensors(distFront, -4.13, 5.27,
                                    distBack, 2.99, 4.66,
                                    distLeft, 2.04, 4.80,
                                    distRight, -3.18, 4.80);

//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// chassis
lemlib::Chassis chassis(
    drivetrain,
    lateralController,
    angularController,
    odomSensorsDrive,
    distSensors
);
