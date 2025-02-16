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

    float GetSpeed()
    {
        return m_speed;
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

    void SetType(TowerType type) {
        m_eType = type;
        
        switch (type) {
            case TowerType::Basic:
                m_fRange = 300.0f;
                m_fMaxCooldown = 3.0f;
                m_fDamage = 10.0f;
                m_speed = 300.f;
                break;
            case TowerType::Sniper:
                m_fRange = 600.0f;
                m_fMaxCooldown = 5.0f;
                m_fDamage = 50.0f;
                m_speed = 800.f;
                break;
            case TowerType::Rapid:
                m_fRange = 200.0f;
                m_fMaxCooldown = 0.25f;
                m_fDamage = 5.0f;
                m_speed = 400.f;
                break;
        }
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
    float m_speed; // Adjust speed as needed
};

#endif