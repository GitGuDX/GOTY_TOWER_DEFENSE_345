#include "Tower.h"

Tower::Tower(TowerType type) 
    : m_eType(type)
    , m_iHealth(100)
    , m_fShootCooldown(0.0f)
{
    switch(type) {
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
            m_fRange = 200.0f;
            m_fMaxCooldown = 0.25f;
            m_fDamage = 5.0f;
            m_speed = 300.f;
            m_iCost = 200;
            break;
    }
}

Tower::~Tower()
{
}

