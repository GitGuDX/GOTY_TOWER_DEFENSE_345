// Observer.h
#pragma once

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;  // Called when the subject changes
};
