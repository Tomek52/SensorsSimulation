#include "RandomMeasGenerator.hpp"

#include <cstdlib>

RandomMeasGenerator::RandomMeasGenerator() {
    static int seed;
    srand(seed++);
}

std::chrono::seconds RandomMeasGenerator::getRandomTime() const {
    return std::chrono::seconds(rand() % 16);
}
int RandomMeasGenerator::getRandomMeas() const { return rand() % 100; }
