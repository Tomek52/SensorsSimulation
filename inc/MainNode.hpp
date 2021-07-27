#pragma once
#include <vector>

#include "CircBuffer.hpp"
#include "IObserver.hpp"

class MainNode : public IObserver {
    CircBuffer circBuffer;

public:
    explicit MainNode(CircBuffer circBuffer);
    void update(const int& message) override;
    void printBuffer();
};