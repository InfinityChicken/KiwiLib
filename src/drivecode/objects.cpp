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
pros::adi::DigitalOut midGoal('D');
pros::adi::DigitalOut odomLift('F');


//intake
pros::Motor leftIntake(-7, pros::MotorGearset::blue);
pros::Motor rightIntake(8, pros::MotorGearset::blue);

//drive motors
pros::MotorGroup leftMotors({-18, 19, -10}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({3, -2, 1}, pros::MotorGearset::blue);

//sensors
pros::Imu imu(6);
pros::Rotation horizRotation(-15);
pros::adi::DigitalIn limitSwitch('H');
pros::Distance distRight(11);
pros::Distance distLeft(16);
pros::Distance distFront(9);

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
    lemlib::Omniwheel::NEW_4,
    (48.0/84.0)*600.0,   
    8
);

//controller settings
lemlib::ControllerSettings lateralController(
    1,
    0,
    0,
    6,
    0.01, //range to exit within
    100, //stay within range for this time
    0.5,
    500,
    0
);


lemlib::ControllerSettings angularController(
    3.5, 
    0,
    48, 
    4,
    0.01, //within +- 1 deg
    100,
    0,
    500,
    0
);

/*

kP | output     kD | output
1  | low        1  | low
2  | low        2  | low
4  | high       4  | low
3  | low        8  | low
3.5| good       16 | low
                32 | low
                64 | high
                48 | 

*/ 

//distance sensors
lemlib::DistanceSensors distSensors(distFront, 0, 0,
                                    distLeft, 0, 0,
                                    distRight, 0, 0);

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
