#ifndef MONSTER_ENTITY_H
#define MONSTER_ENTITY_H

#include "Entity.h"
#include "../GameEvents.h"
#include "../Generators/MonsterGenerator.h"
#include <iostream>
#include <vector>

class MonsterGenerator;

class MonsterEntity : public Entity, public IGameSubject
{
public:
    MonsterEntity();
    MonsterEntity(MonsterGenerator::MonsterType type, int level);
    ~MonsterEntity() = default;

    void AddObserver(IGameObserver* observer) override {
        m_observers.push_back(observer);
    }

    void RemoveObserver(IGameObserver* observer) override {
        m_observers.erase(
            std::remove(m_observers.begin(), m_observers.end(), observer),
            m_observers.end()
        );
    }

    void NotifyStatsChanged() {
        for (auto observer : m_observers) {
            observer->Update(*this);
        }
    }    

    void SetPosition(const sf::Vector2f& position) override
    {
        Entity::SetPosition(position);

        NotifyStatsChanged();
    }

    void Move(const sf::Vector2f& offset) override
    {
        Entity::Move(offset);

        NotifyStatsChanged();
    }

    void SetType(MonsterGenerator::MonsterType type) { 
        m_eType = type; 
        NotifyStatsChanged();
    }

    void SetHealth(float health) { 
        m_iHealth = health; 
        NotifyStatsChanged();
    }

    void SetMaxHealth(float maxHealth) { 
        m_iMaxHealth = maxHealth; 
        NotifyStatsChanged();
    }

    void SetSpeed(float speed) { 
        m_fSpeed = speed; 
        NotifyStatsChanged();
    }

    void SetLevel(int level) { 
        m_iLevel = level; 
        NotifyStatsChanged();
    }

    void SetStrength(int strength) { 
        m_iStrength = strength; 
        NotifyStatsChanged();
    }

    void SetReward(int reward) { 
        m_iReward = reward; 
        NotifyStatsChanged();
    }

    void SetCurrentPathIndex(size_t index) { 
        m_stCurrentPathIndex = index; 
        NotifyStatsChanged();
    }

    void SetIsDying(bool isDying) { 
        m_bIsDying = isDying; 
        NotifyStatsChanged();
    }

    void SetIsDead(bool isDead) { 
        m_bIsDead = isDead; 
        NotifyStatsChanged();
    }

    void SetIsTemplate(bool isTemplate) { 
        m_bIsTemplate = isTemplate; 
        NotifyStatsChanged();
    }

    void IncrementActiveFrameIndex(int indexLimit);

    void IncrementDyingFrameIndex(int indexLimit);

    MonsterGenerator::MonsterType GetType() const { return m_eType; }

    float GetHealth() const { return m_iHealth; }

    float GetMaxHealth() const { return m_iMaxHealth; }

    float GetSpeed() const { return m_fSpeed; }

    int GetLevel() const { return m_iLevel; }

    int GetStrength() const { return m_iStrength; }

    int GetReward() const { return m_iReward; }

    size_t GetCurrentPathIndex() const { return m_stCurrentPathIndex; }

    int GetActiveFrameIndex() const { return m_iActiveFrameIndex; }

    int GetDyingFrameIndex() const { return m_iDyingFrameIndex; }

    bool GetIsDying() const { return m_bIsDying; }

    bool GetIsFinishedDying() const { return m_bIsFinishedDying; }

    bool GetIsDead() const { return m_bIsDead; }

    bool GetIsTemplate() const { return m_bIsTemplate; }

private:
    void SetInitialStats();

private:
    std::vector<IGameObserver*> m_observers;

    MonsterGenerator::MonsterType m_eType;
    size_t m_stCurrentPathIndex;           // index of the monster's current path
    float m_iHealth;
    float m_iMaxHealth;
    float m_fSpeed;
    int m_iLevel;
    int m_iStrength;                           // Determines the rate that the monster steals coin from the player
    int m_iReward;
    int m_iActiveFrameIndex;
    int m_iDyingFrameIndex;
    bool m_bIsDying;
    bool m_bIsFinishedDying;
    bool m_bIsDead;

    bool m_bIsTemplate;
};

#endif