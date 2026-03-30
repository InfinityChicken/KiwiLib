#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include <climits>
#include "objects.hpp"
#include "drivecode/util.hpp"
#include "pros/distance.hpp"

//pistons
pros::adi::DigitalOut scraper('A');
pros::adi::DigitalOut wing('B');
pros::adi::DigitalOut trapdoor('C');
pros::adi::DigitalOut intakeLift('D');


//intake
pros::Motor topIntake(-19, pros::MotorGearset::blue);
pros::Motor midIntake(-15, pros::MotorGearset::blue);
pros::Motor bottomIntake(16, pros::MotorGearset::blue);

//drive motors
pros::MotorGroup leftMotors({-0, -1, 3}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({2, 4, -0}, pros::MotorGearset::blue);

//sensors
pros::Imu imu(0);
pros::Rotation horizRotation(0);
pros::Distance distRight(0);
pros::Distance distLeft(0);
pros::Distance distFrontLeft(0);
pros::Distance distFrontRight(0);
pros::Distance distBack(0);

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
    11,
    4,
    (48.0/84.0)*600.0,   
    30 //radius multiplier for movetopose angular constraint. more horizontaldrift allows more aggressive drifting
); //good 45

//controller settings
lemlib::ControllerSettings lateralController(
    10,                           //kP
    0.16,                         //kI
    64,                           //kD    
    4,                   //windup range
    1,                    //small error
    50,           //small error timeout
    0,                    //large error 
    500,           //large error timeout
    0                           //slew
);

lemlib::ControllerSettings angularController(
    3.125, 
    0.32,
    23,
    5,
    1.5,
    50,
    0,
    500,
    0
);

//distance sensors
lemlib::DistanceSensors distSensors(distFrontLeft, -5.75, 5.25, // prev 5.25, 7
                                    distFrontRight, 5.25, 4.75, // prev -5.5, 6.25
                                    distBack, -3, 6,
                                    distLeft, -1.75, 5.25,
                                    distRight, 2.5, 5.25);

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
