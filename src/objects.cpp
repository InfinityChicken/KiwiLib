#include "main.h"
#include "objects.hpp"

//motors
pros::MotorGroup leftMotors({-1, -2, -3}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({4, 5, 6}, pros::MotorGearset::blue);

//sensors
pros::Imu imu(20);
pros::Rotation horizRotation(-19);
pros::Rotation vertRotation(-18);

//odom objects
lemlib::TrackingWheel horizOdom(
    &horizRotation, 
    2,
    0
);

lemlib::TrackingWheel vertOdom(
    &vertRotation, 
    2, 
    0
);

lemlib::OdomSensors odomSensorsDrive(
    &vertOdom,
    nullptr,
    &horizOdom,
    nullptr,
    &imu
);


//drivetrain
lemlib::Drivetrain drivetrain(
    &leftMotors,
    &rightMotors,
    29,
    lemlib::Omniwheel::NEW_325,
    450,   
    8
);

//controller settings
lemlib::ControllerSettings lateralController(
    0,
    0,
    0,
    3,
    0.25, //range to exit within
    100, //stay within range for this time
    0, //large disabled
    0, //large disabled
    0
);

lemlib::ControllerSettings angularController(
    0, 
    0,
    0, 
    3,
    0.5, //within +- 1 deg
    100,
    0, //large disabled
    0, //large disabled
    0
);

//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);