#include "main.h"
#include <climits>

//gains: DO NOT CHANGE WHEN CHANGED IN FUNCTIONS BRUU
float kP_lat = 8;
float kD_lat = 6;
float slew_lat = 0; //2.2

float kP_ang = 9;
float kD_ang = 60;
float slew_ang = 0;

//motor definitions
pros::Motor bottomRoller(20, pros::MotorGearset::blue);
pros::Motor topRoller(12, pros::MotorGearset::blue);

pros::MotorGroup leftMotors({-15, -13, -14}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({19, 3, 17}, pros::MotorGearset::blue);

//piston definitions
pros::adi::DigitalOut littleWill ('B'); 
pros::adi::DigitalOut descore ('D');
pros::adi::DigitalOut trapdoor ('C');
pros::adi::DigitalOut hood('A');
pros::adi::DigitalOut odomLift('F');
//pros::ADIDigitalOut colorPiston ('D');

//sensor definitions
pros::Optical colorLeft(-1); //TODO: broken
pros::Optical colorRight(10); //TODO: working
pros::Distance distance(1);
pros::Imu imu(16);
pros::Rotation horizRotation(-4);
pros::Rotation vertRotation(-11);

//drivetrain definitions
lemlib::TrackingWheel horizOdom(
    &horizRotation, 
    2,  //TODO: changed from 2.125
    0
);

lemlib::TrackingWheel vertOdom(
    &vertRotation, 
    2, 
    0
);

lemlib::OdomSensors odomSensorsDrive(
    &vertOdom, //got rid of odom
    nullptr,
    &horizOdom,
    nullptr,
    &imu
);

lemlib::Drivetrain drivetrain(
    &leftMotors,
    &rightMotors,
    29,
    lemlib::Omniwheel::NEW_325,
    450,   
    8
);

//setting definitions
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

lemlib::Chassis chassis(
    drivetrain,
    lateralController,
    angularController,
    odomSensorsDrive
);

//control definitions
pros::Controller controller(pros::E_CONTROLLER_MASTER);