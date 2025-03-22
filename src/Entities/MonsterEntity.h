#ifndef MONSTER_ENTITY_H
#define MONSTER_ENTITY_H

#include "Entity.h"
#include "../GameEvents.h"
#include "../Generators/MonsterGeneratorData.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

//class MonsterGenerator;

class MonsterEntity : public Entity, public IGameSubject
{
public:
    MonsterEntity();
    MonsterEntity(MonsterGeneratorData::MonsterType type, int level);
    ~MonsterEntity() = default;

    virtual void AddObserver(IGameObserver* observer) override {
        m_observers.push_back(observer);
    }

    virtual void RemoveObserver(IGameObserver* observer) override {
        m_observers.erase(
            std::remove(m_observers.begin(), m_observers.end(), observer),
            m_observers.end()
        );
    }

    virtual void RemoveAllObservers()
    {
        m_observers.clear();
    }

    virtual void NotifyStatsChanged() {
        for (auto observer : m_observers) {
            observer->Update(*this);
        }
    }

    virtual const MonsterEntity* GetBaseMonsterEntity() const
    {
        return this;  // In the base class, this is just the current object
    }

    // Explicitly Ignore the Parameter to avoid compiler's unused parameter warning
    // virtual void Update(float /*deltaTime*/) 
    // {
    //     // No functionality here; just a placeholder
    // }

    virtual void SetPosition(const sf::Vector2f& position) override
    {
        m_vPosition = position;
        NotifyStatsChanged();
    }

    // virtual void Move(const sf::Vector2f& offset) override
    // {
    //     Entity::Move(offset);

    //     NotifyStatsChanged();
    // }

    virtual void Move(const sf::Vector2f& offset) override 
    {
        m_vPosition += offset;
        NotifyStatsChanged();
    }

    virtual void SetType(MonsterGeneratorData::MonsterType type) { 
        m_eType = type; 
        NotifyStatsChanged();
    }

    virtual void SetHealth(float health) { 
        m_iHealth = health; 
        NotifyStatsChanged();
    }

    virtual void SetMaxHealth(float maxHealth) { 
        m_iMaxHealth = maxHealth; 
        NotifyStatsChanged();
    }

    virtual void SetSpeed(float speed) { 
        m_fSpeed = speed; 
        NotifyStatsChanged();
    }

    virtual void SetLevel(int level) { 
        m_iLevel = level; 
        NotifyStatsChanged();
    }

    virtual void SetStrength(int strength) { 
        m_iStrength = strength; 
        NotifyStatsChanged();
    }

    virtual void SetReward(int reward) { 
        m_iReward = reward; 
        NotifyStatsChanged();
    }

    virtual void SetCurrentPathIndex(size_t index) { 
        m_stCurrentPathIndex = index; 
        NotifyStatsChanged();
    }

    virtual void SetIsDying(bool isDying) { 
        m_bIsDying = isDying; 
        NotifyStatsChanged();
    }

    virtual void SetIsDead(bool isDead) { 
        m_bIsDead = isDead; 
        NotifyStatsChanged();
    }

    virtual void SetIsTemplate(bool isTemplate) { 
        m_bIsTemplate = isTemplate; 
        NotifyStatsChanged();
    }

    virtual void IncrementActiveFrameIndex(int indexLimit);

    virtual void IncrementDyingFrameIndex(int indexLimit);

    virtual MonsterGeneratorData::MonsterType GetType() const { return m_eType; }

    virtual Vector2f GetPosition() const override { return m_vPosition; }

    virtual float GetHealth() const { return m_iHealth; }

    virtual float GetMaxHealth() const { return m_iMaxHealth; }

    virtual float GetSpeed() const { return m_fSpeed; }

    virtual int GetLevel() const { return m_iLevel; }

    virtual int GetStrength() const { return m_iStrength; }

    virtual int GetReward() const { return m_iReward; }

    virtual size_t GetCurrentPathIndex() const { return m_stCurrentPathIndex; }

    virtual int GetActiveFrameIndex() const { return m_iActiveFrameIndex; }

    virtual int GetDyingFrameIndex() const { return m_iDyingFrameIndex; }

    virtual bool GetIsDying() const { return m_bIsDying; }

    virtual bool GetIsFinishedDying() const { return m_bIsFinishedDying; }

    virtual bool GetIsDead() const { return m_bIsDead; }

    virtual bool GetIsTemplate() const { return m_bIsTemplate; }

private:
    void SetInitialStats();

    float GetLevelUpRateAtLevel(int level, float baseRate)
    {
        return baseRate * std::pow(1.1f, level - 1); // Assuming a 10% increase per level.
    }

private:
    std::vector<IGameObserver*> m_observers;

    MonsterGeneratorData::MonsterType m_eType;
    sf::Vector2f m_vPosition;
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