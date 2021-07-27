#pragma once
#include <chrono>

struct RandomMeasGenerator {
    RandomMeasGenerator();
    std::chrono::seconds getRandomTime() const;
    int getRandomMeas() const;
};