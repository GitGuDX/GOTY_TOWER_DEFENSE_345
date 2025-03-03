/**

@file Tower.h

@brief Declares the Tower class with attack logic and range mechanics.
*/

#ifndef TOWER_H
#define TOWER_H

#include "Entity.h"
#include <iostream>
#include "GameEvents.h"

enum class TowerType {
    Basic,
    Sniper,
    Rapid
};

class Tower : public Entity, public IGameSubject
{
public:
    Tower(TowerType type = TowerType::Basic); // Default constructor takes a type
    ~Tower();


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

    void NotifyStatsChanged() {
        for (auto observer : m_observers) {
            observer->Update(*this);
        }
    }

    void DebugPrint() const 
    {
        std::cout << "Tower Position: " << GetPosition().x << "," << GetPosition().y << "\n"
                  << "Health: " << m_iHealth << "\n"
                  << "Speed: " << m_fDamage << "\n";
    }

    float GetDamage() const
    {
        return m_fDamage;
    }

    float GetCooldown() const{
        return m_fMaxCooldown;
    }

    float GetSpeed() const 
    {
        return m_speed;
    }
    
    size_t GetCurrentPathIndex () const
    {
        return m_stCurrentPathIndex;
    }

    void SetDamage(float newDamage)
    {
        m_fDamage = newDamage;
    }

    void SetCurrentPathIndex(size_t newIndex)
    {
        m_stCurrentPathIndex = newIndex;

    }

    void SetType(TowerType type) {
        
        m_eType = type;
        
        switch (type) {
            case TowerType::Basic:
                m_fRange = 300.0f;
                m_fMaxCooldown = 1.0f;
                m_fDamage = 10.0f;
                m_speed = 300.f;
                m_iCost = 100;
                break;
            case TowerType::Sniper:
                m_fRange = 600.0f;
                m_fMaxCooldown = 3.0f;
                m_fDamage = 50.0f;
                m_speed = 800.f;
                m_iCost = 300;
                break;
            case TowerType::Rapid:
                m_fRange = 170.0f;
                m_fMaxCooldown = 0.14f;
                m_fDamage = 5.0f;
                m_speed = 400.f;
                m_iCost = 200;
                break;
        }
        NotifyStatsChanged();

    }

    void SetRange(float range) { m_fRange = range; }
    float GetRange() const { return m_fRange; }
    
    bool CanShoot() const { return m_fShootCooldown <= 0.0f; }
    void ResetCooldown() { m_fShootCooldown = m_fMaxCooldown; }
    void UpdateCooldown(float deltaTime) { m_fShootCooldown -= deltaTime; }

    TowerType GetType() const { return m_eType; }
    int GetCost() const { return m_iCost; }
    void SetCost(int value) { m_iCost = value; }

    // Add new level-related methods
    int GetLevel() const { return m_iLevel; }
    bool CanUpgrade() const { return m_iLevel < MAX_LEVEL; }
    bool Upgrade();
    int GetUpgradeCost() const;

    float GetHealth();               // Returns current health
    bool IsDestroyed();              // Checks if tower is destroyed
    void TakeDamage(float damage);   // Reduces health when attacked

private:
    std::vector<IGameObserver*> m_observers;
    static const int MAX_LEVEL = 3; // Maximum level a tower can reach
    
    TowerType m_eType;
    int m_iHealth;
    float m_fDamage;
    float m_iCost;
    size_t m_stCurrentPathIndex;           // index of the Tower's current path
    float m_fShootCooldown;
    float m_fMaxCooldown;
    float m_fRange;
    float m_speed; // Adjust speed as needed
    int m_iLevel;                   // Current tower level

    float m_fHealth = 100.0f;  // Tower health
};

#endif