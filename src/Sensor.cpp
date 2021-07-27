#include "Sensor.hpp"

#include <time.h>

#include <thread>

int Sensor::sendData() { return data; }
void Sensor::notify() {
    for (const auto& observer : observersVec) {
        observer->update(data);
    }
}

void Sensor::attach(const std::shared_ptr<IObserver>& observer) {
    observersVec.emplace_back(observer);
}

void Sensor::startMakingMeasurements() {
    while (1) {
        srand(time(NULL));
        int randomVariable = rand();
        data = randomVariable % 100;
        this->notify();

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(3s);
    }
}
