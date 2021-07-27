#include <atomic>
#include <iostream>
#include <memory>
#include <thread>

#include "Logger.hpp"
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

        std::vector<Sensor> sensors;
        for (int i = 0; i < numOfSensors; i++) {
            sensors.emplace_back(Sensor(i));
        }

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

        for (auto&& th : sensorThreads) {
            th.detach();
        }

        std::atomic<bool> mainFlag(true);
        std::thread mainNodeThread([&]() {
            while (1) {
                std::string in;
                std::cout << "Write 1 to dump logs\n"
                          << "Write 2 to exit\n";
                std::cin >> in;

                switch (std::stoi(in)) {
                    case 1:
                        SENSOR_LOG.dumpLogs();
                        std::cout << "Logs dumped\n";
                        break;
                    case 2:
                        mainFlag = false;
                        break;
                }
            };
        });

        mainNodeThread.detach();
        while (mainFlag) {
            mainNode.printBuffer();
            std::this_thread::sleep_for(2s);
        }
        SENSOR_LOG.dumpLogs();
    }
    return 0;
}