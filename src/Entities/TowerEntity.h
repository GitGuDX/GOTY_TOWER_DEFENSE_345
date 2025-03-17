#ifndef TOWER_ENTITY_H
#define TOWER_ENTITY_H

#include "Entity.h"
#include "../GameEvents.h"
#include "../Generators/TowerGenerator.h"
#include <iostream>
#include <vector>
#include "../TowerTargetStrategy.h"

class TowerGenerator;


class TowerEntity : public Entity, public IGameSubject
{
private:
    struct UpgradeRate
    {
        static constexpr float fDamageMultiplier = 1.20f;
        static constexpr float fRangeMultiplier = 1.05f;
        static constexpr float fCooldownMultiplier = 0.9f;
        static constexpr float fSpeedMultiplier = 1.10f;
    };

public:
    TowerEntity(TowerGenerator::TowerType type); // Default constructor takes a type
    ~TowerEntity() = default;

    void SetTargetStrategy(TowerTargetStrategy* strategy) {
        m_targetStrategy = strategy;
    }

    Monster* SelectTarget(const std::vector<Monster>& enemies) const {
        if (m_targetStrategy) {
            return m_targetStrategy->SelectTarget(*this, enemies);
        }
        return nullptr;
    }

    void AddObserver(IGameObserver* observer) override {
        //std::cout << "This pointer when addObserver is called: " << this << std::endl;
        m_observers.push_back(observer);
    }

    void RemoveObserver(IGameObserver* observer) override {
        m_observers.erase(
            std::remove(m_observers.begin(), m_observers.end(), observer),
            m_observers.end()
        );
    }

    void NotifyStatsChanged() {
        //std::cout << "This pointer when notify change is called: " << this << std::endl;
        for (auto observer : m_observers) {
            observer->Update(*this);
        }
    }

    void SetPosition(const sf::Vector2f& position) override
    {
        //std::cout << "This pointer when set position is called: " << this << std::endl;
        Entity::SetPosition(position);

        NotifyStatsChanged();
    }

    void SetType(TowerGenerator::TowerType type) { 
        m_eType = type; 
        NotifyStatsChanged();
    }

    void SetRange(float range) { 
        m_fRange = range; 
        NotifyStatsChanged();
    }

    void SetMaxCooldown(float cooldown) { 
        m_fMaxCooldown = cooldown; 
        NotifyStatsChanged();
    }

    void SetDamage(float damage) { 
        m_fDamage = damage; 
        NotifyStatsChanged();
    }

    void SetSpeed(float speed) { 
        m_speed = speed; 
        NotifyStatsChanged();
    }

    void SetCost(int cost) { 
        m_iCost = cost; 
        NotifyStatsChanged();
    }

    void SetLevel(int level) { 
        m_iLevel = level; 
        NotifyStatsChanged();
    }

    void SetIsTemplate(bool isTemplate) { 
        m_isTemplate = isTemplate; 
        NotifyStatsChanged();
    }

    void InitializeStat();

    TowerGenerator::TowerType GetType() const { return m_eType; }

    float GetRange() const { return m_fRange; }

    float GetMaxCooldown() const { return m_fMaxCooldown; }

    float GetDamage() const { return m_fDamage; }

    float GetSpeed() const { return m_speed; }

    int GetCost() const { return m_iCost; }

    int GetLevel() const { return m_iLevel; }

    bool GetIsTemplate() const { return m_isTemplate; }

    bool CanShoot() const { return m_fShootCooldown <= 0.0f; }

    void ResetCooldown() { m_fShootCooldown = m_fMaxCooldown; }

    void UpdateCooldown(float deltaTime) { m_fShootCooldown -= deltaTime; }

    bool CanUpgrade() const { return m_iLevel < MAX_LEVEL; }

    bool Upgrade();

    int GetUpgradeCost() const;


private:

    std::vector<IGameObserver*> m_observers;
    static const int MAX_LEVEL = 3; // Maximum level a tower can reach

    TowerGenerator::TowerType m_eType;
    float m_fRange;
    float m_fMaxCooldown;
    float m_fDamage;
    float m_speed;
    int m_iCost;
    int m_iLevel;

    float m_fShootCooldown;
    TowerTargetStrategy* m_targetStrategy;


    bool m_isTemplate = false;

};

#endif  // TOWER_ENTITY_H