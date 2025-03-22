#ifndef TOWER_ENTITY_H
#define TOWER_ENTITY_H

#include "Entity.h"
#include "../GameEvents.h"
#include "../Generators/TowerGeneratorData.h"
#include <iostream>
#include <vector>
#include <memory>
#include "../TowerTargetStrategy.h"

//class TowerGenerator;


class TowerEntity : public Entity, public IGameSubject
{
// protected:
//     struct UpgradeRate
//     {
//         static constexpr float fDamageMultiplier = 1.70f;
//         static constexpr float fRangeMultiplier = 1.55f;
//         static constexpr float fCooldownMultiplier = 1.4f;
//         static constexpr float fSpeedMultiplier = 1.60f;
//     };

public:
    TowerEntity(TowerGeneratorData::TowerType type); // Default constructor takes a type
    ~TowerEntity() = default;

    virtual void SetTargetStrategy(TowerTargetStrategy* strategy) {
        m_targetStrategy = strategy;
        std::cout << "Strategy set for tower at position: " << GetPosition().x << "," << GetPosition().y << std::endl;
    }


    virtual MonsterEntity* SelectTarget(const std::vector<std::unique_ptr<MonsterEntity>>& enemies) const {
        if (m_targetStrategy) {
            return m_targetStrategy->SelectTarget(*this, enemies);
        }
        std::cout << "No targeting strategy set!" << std::endl;
        return nullptr;
    }

    virtual void AddObserver(IGameObserver* observer) override {
        //std::cout << "This pointer when addObserver is called: " << this << std::endl;
        m_observers.push_back(observer);
    }

    virtual void RemoveObserver(IGameObserver* observer) override {
        m_observers.erase(
            std::remove(m_observers.begin(), m_observers.end(), observer),
            m_observers.end()
        );
    }

    virtual void NotifyStatsChanged() {
        //std::cout << "This pointer when notify change is called: " << this << std::endl;
        for (auto observer : m_observers) {
            observer->Update(*this);
        }
    }

    virtual const TowerEntity* GetBaseTowerEntity() const
    {
        return this;  // In the base class, this is just the current object
    }

    virtual void SetPosition(const sf::Vector2f& position) override
    {
        //std::cout << "This pointer when set position is called: " << this << std::endl;
        //Entity::SetPosition(position);
        m_vPosition = position;

        NotifyStatsChanged();
    }

    virtual void SetType(TowerGeneratorData::TowerType type) { 
        m_eType = type; 
        NotifyStatsChanged();
    }

    virtual void SetRange(float range) { 
        m_fRange = range; 
        NotifyStatsChanged();
    }

    virtual void SetMaxCooldown(float cooldown) { 
        m_fMaxCooldown = cooldown; 
        NotifyStatsChanged();
    }

    virtual void SetDamage(float damage) { 
        m_fDamage = damage; 
        NotifyStatsChanged();
    }

    virtual void SetSpeed(float speed) { 
        m_speed = speed; 
        NotifyStatsChanged();
    }

    virtual void SetCost(int cost) { 
        m_iCost = cost; 
        NotifyStatsChanged();
    }

    virtual void SetLevel(int level) { 
        m_iLevel = level; 
        NotifyStatsChanged();
    }

    virtual void SetIsTemplate(bool isTemplate) { 
        m_isTemplate = isTemplate; 
        NotifyStatsChanged();
    }

    
    virtual void IncrementLevel() { 
        m_iLevel++; 
        NotifyStatsChanged();
    }

    virtual void InitializeStat();

    virtual TowerGeneratorData::TowerType GetType() const { return m_eType; }

    virtual Vector2f GetPosition() const override { return m_vPosition; }

    virtual float GetRange() const { return m_fRange; }

    virtual float GetMaxCooldown() const { return m_fMaxCooldown; }

    virtual float GetDamage() const { return m_fDamage; }

    virtual float GetSpeed() const { return m_speed; }

    virtual int GetCost() const { return m_iCost; }

    virtual int GetLevel() const { return m_iLevel; }

    virtual bool GetIsTemplate() const { return m_isTemplate; }

    virtual float GetShootCooldown() const { return m_fShootCooldown; }

    virtual bool GetIsFlameThrowerActive() const { return bIsFlameThrowerActive; }

    virtual void SetIsFlameThrowerActive(bool isActive) { bIsFlameThrowerActive = isActive; }

    int GetFlameFrame() const;

    void SetFlameFrame(int frame);
    
    void IncrementFlameFrame();
    
    void DecrementFlameFrame();

    // For flame clock
    sf::Clock& GetFlameClock(); // Return by reference so you can call .restart()

    // For flame sprite
    Entity& GetFlameSprite();

    virtual bool CanShoot() const { return m_fShootCooldown <= 0.0f; }

    virtual void ResetCooldown() { m_fShootCooldown = GetMaxCooldown(); }

    virtual void UpdateCooldown(float deltaTime) { m_fShootCooldown -= deltaTime; }

    virtual bool CanUpgrade() const { return m_iLevel < MAX_LEVEL; }

    virtual bool Upgrade();

    virtual int GetUpgradeCost() const;


private:

    std::vector<IGameObserver*> m_observers;
    static const int MAX_LEVEL = 3; // Maximum level a tower can reach

    TowerGeneratorData::TowerType m_eType;
    sf::Vector2f m_vPosition;
    float m_fRange;
    float m_fMaxCooldown;
    float m_fDamage;
    float m_speed;
    int m_iCost;
    int m_iLevel;
    bool bIsFlameThrowerActive;
    int iFlameFrame;
    sf::Clock flameClock;
    Entity flameSprite; // If your flame is visualized per tower

    float m_fShootCooldown;
    TowerTargetStrategy* m_targetStrategy = nullptr;


    bool m_isTemplate = false;

};

#endif  // TOWER_ENTITY_H