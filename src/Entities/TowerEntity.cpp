#include "TowerEntity.h"

TowerEntity::TowerEntity(TowerGeneratorData::TowerType type)
    : m_eType(type)
    , m_fRange(0.0f)
    , m_fMaxCooldown(0.0f)
    , m_fDamage(0.0f)
    , m_speed(0.0f)
    , m_iCost(0)
    , m_iLevel(1)  // Start at level 1
    , bIsFlameThrowerActive(false)
    , iFlameFrame(0)
    , m_fShootCooldown(0.0f)
    , m_targetStrategy(nullptr)

{
}

int TowerEntity::GetUpgradeCost() const
{
    if (!CanUpgrade()) {
        return 0;
    }
    
    // Cost increases with each level
    return m_iCost * m_iLevel;
}

// ** Should be in TowerObserver class/////////////
int TowerEntity::GetFlameFrame() const {
    return iFlameFrame;
}
void TowerEntity::SetFlameFrame(int frame) {
    iFlameFrame = frame;
}
void TowerEntity::IncrementFlameFrame() {
    iFlameFrame++;
}
void TowerEntity::DecrementFlameFrame() {
    iFlameFrame--;
}
sf::Clock& TowerEntity::GetFlameClock() {
    return flameClock;
}
Entity& TowerEntity::GetFlameSprite() {
    return flameSprite;
}
///////////////////////////////////////////////////