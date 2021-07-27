
#include "Sensor.hpp"

#include <iostream>
#include <sstream>
#include <thread>

#include "Logger.hpp"
#include "RandomMeasGenerator.hpp"

Sensor::Sensor(const int& sensorNum) : sensorNumber(sensorNum) {}

int Sensor::sendData() { return data; }
void Sensor::notify() {
    for (const auto& observer : observersVec) {
        observer->update(data);
        std::ostringstream out;
        out << "New measurement of sensor " << sensorNumber << ": " << data
            << "\n";
        // std::cout << out.str();
        SENSOR_LOG(out.str());
    }
}

void Sensor::attach(const std::shared_ptr<IObserver>& observer) {
    observersVec.emplace_back(observer);
}

void Sensor::startMakingMeasurements() {
    RandomMeasGenerator measGenerator;
    while (1) {
        data = measGenerator.getRandomMeas();
        this->notify();
        std::this_thread::sleep_for(measGenerator.getRandomTime());
    }
}
