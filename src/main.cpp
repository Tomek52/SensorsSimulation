#include <iostream>
#include <memory>

#include "MainNode.hpp"
#include "Sensor.hpp"

int main(int argc, char** argv) {
    int numOfSensors = std::stoi(argv[1]);
    int bufferSize = std::stoi(argv[2]);

    std::vector<Sensor> sensors(numOfSensors, Sensor());

    CircBuffer circBuffer(bufferSize);
    MainNode mainNode(circBuffer);

    auto mainNodePtr = std::make_shared<MainNode>(mainNode);

    for (auto& sensor : sensors) {
        sensor.attach(mainNodePtr);
    }

    for (auto& sensor : sensors) {
        sensor.notify();
    }
    mainNode.printBuffer();
    return 0;
}