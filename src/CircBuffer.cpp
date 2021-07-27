#include "CircBuffer.hpp"

CircBuffer::CircBuffer(const int& size) : buffer(std::vector<int>(size, 0)) {}
CircBuffer::CircBuffer(const CircBuffer& other) {
    buffer = other.buffer;
    head = other.head;
}

void CircBuffer::writeNewData(const int data) {
    std::lock_guard<std::mutex> lock(mtx);
    head += 1;
    if (head == buffer.size()) {
        head = 0;
    }
    buffer[head] = data;
}

std::vector<int> CircBuffer::readData() { return buffer; }

void CircBuffer::changeBufferSize(const int& size) { buffer.resize(size); }
