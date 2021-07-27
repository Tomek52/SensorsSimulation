#pragma once
#include <fstream>
#include <mutex>
#include <sstream>
#include <string>

class Logger {
    void logg(const std::string& s);
    const std::string fileName;
    std::ofstream fs;
    std::stringstream logsToDump;
    mutable std::mutex mtx;

public:
    Logger(const std::string& fileName);
    void operator()(const std::string& s);
    void dumpLogs();
};

static Logger SENSOR_LOG("SENSORS.LOG");
static Logger CLIENT_LOG("CLIENT.LOG");
