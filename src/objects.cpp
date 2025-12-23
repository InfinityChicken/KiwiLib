#include "main.h"
#include "objects.hpp"

//motors
pros::MotorGroup leftMotors({11, -12, -13}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({-19, 18, 17}, pros::MotorGearset::blue);

//sensors
pros::Imu imu(20);
pros::Rotation horizRotation(16);

//odom objects
lemlib::TrackingWheel horizOdom(
    &horizRotation, 
    2,
    0
);

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
    0,
    lemlib::Omniwheel::NEW_275,
    600,   
    8
);

//controller settings
lemlib::ControllerSettings lateralController(
    0,
    0,
    0,
    6,
    0.1, //range to exit within
    100, //stay within range for this time
    0.5,
    500,
    0
);

lemlib::ControllerSettings angularController(
    0, 
    0,
    0, 
    10,
    0.5, //within +- 1 deg
    100,
    2,
    500,
    0
);

//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);