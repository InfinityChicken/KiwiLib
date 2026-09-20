#pragma once
#include "sdcard/sdmain.hpp"

class sdTest {
    public:
        // Exercises every sdWriter function against /usd/sdtest.csv.
        // Blocks for ~6 seconds, then returns. Safe to call from initialize()
        // or opcontrol() — no chassis / motor interaction.
        static void run();
};
