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
pros::Rotation horizRotation(21);
pros::adi::DigitalIn limitSwitch('H');
pros::Distance distRight(11);
pros::Distance distLeft(16);
pros::Distance distFrontLeft(15);
pros::Distance distFrontRight(9);
pros::Distance distBack(14);

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
    8       //what speed you attempt to take around turns during move to pose
                            //, as a percentage --- this is 80% lateral around turns
);

//controller settings
lemlib::ControllerSettings lateralController(
    10,     //kP
    0.16,   //kI
    64,     //kD    
    4,      //windup range
    0.75,   //small error
    40,     //small error timeout //TODO: test this
    0,      //large error 
    500,    //large error timeout //TODO: large disabled asw
    0       //slew
);

lemlib::ControllerSettings angularController(
    3.125, 
    0.32,
    23,
    5,
    1.5, //within +- 1 deg
    40, //TODO: test this
    0, //TODO: large disabled...
    500,
    0
);



/* linear table
kP | output     kD  | output            kI      | output
1  | low        1   | low               0.01    | low
2  | low        2   | low               0.02    | low
4  | low        4   | low               0.04    | low
8  | low        8   | low               0.08    | low
16 | high       16  | low               0.16    | low
12 | good       32  | low               0.32    | high
                64  | high
                48
                


*/

/* angular table
kP | output     kD  | output            kI      | output
1  | low        1   | low               0.01    | low
2  | low        2   | low               0.02    | low
4  | high       4   | low               0.04    | low
3  | low        8   | low               0.08    | low
3.5| high       16  | low               0.16    | low
3.25| high      32  | high              0.32    |
3.125|good      24  | high
                20  | low
                22  | low
                23  | perf
                24  | perf w/ 

*/ 

//distance sensors
lemlib::DistanceSensors distSensors(distFrontLeft, -0, 0,
                                    distFrontRight, 5.25, 7,
                                    distBack, -3, 6,
                                    distLeft, -2.5, 5.25,
                                    distRight, 2.5, 5.25);

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
