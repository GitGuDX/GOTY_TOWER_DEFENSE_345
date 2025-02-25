// Subject.h
#pragma once
#include <vector>
#include "Observer.h"

class Subject {
    std::vector<Observer*> observers;  // List of observers

public:
    // Attach an observer
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    // Notify all observers
    void notify() {
        for (auto observer : observers) {
            observer->update();  // Call update on each observer
        }
    }

    // Detach an observer (optional)
    void detach(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }
};