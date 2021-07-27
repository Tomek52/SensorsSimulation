#pragma once
#include <vector>

#include "CircBuffer.hpp"
#include "IObserver.hpp"

class MainNode : public IObserver {
    CircBuffer& circBuffer;
    std::vector<int> newMeasForClients;
    std::vector<int>& newMeasForClientsRef = newMeasForClients;
    void notifyingClientsAboutNewMeas();

public:
    explicit MainNode(CircBuffer& circBuffer);
    void update(const int message) override;
    void printBuffer();
};