#include "Tower.h"

Tower::Tower(TowerType type) 
    : m_eType(type)
    , m_iHealth(100)
    , m_fShootCooldown(0.0f)
{
    switch(type) {
        case TowerType::Basic:
            m_fRange = 300.0f;
            m_fMaxCooldown = 3.0f;
            m_fDamage = 10.0f;
            break;
        case TowerType::Sniper:
            m_fRange = 600.0f;
            m_fMaxCooldown = 5.0f;
            m_fDamage = 50.0f;
            break;
        case TowerType::Rapid:
            m_fRange = 200.0f;
            m_fMaxCooldown = 1.0f;
            m_fDamage = 5.0f;
            break;
    }
}

Tower::~Tower()
{
}

