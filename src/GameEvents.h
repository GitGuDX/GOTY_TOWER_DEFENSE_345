#pragma once
#include <vector>
#include <string>

class Tower;
class IGameSubject;

// Observer interface
class IGameObserver {
public:
    virtual ~IGameObserver() = default;
    virtual void Update(const IGameSubject& subject) = 0;
};

// Subject interface
class IGameSubject {
public:
    virtual ~IGameSubject() = default;
    virtual void AddObserver(IGameObserver* observer) = 0;
    virtual void RemoveObserver(IGameObserver* observer) = 0;

};