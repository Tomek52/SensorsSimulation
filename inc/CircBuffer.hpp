#pragma once

#include <mutex>
#include <vector>

class CircBuffer {
    std::vector<int> buffer;
    int head = 0;
    mutable std::mutex mtx;

public:
    explicit CircBuffer(const int& size);
    ~CircBuffer() = default;
    CircBuffer(const CircBuffer& other);
    CircBuffer(CircBuffer&& other) = default;
    CircBuffer& operator=(const CircBuffer& other) = default;
    CircBuffer& operator=(CircBuffer&& other) = default;
    void writeNewData(const int data);
    std::vector<int> readData();
    void changeBufferSize(const int& size);
};