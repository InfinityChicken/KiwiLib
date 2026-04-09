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
pros::MotorGroup rightMotors({1, -3, 4}, pros::MotorGearset::blue);

//sensors
pros::Imu imu(6);
pros::Rotation horizRotation(-7);
pros::Distance distRight(13);
pros::Distance distLeft(20);
pros::Distance distFrontLeft(15);
pros::Distance distFrontRight(12);
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
    11.44, //TODO: ensure accuracy
    3.25,
    450,    //TODO: horizontal drift disabled
    0 //radius multiplier for movetopose angular constraint. more horizontaldrift allows more aggressive drifting
);

//controller settings
lemlib::ControllerSettings lateralController(
    0,                           //kP
    0,                         //kI
    0,                           //kD    
    4,                   //windup range
    1,                    //small error
    50,           //small error timeout
    0,                    //large error 
    500,           //large error timeout
    0                           //slew
);

lemlib::ControllerSettings angularController(
    2.5,
    0.32,
    20,
    5,
    2,
    50,
    0,
    500,
    0
);

//distance sensors
lemlib::DistanceSensors distSensors(distFrontLeft, -4.13, 5.27,
                                    distFrontRight, 4.13, 5.27,
                                    distBack, 2.99, 4.66,
                                    distLeft, 4.80, 2.04,
                                    distRight, 4.80, -3.18);

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
