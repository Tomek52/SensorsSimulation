#include "Logger.hpp"

#include <iostream>

Logger::Logger(const std::string& fileName) : fileName(fileName) {}

void Logger::logg(const std::string& s) {
    std::lock_guard<std::mutex> lg(mtx);
    fs.open(fileName, std::ios_base::app);
    if (!fs) {
        throw std::runtime_error("Cannot open the output file.");
    }
    fs << s;
    fs.close();
}

void Logger::dumpLogs() {
    try {
        logg(logsToDump.str());
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

void Logger::operator()(const std::string& s) {
    std::cout << s;
    // try {
    //     logsToDump << s;
    // } catch (const std::exception& e) {
    //     std::cerr << e.what() << '\n';
    // }
}