#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "drivecode/util.hpp"
#include "drivecode/objects.hpp"
#include "sdcard/sdmain.hpp"
#include "drivecode/cascade.hpp"
#include "drivecode/intake.hpp"
#include "drivecode/pistons.hpp"
#include "drivecode/flip.hpp"
// #include "autonomous/autonSelector.hpp"

void runCascade();

void motorInit() {}

// sensor settings
void sensorInit() {
    vision.clear_led();
    vision.set_exposure(150);
    vision.set_led(4024241);
    vision.set_signature(3, &yellowSig);
    vision.set_signature(2, &blueSig);
    vision.set_signature(1, &redSig);
}

// display logo for auton selector
void displayLogo() {
    // create a variable for the c array (image)
    LV_IMAGE_DECLARE(logo);

    // declare and define the image object
    lv_obj_t* img = lv_image_create(lv_screen_active());

    // set the source data for the image 
    lv_image_set_src(img,&logo);
}

// display vinish for the jokes
void displayVinish() {
    // create a variable for the c array (image)
    LV_IMAGE_DECLARE(vinish);

    // declare and define the image object
    lv_obj_t* img = lv_image_create(lv_screen_active());

    // set the source data for the image 
    lv_image_set_src(img,&vinish);
}

//begin all tasks
void taskInit() {
    // pros::Task screenTask(runScreen, "screen task");

    // pros::Task cascadeTask(runCascade, "cascade task");
    // pros::Task flipTask(runFlip, "flip task");
    // pros::Task intakeTask(runIntake, "intake task");
    // pros::Task pistonTask(runPistons, "pistons task");

    // pros::Task scoreTask(macroScore, "score task");
}

//brain task
void runScreen() {
    while(true) {
        lemlib::Pose pose = chassis.getPose();

        // pros::screen::print(pros::E_TEXT_MEDIUM, 1, "X: %.3f", pose.x);
        // pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Y: %.3f", pose.y);
        // pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Theta: %.3f", pose.theta);

        // pros::screen::print(pros::E_TEXT_MEDIUM, 4, "Front: %.2f in", distFrontLeft.get() / 25.4);
        // pros::screen::print(pros::E_TEXT_MEDIUM, 5, "Right: %.2f in", distRight.get() / 25.4);
        // pros::screen::print(pros::E_TEXT_MEDIUM, 6, "Left:  %.2f in", distLeft.get() / 25.4);
        // pros::screen::print(pros::E_TEXT_MEDIUM, 7, "Back:  %.2f in", distBack.get() / 25.4);

        // pros::screen::print(pros::E_TEXT_MEDIUM, 8, "override=%d state=%d macro=%d", manualOverride, cascadeState, macroIsOn);

        // displayLogo();

        pros::delay(10);
    }
}

//console task
void runConsole() {
    while(true) {
        pros::delay(50);
    }
}