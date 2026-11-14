#include "drivecode/objects.hpp"
#include "drivecode/util.hpp"

// TODO: CONTROLS
// Buttons on the controller that control assigned subsystems

// REFACTOR (11/13/2026) : changed CONTROL1 --> clawButton; Gourav wants the claw open/close to be the same button
pros::controller_digital_e_t clawButton = pros::E_CONTROLLER_DIGITAL_R1;

// REFACTOR (11/13/2026) : changed CONTROL2 --> clawStopSpinning; Gourav wants the claw stop spinning to be R2
pros::controller_digital_e_t clawSpinToggle = pros::E_CONTROLLER_DIGITAL_R2; 

// DR4B UP
pros::controller_digital_e_t liftUp = pros::E_CONTROLLER_DIGITAL_L1;
// DR4B DOWN
pros::controller_digital_e_t liftDown = pros::E_CONTROLLER_DIGITAL_L2;

// DR4B PID UP
pros::controller_digital_e_t CONTROL5 = pros::E_CONTROLLER_DIGITAL_LEFT;
// DR4B PID DOWN
pros::controller_digital_e_t CONTROL6 = pros::E_CONTROLLER_DIGITAL_DOWN; //pid dr4b down

// REFACTOR (11/13/2026) : changed CONTROL7 --> toggleClockwise; Gourav wants this button to spin the toggle forward
pros::controller_digital_e_t toggleClockwise = pros::E_CONTROLLER_DIGITAL_Y; //toggle forward

// REFACTOR (11/13/2026) : changed CONTROL8 --> toggleCounterClockwise; Gourav wants this button to spin the toggle backward
pros::controller_digital_e_t toggleCounterClockwise= pros::E_CONTROLLER_DIGITAL_B; //toggle backward

// RESET LIFT TO DOWN POSITION
pros::controller_digital_e_t liftFullDown = pros::E_CONTROLLER_DIGITAL_DOWN; 

// TODO: Add actual drivetrain motor ports
// 55w, 2x 11w 5.5w each side
pros::MotorGroup leftMotors({12, -13, -14}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({-20, 16, 15}, pros::MotorGearset::blue);

// TODO: Add actual claw ports
// 5.5w motor
pros::Motor claw(7, pros::MotorGearset::green);

// TODO: Add actual reverse bar ports and rotation
// 2x 11w motors
pros::MotorGroup lift({-3, 1}, pros::MotorGearset::green);//all motors for cascade are green

// toggle roller motor
pros::Motor toggle(11, pros::MotorGearset::green);

// TODO: Add actual lift sensor ports
// lift distance sensors for autolift/score macro
pros::Distance distLiftHeight(0);
// goal type optical sensor
pros::Optical goalOptical(0);

// toggle optical sensor for autotoggle
pros::Optical toggleOptical(0);

// TODO: Add actual distance sensor ports
// distance sensors for dsr
pros::Distance distFront(21);
pros::Distance distBack(8);
pros::Distance distLeft(2);
pros::Distance distRight(6);

// TODO: Add actual odometry ports
// odometry sensors for chassis
pros::Rotation horizRotation(9);
pros::Rotation vertRotation(17);
pros::Imu imu(10);

// odom objects
lemlib::TrackingWheel horizOdom(
    &horizRotation, 
    2.75,
    0
);
lemlib::TrackingWheel vertOdom(
    &vertRotation, 
    2.75,
    0
);

// odom sensors
lemlib::OdomSensors odomSensorsDrive(
    nullptr,
    nullptr,
    &horizOdom,
    nullptr,
    &imu
);

//TODO: ADD ACTUAL VALUES
// drivetrain
lemlib::Drivetrain drivetrain(
    &leftMotors,
    &rightMotors,
    10.445,
    2.75,
    450,
    99999 //we have tractions!
    //radius multiplier for movetopose angular constraint. more horizontaldrift allows more aggressive drifting
);

// lateral pid controller
lemlib::ControllerSettings lateralController(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              4, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular pid controller
lemlib::ControllerSettings angularController(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              4, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// distance sensors
lemlib::DistanceSensors distSensors(distFront, 4.054, 4.663,
                                    distBack, 5.954, 5.226,
                                    distLeft, -3.454, 5.176,
                                    distRight, -3.454, 5.176);

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// chassis
lemlib::Chassis chassis(
    drivetrain,
    lateralController,
    angularController,
    odomSensorsDrive,
    distSensors
);

// double reverse four bar
lemlib::PID liftPID(15,
                    // proportional gain (kP)
                    0.0,
                    // integral gain (kI)
                    2,
                    // derivative gain (kD)
                    5,
                    // antiwindup
                    true
                    // sign flip reset boolean
);