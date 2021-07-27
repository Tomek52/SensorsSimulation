#pragma once

class IObserver {
public:
    virtual ~IObserver(){};
    virtual void update(const int& message) = 0;
};