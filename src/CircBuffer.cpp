#include "CircBuffer.hpp"

CircBuffer::CircBuffer(const int& size) : buffer(std::vector<int>(size, 0)) {}

void CircBuffer::writeNewData(const int& data) {
    head += 1;

    if (head == buffer.size()) {
        head = 0;
    }

    buffer[head] = data;
}

std::vector<int> CircBuffer::readData() { return buffer; }
