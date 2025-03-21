#include "TowerEntity.h"

TowerEntity::TowerEntity(TowerGeneratorData::TowerType type)
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
    if (m_eType == TowerGeneratorData::TowerType::Basic) 
    {
        m_fRange = TowerGeneratorData::TowerTypeData::Basic::fRange;
        m_fMaxCooldown = TowerGeneratorData::TowerTypeData::Basic::fMaxCooldown;
        m_fDamage = TowerGeneratorData::TowerTypeData::Basic::fDamage;
        m_speed = TowerGeneratorData::TowerTypeData::Basic::fspeed;
        m_iCost = TowerGeneratorData::TowerTypeData::Basic::iCost;
    }
    else if (m_eType == TowerGeneratorData::TowerType::Sniper) 
    {
        m_fRange = TowerGeneratorData::TowerTypeData::Sniper::fRange;
        m_fMaxCooldown = TowerGeneratorData::TowerTypeData::Sniper::fMaxCooldown;
        m_fDamage = TowerGeneratorData::TowerTypeData::Sniper::fDamage;
        m_speed = TowerGeneratorData::TowerTypeData::Sniper::fspeed;
        m_iCost = TowerGeneratorData::TowerTypeData::Sniper::iCost;
    }
    else if (m_eType == TowerGeneratorData::TowerType::Rapid) 
    {
        m_fRange = TowerGeneratorData::TowerTypeData::Rapid::fRange;
        m_fMaxCooldown = TowerGeneratorData::TowerTypeData::Rapid::fMaxCooldown;
        m_fDamage = TowerGeneratorData::TowerTypeData::Rapid::fDamage;
        m_speed = TowerGeneratorData::TowerTypeData::Rapid::fspeed;
        m_iCost = TowerGeneratorData::TowerTypeData::Rapid::iCost;
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
