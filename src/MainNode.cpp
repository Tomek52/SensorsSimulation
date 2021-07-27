#include "MainNode.hpp"

#include <iostream>
#include <sstream>

MainNode::MainNode(CircBuffer circBuffer) : circBuffer(circBuffer) {}

void MainNode::update(const int& message) { circBuffer.writeNewData(message); }

void MainNode::printBuffer() {
    std::ostringstream out;
    out << "Buffer values: ";
    for (const auto& b : circBuffer.readData()) {
        out << b << " ";
    }
    out << "\n";
    std::cout << out.str();
}