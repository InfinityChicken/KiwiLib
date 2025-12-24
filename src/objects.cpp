#include "main.h"
#include "objects.hpp"

//motors
pros::MotorGroup leftMotors({11, -12, -13}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({-19, 20, 17}, pros::MotorGearset::blue);

//sensors
pros::Imu imu(4);
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
    8,
    0,
    0,
    2,
    0.25, //range to exit within
    100, //stay within range for this time
    0,
    0,
    0
);

lemlib::ControllerSettings angularController(
    1.5, 
    0.4,
    7, 
    2,
    0.5, //within +- 1 deg
    100,
    3,
    500, //test
    0
);

lemlib::Chassis chassis(
    drivetrain,
    lateralController,
    angularController,
    odomSensorsDrive
);

//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);