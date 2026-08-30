#pragma once
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <cstdint>
#include "pros/rtos.hpp"
#include <iomanip>
#include <chrono>
#include <ctime>

class sdWriter {
    public:
        // Everything one log file needs to know about itself
        struct fileData {
            std::vector<std::function<std::string()>> values;
            bool isWriting = false;
            int frequency = 20;       // ms between rows
            uint32_t lastWrite = 0;   // pros::millis() of last row
        };

        // Which file synchronous logs (DSR, labels) go to. "" = logging off.
        static std::string activeFile;
        static std::vector<std::function<std::string()>> poseData;

        static void initFile(const std::string& filename);
        static void setData(const std::string& filename,
                            const std::vector<std::function<std::string()>>& values);
        static void startWrite(const std::string& filename);
        static void stopWrite(const std::string& filename);
        static void changeFrequency(const std::string& filename, int newFrequency);
        static void writeData(const std::string& filename);
        static void runWriter();
        static void logRow(const std::string& filename,
                           const std::vector<std::string>& fields);
        static void writeLabel(const std::string& filename, const std::string& label);
        static std::string getTimestamp();
        static std::string stealCompTime();

    private:
        static std::unordered_map<std::string, fileData> files;
        static pros::Mutex filesMutex;
};