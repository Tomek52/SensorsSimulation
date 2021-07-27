#pragma once
#include <memory>
#include <vector>

#include "IObserver.hpp"
#include "ISubject.hpp"

class Sensor : public ISubject {
    const int sensorNumber;
    int data = 1;
    std::vector<std::shared_ptr<IObserver>> observersVec;
    int sendData();

public:
    explicit Sensor(const int& sensorNum);
    void startMakingMeasurements();
    void attach(const std::shared_ptr<IObserver>& observer) override;
    void notify() override;
};