#pragma once
#include "GameEvents.h"
#include <vector>

class GameEventManager : public IGameSubject {
private:
    std::vector<IGameObserver*> m_observers;

public:
    void AddObserver(IGameObserver* observer) override {
        m_observers.push_back(observer);
    }

    void RemoveObserver(IGameObserver* observer) override {
        m_observers.erase(
            std::remove(m_observers.begin(), m_observers.end(), observer),
            m_observers.end()
        );
    }

   /* void NotifyObservers(const GameEvent& event) override {
        for (auto observer : m_observers) {
            observer->OnGameEvent(event);
        }
    }*/
};