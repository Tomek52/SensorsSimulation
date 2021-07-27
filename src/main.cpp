#include <iostream>
#include <memory>
#include <thread>

#include "MainNode.hpp"
#include "Sensor.hpp"

using namespace std::chrono_literals;

int main(int argc, char** argv) {
    if (argv[1] == "--help" or argv[1] == "-h" or argc != 3) {
        std::cout << "Pass two params to prgram:\n"
                  << "1. number of sensors.\n"
                  << "2. size of buffer\n";
    } else {
        int numOfSensors = std::stoi(argv[1]);
        int bufferSize = std::stoi(argv[2]);

        std::vector<Sensor> sensors(numOfSensors, Sensor());

        CircBuffer circBuffer(bufferSize);
        MainNode mainNode(circBuffer);

        auto mainNodePtr = std::make_shared<MainNode>(mainNode);

        for (auto& sensor : sensors) {
            sensor.attach(mainNodePtr);
        }

        std::vector<std::thread> sensorThreads;
        for (const auto& sensor : sensors) {
            sensorThreads.emplace_back(
                std::thread(&Sensor::startMakingMeasurements, sensor));
        }

        while (1) {
            mainNode.printBuffer();
            std::this_thread::sleep_for(2s);
        }
    }
    return 0;
}