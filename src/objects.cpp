#include "main.h"
#include "objects.hpp"

float kP_lat = 0;
float kD_lat = 0;
float kI_lat = 0;
float slew_lat = 0;

float kP_ang = 0;
float kD_ang = 0;
float kI_ang = 0;
float slew_ang = 0;

//motors
pros::MotorGroup leftMotors({-15, -13, -14}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({19, 3, 17}, pros::MotorGearset::blue);

//sensors
pros::Imu imu(16);
pros::Rotation horizRotation(-4);
pros::Rotation vertRotation(-11);

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
    kP_lat,
    0,
    kD_lat,
    3,
    0.25, //range to exit within
    100, //stay within range for this time
    0, //large disabled
    0, //large disabled
    slew_lat
);

lemlib::ControllerSettings angularController(
    kP_ang, 
    0,
    kD_ang, 
    3,
    1, //within +- 1 deg
    100,
    0, //large disabled
    0, //large disabled
    slew_ang
);

//chassis
lemlib::Chassis chassis(
    drivetrain,
    lateralController,
    angularController,
    odomSensorsDrive
);

//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);