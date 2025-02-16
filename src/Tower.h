#ifndef TOWER_H
#define TOWER_H

#include "Entity.h"
#include <iostream>

enum class TowerType {
    Basic,
    Sniper,
    Rapid
};

class Tower : public Entity
{
public:
    Tower(TowerType type = TowerType::Basic); // Default constructor takes a type
    ~Tower();

    void DebugPrint() const 
    {
        std::cout << "Tower Position: " << GetPosition().x << "," << GetPosition().y << "\n"
                  << "Health: " << m_iHealth << "\n"
                  << "Speed: " << m_fDamage << "\n";
    }

    float GetDamage()
    {
        return m_fDamage;
    }
    
    size_t GetCurrentPathIndex()
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

    void SetRange(float range) { m_fRange = range; }
    float GetRange() const { return m_fRange; }
    
    bool CanShoot() const { return m_fShootCooldown <= 0.0f; }
    void ResetCooldown() { m_fShootCooldown = m_fMaxCooldown; }
    void UpdateCooldown(float deltaTime) { m_fShootCooldown -= deltaTime; }

    TowerType GetType() const { return m_eType; }

private:
    TowerType m_eType;
    int m_iHealth;
    float m_fDamage;
    size_t m_stCurrentPathIndex;           // index of the Tower's current path
    float m_fShootCooldown;
    float m_fMaxCooldown;
    float m_fRange;
};

#endif