#include "sdcard/sdtest.hpp"
#include "sdcard/sdmain.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "drivecode/objects.hpp"
#include "pros/rtos.hpp"
#include <cmath>
#include <cstdio>
#include <string>

void sdTest::run() {
    const std::string file = sdWriter::getTimestamp() + "_sdtest.csv";

    printf("[sdtest] start\n");

    // 1. initFile: create the file on the SD card
    sdWriter::initFile(file);
    sdWriter::activeFile = file;

    // 2. logRow: write a header row directly (synchronous, no streaming yet)
    sdWriter::logRow(file, {"time_ms", "counter", "cos", "x", "y"});

    // 3. writeLabel: drop a tagged marker
    sdWriter::writeLabel(file, "test start");

    // set frequency to 10 ms
    sdWriter::changeFrequency(file, 10);

    // 4. setData: register synthetic getters. Each closure produces a fresh
    //    string every time the background runWriter task calls it.
    int counter = 0;
    sdWriter::setData(file, {
        // time (milliseconds)
        []() { return std::to_string(pros::millis()); },

        // counter
        [&counter]() { return std::to_string(counter++); },

        // theta
        []() {
        return std::to_string(chassis.getPose().theta);        
        },

        // x
        []() {
        return std::to_string(chassis.getPose().x);        
        },

        // y
        []() {
        return std::to_string(chassis.getPose().y);        
        },
    });
    
}
