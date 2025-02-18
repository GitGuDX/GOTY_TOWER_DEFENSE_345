/**

@file Tower.cpp

@brief Implements Tower functionalities, including shooting and upgrades.
*/

#include "Tower.h"

Tower::Tower(TowerType type) 
    : m_eType(type)
    , m_iHealth(100)
    , m_fShootCooldown(0.0f)
    , m_iLevel(1)  // Start at level 1
{
    // Initialize base stats
    switch(type) {
        case TowerType::Basic:
            m_fRange = 300.0f;
            m_fMaxCooldown = 1.0f;
            m_fDamage = 10.0f;
            m_speed = 200.f;
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
            m_fRange = 200.0f;
            m_fMaxCooldown = 0.20f;
            m_fDamage = 5.0f;
            m_speed = 400.f;
            m_iCost = 200;
            break;
    }
}

Tower::~Tower()
{
}

bool Tower::Upgrade()
{
    if (!CanUpgrade()) {
        return false;
    }

    m_iLevel++;
    
    // Increase stats based on level (example multipliers)
    const float damageMultiplier = 1.25f;
    const float rangeMultiplier = 1.1f;
    const float cooldownMultiplier = 0.8f;
    const float speedMultiplier = 1.15f;

    m_fDamage *= damageMultiplier;
    m_fRange *= rangeMultiplier;
    m_fMaxCooldown *= cooldownMultiplier;
    m_speed += speedMultiplier;

    return true;
}

int Tower::GetUpgradeCost() const
{
    if (!CanUpgrade()) {
        return 0;
    }
    
    // Cost increases with each level
    return m_iCost * m_iLevel;
}

