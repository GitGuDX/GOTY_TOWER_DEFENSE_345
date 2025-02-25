#pragma once
#include <vector>
#include <string>

// Event types that can occur in the game
enum class GameEventType {
    MonsterDeath,
    TowerAttack,
    LevelChange,
    ScoreChange,
    GameOver
};

// Event data structure
struct GameEvent {
    GameEventType type;
    int value;
    std::string message;
};

// Observer interface
class IGameObserver {
public:
    virtual ~IGameObserver() = default;
    virtual void OnGameEvent(const GameEvent& event) = 0;
    virtual void OnTowerStatsChanged(const Tower& tower) = 0;
};

// Subject interface
class IGameSubject {
public:
    virtual ~IGameSubject() = default;
    virtual void AddObserver(IGameObserver* observer) = 0;
    virtual void RemoveObserver(IGameObserver* observer) = 0;
    virtual void NotifyObservers(const GameEvent& event) = 0;
};