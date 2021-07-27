#include "Sensor.hpp"

int Sensor::sendData() { return data; }
void Sensor::notify() {
    for (const auto& observer : observersVec) {
        observer->update(5);
    }
}

void Sensor::attach(const std::shared_ptr<IObserver>& observer) {
    observersVec.emplace_back(observer);
}

void Sensor::detach(const std::shared_ptr<IObserver>& observer) {}