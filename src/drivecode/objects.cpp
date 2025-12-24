#include "main.h"
#include <climits>
#include "objects.hpp"
#include "drivecode/util.hpp"


int ROLLER1_PORT = 0;
int ROLLER2_PORT = 0;

float kP_lat = 0;
float slew_lat = 0;
float kD_lat = 0;

float kP_ang = 0;
float kD_ang = 0;
float slew_ang = 0;

// MOTORS
pros::Motor roller1(ROLLER1_PORT, pros::MotorGearset::blue);
pros::Motor roller2(ROLLER2_PORT, pros::MotorGearset::blue);

// PISTONS
pros::adi::DigitalOut will('A');
pros::adi::DigitalOut wing('B');
pros::adi::DigitalOut longTrap('C');
pros::adi::DigitalOut midTrap('D');
pros::adi::DigitalOut odomLift('F');


//motors
pros::MotorGroup leftMotors({11, 12, -13}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({18, 20, -17}, pros::MotorGearset::blue);

//sensors
pros::Imu imu(20);
pros::Rotation horizRotation(16);
pros::Rotation vertRotation(15);

//odom objects
lemlib::TrackingWheel horizOdom(
    &horizRotation, 
    2,
    0
);

lemlib::TrackingWheel vertOdom(
    &vertRotation,
    2,
    90
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
    lemlib::Omniwheel::NEW_2,
    450,   
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

// chassis

lemlib::Chassis chassis(drivetrain, sensors, lemlib::default and custom settings here...); 
