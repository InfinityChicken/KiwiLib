#include "main.h"
#include <climits>

//gains for easy tuning
float kP = 5;
float kD = 0;
float slew = 8;

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
//pros::ADIDigitalOut colorPiston ('D');

//sensor definitions
pros::Optical colorLeft(0); //TODO: THIS IS THE ONE THAT'S WIRED // was 10
pros::Optical colorRight(0); //TODO: fix port //3
pros::Distance distance(1);
pros::Imu imu(16);
pros::Rotation horizRotation(4);
pros::Rotation vertRotation(-11);

//drivetrain definitions
lemlib::TrackingWheel horizOdom(
    &horizRotation, 
    lemlib::Omniwheel::NEW_2, 
    0
);

lemlib::TrackingWheel vertOdom(
    &vertRotation, 
    lemlib::Omniwheel::NEW_2, 
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
    kP, //6
    0,
    kD, //30
    3,
    0.2, //range to exit within
    500, //stay within range for this time
    3, 
    INT_MAX, //large disabled
    slew
);

lemlib::ControllerSettings angularController(
    0, 
    0,
    0, 
    3,
    0.5, //within .5 deg
    250,
    3,
    INT_MAX, //large disabled
    0
);

lemlib::Chassis chassis(
    drivetrain,
    lateralController,
    angularController,
    odomSensorsDrive
);

//control definitions
pros::Controller controller(pros::E_CONTROLLER_MASTER);