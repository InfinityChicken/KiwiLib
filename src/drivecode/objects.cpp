#include "main.h"
#include <climits>

//motor definitions
pros::Motor bottomRoller(20, pros::MotorGearset::blue);
pros::Motor topRoller(12, pros::MotorGearset::blue);

pros::MotorGroup leftMotors({-15, -13, -14}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({19, 3, 17}, pros::MotorGearset::blue);

//piston definitions
pros::ADIDigitalOut littleWill ('B'); 
pros::ADIDigitalOut descore ('D');
pros::ADIDigitalOut trapdoor ('C');
pros::ADIDigitalOut hood('A');
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

lemlib::OdomSensors sensorsForUse(
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

lemlib::ControllerSettings lateralController(
    0,
    0,
    0,
    3,
    0.25, //within 1/4 inch
    250, //stay within 1/4 inch for 250 ms
    3, 
    INT_MAX, //large disabled
    0
);

lemlib::ControllerSettings angularController(
    0, 
    0,
    0, 
    3,
    0.5,
    250,
    3,
    INT_MAX, //large disabled
    0
);

lemlib::Chassis chassis(
    drivetrain,
    lateralController,
    angularController,
    sensorsForUse
);

//control definitions
pros::Controller controller(pros::E_CONTROLLER_MASTER);