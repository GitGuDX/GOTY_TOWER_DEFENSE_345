#include "TowerEntity.h"

TowerEntity::TowerEntity(TowerGenerator::TowerType type)
    : m_eType(type)
    , m_fRange(0.0f)
    , m_fMaxCooldown(0.0f)
    , m_fDamage(0.0f)
    , m_speed(0.0f)
    , m_iCost(0)
    , m_iLevel(1)  // Start at level 1
    , m_fShootCooldown(0.0f)
    , m_targetStrategy(nullptr) 

{
}

void TowerEntity::InitializeStat()
{
    // std::cout << "TowerEntity::InitializeStat() - Tower type: " << static_cast<int>(m_eType) << std::endl;
    // Access the appropriate struct based on the tower type
    if (m_eType == TowerGenerator::TowerType::Basic) 
    {
        m_fRange = TowerGenerator::TowerTypeData::Basic::fRange;
        m_fMaxCooldown = TowerGenerator::TowerTypeData::Basic::fMaxCooldown;
        m_fDamage = TowerGenerator::TowerTypeData::Basic::fDamage;
        m_speed = TowerGenerator::TowerTypeData::Basic::fspeed;
        m_iCost = TowerGenerator::TowerTypeData::Basic::iCost;
    }
    else if (m_eType == TowerGenerator::TowerType::Sniper) 
    {
        m_fRange = TowerGenerator::TowerTypeData::Sniper::fRange;
        m_fMaxCooldown = TowerGenerator::TowerTypeData::Sniper::fMaxCooldown;
        m_fDamage = TowerGenerator::TowerTypeData::Sniper::fDamage;
        m_speed = TowerGenerator::TowerTypeData::Sniper::fspeed;
        m_iCost = TowerGenerator::TowerTypeData::Sniper::iCost;
    }
    else if (m_eType == TowerGenerator::TowerType::Rapid) 
    {
        m_fRange = TowerGenerator::TowerTypeData::Rapid::fRange;
        m_fMaxCooldown = TowerGenerator::TowerTypeData::Rapid::fMaxCooldown;
        m_fDamage = TowerGenerator::TowerTypeData::Rapid::fDamage;
        m_speed = TowerGenerator::TowerTypeData::Rapid::fspeed;
        m_iCost = TowerGenerator::TowerTypeData::Rapid::iCost;
    }
    NotifyStatsChanged();
}

bool TowerEntity::Upgrade()
{
    if (!CanUpgrade()) {
        return false;
    }

    IncrementLevel();
    
    // m_fRange *= UpgradeRate::fRangeMultiplier;
    // m_fMaxCooldown *= UpgradeRate::fCooldownMultiplier;
    // m_fDamage *= UpgradeRate::fDamageMultiplier;
    // m_speed *= UpgradeRate::fSpeedMultiplier;

    NotifyStatsChanged();

    return true;
}

int TowerEntity::GetUpgradeCost() const
{
    if (!CanUpgrade()) {
        return 0;
    }
    
    // Cost increases with each level
    return m_iCost * m_iLevel;
}
