#pragma once
#include <vector>
#include <string>

class Tower;



// Observer interface
class IGameObserver {
public:
    virtual ~IGameObserver() = default;
    virtual void OnTowerStatsChanged(const Tower& tower) = 0;
};

// Subject interface
class IGameSubject {
public:
    virtual ~IGameSubject() = default;
    virtual void AddObserver(IGameObserver* observer) = 0;
    virtual void RemoveObserver(IGameObserver* observer) = 0;

};