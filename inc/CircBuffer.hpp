#pragma once

#include <vector>

class CircBuffer {
    std::vector<int> buffer;
    int head = 0;

public:
    explicit CircBuffer(const int& size);
    void writeNewData(const int& data);
    std::vector<int> readData();
};