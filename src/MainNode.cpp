#include "MainNode.hpp"

#include <iostream>
#include <sstream>
#include <thread>

#include "Logger.hpp"

using namespace std::chrono_literals;

MainNode::MainNode(CircBuffer& circBuffer) : circBuffer(circBuffer) {
    notifyingClientsAboutNewMeas();
}

void MainNode::update(const int message) {
    newMeasForClientsRef.emplace_back(message);
    circBuffer.writeNewData(message);
}

void MainNode::printBuffer() {
    std::ostringstream out;
    out << "Buffer values: ";
    for (const auto& b : circBuffer.readData()) {
        out << b << " ";
    }
    out << "\n";
    // std::cout << out.str();
    SENSOR_LOG(out.str());
}
void MainNode::notifyingClientsAboutNewMeas() {
    std::thread clientThread([&]() {
        static int counter;
        while (1) {
            counter++;
            std::this_thread::sleep_for(2s);
            std::ostringstream out;
            const auto newMeas = newMeasForClientsRef;
            newMeasForClientsRef.clear();
            const auto buffer = circBuffer.readData();
            out << counter << " New meas: ";
            for (const auto& meas : newMeas) {
                out << meas << " ";
            }
            out << "Buffer: ";
            for (const auto& meas : buffer) {
                out << meas << " ";
            }
            out << "\n";
            CLIENT_LOG(out.str());
        }
    });
    clientThread.detach();
}
