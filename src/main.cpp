#include <atomic>
#include <iostream>
#include <memory>
#include <thread>

#include "Logger.hpp"
#include "MainNode.hpp"
#include "Sensor.hpp"

using namespace std::chrono_literals;

void runInterface(std::atomic<bool>& mainFlag, CircBuffer& circBuffer,
                  std::vector<std::thread>& sensorThreads,
                  std::vector<Sensor>& sensors);
void printHelp();

int main(int argc, char** argv) {
    if (argv[1] == "--help" or argv[1] == "-h" or argc != 3) {
        printHelp();
    } else {
        int numOfSensors = std::stoi(argv[1]);
        int bufferSize = std::stoi(argv[2]);

        // create sensors
        std::vector<Sensor> sensors;
        for (int i = 0; i < numOfSensors; i++) {
            sensors.emplace_back(Sensor(i));
        }

        // create main node
        CircBuffer circBuffer(bufferSize);
        MainNode mainNode(circBuffer);
        auto mainNodePtr = std::make_shared<MainNode>(mainNode);

        for (auto& sensor : sensors) {
            sensor.attach(mainNodePtr);
        }

        // run sensors in different threads
        std::vector<std::thread> sensorThreads;
        for (const auto& sensor : sensors) {
            sensorThreads.emplace_back(
                std::thread(&Sensor::startMakingMeasurements, sensor));
        }

        // human interface
        std::atomic<bool> mainFlag(true);
        runInterface(mainFlag, circBuffer, sensorThreads, sensors);

        // Log buffer to SENSOR.LOG
        while (mainFlag) {
            mainNode.printBuffer();
            std::this_thread::sleep_for(2s);
        }
        SENSOR_LOG.dumpLogs();  // not work, I did not have time to do
    }
    return 0;
}

void runInterface(std::atomic<bool>& mainFlag, CircBuffer& circBuffer,
                  std::vector<std::thread>& sensorThreads,
                  std::vector<Sensor>& sensors) {
    std::thread mainNodeThread([&]() {
        while (1) {
            std::string in;
            std::cout << "Write 1 to dump logs\n"
                      << "Write 2 to exit\n"
                      << "Write 3 to change buffer size\n"
                      << "Write 4 to add new sensor\n";
            std::cin >> in;

            switch (std::stoi(in)) {
                case 1:
                    SENSOR_LOG
                        .dumpLogs();  // not work, I did not have time to do
                    std::cout << "Logs dumped\n";
                    break;
                case 2:
                    mainFlag = false;
                    break;
                case 3:
                    std::cout << "Write new buffer size\n";
                    int size;
                    std::cin >> size;
                    circBuffer.changeBufferSize(size);
                    std::cout << "Done\n";
                    break;
                case 4:
                    std::cout << "Write sensor number\n";
                    int num;
                    std::cin >> num;
                    sensors.emplace_back(Sensor(num));
                    sensorThreads.emplace_back(&Sensor::startMakingMeasurements,
                                               sensors.back());
                    sensorThreads.back().detach();
                    std::cout << "Added new sensor\n";
                    break;
            }
        };
    });
    mainNodeThread.detach();
}

void printHelp() {
    std::cout << "Pass two params to prgram:\n"
              << "1. number of sensors.\n"
              << "2. size of buffer\n"
              << "programs create two logs file in thesame directory:\n"
              << "SENSOR.LOG - number of sensor and meas and also buffer\n"
              << "CLIENT.LOG - evry 2 seconds new log appears, new measand "
                 "buffer";
}