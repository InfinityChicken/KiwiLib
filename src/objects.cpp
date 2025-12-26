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

lemlib::OdomSensors odometrySensors(
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
    0 //horizontal drift doesn't matter isn't used anywhere
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
    2, 
    0.48,
    13, 
    10,
    0.5, //within +- 1 deg
    100,
    0,
    500, //test
    0
);

lemlib::Chassis chassis(
    drivetrain,
    lateralController,
    angularController,
    odometrySensors
);

//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);