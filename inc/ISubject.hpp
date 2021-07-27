#pragma once
#include <IObserver.hpp>
#include <memory>

class ISubject {
public:
    virtual ~ISubject(){};
    virtual void attach(const std::shared_ptr<IObserver>& observer) = 0;
    virtual void detach(const std::shared_ptr<IObserver>& observer) = 0;
    virtual void notify() = 0;
};
