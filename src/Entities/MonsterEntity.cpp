#include "MonsterEntity.h"

MonsterEntity::MonsterEntity(MonsterGenerator::MonsterType type, int level)
    : m_eType(type)
    , m_stCurrentPathIndex(0)
    , m_iLevel(level)
    , m_iActiveFrameIndex(0)
    , m_iDyingFrameIndex(0)
    , m_bIsDying(false)
{
    SetInitialStats();
}

void MonsterEntity::SetInitialStats()
{
    // Calculate and set the stats based on typeData and level
    if (m_eType == MonsterGenerator::MonsterType::Skeleton) {
        m_iMaxHealth = (MonsterGenerator::MonsterTypeData::BaseStats::iHealth + MonsterGenerator::MonsterTypeData::Skeleton::iHealthDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fHealthLevelUpRate);
        m_iHealth = m_iMaxHealth;
        m_fSpeed = (MonsterGenerator::MonsterTypeData::BaseStats::fSpeed + MonsterGenerator::MonsterTypeData::Skeleton::fSpeedDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fSpeedLevelUpRate);
        m_iStrength = (MonsterGenerator::MonsterTypeData::BaseStats::iStrength + MonsterGenerator::MonsterTypeData::Skeleton::iStrengthDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fStrengthLevelUpRate);
        m_iReward = (MonsterGenerator::MonsterTypeData::BaseStats::iReward + MonsterGenerator::MonsterTypeData::Skeleton::iRewardDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fRewardLevelUpRate);
    }
    else if (m_eType == MonsterGenerator::MonsterType::Reaper) {
        m_iMaxHealth = (MonsterGenerator::MonsterTypeData::BaseStats::iHealth + MonsterGenerator::MonsterTypeData::Reaper::iHealthDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fHealthLevelUpRate);
        m_iHealth = m_iMaxHealth;
        m_fSpeed = (MonsterGenerator::MonsterTypeData::BaseStats::fSpeed + MonsterGenerator::MonsterTypeData::Reaper::fSpeedDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fSpeedLevelUpRate);
        m_iStrength = (MonsterGenerator::MonsterTypeData::BaseStats::iStrength + MonsterGenerator::MonsterTypeData::Reaper::iStrengthDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fStrengthLevelUpRate);
        m_iReward = (MonsterGenerator::MonsterTypeData::BaseStats::iReward + MonsterGenerator::MonsterTypeData::Reaper::iRewardDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fRewardLevelUpRate);
    }
    else if (m_eType == MonsterGenerator::MonsterType::Golem) {
        m_iMaxHealth = (MonsterGenerator::MonsterTypeData::BaseStats::iHealth + MonsterGenerator::MonsterTypeData::Golem::iHealthDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fHealthLevelUpRate);
        m_iHealth = m_iMaxHealth;
        m_fSpeed = (MonsterGenerator::MonsterTypeData::BaseStats::fSpeed + MonsterGenerator::MonsterTypeData::Golem::fSpeedDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fSpeedLevelUpRate);
        m_iStrength = (MonsterGenerator::MonsterTypeData::BaseStats::iStrength + MonsterGenerator::MonsterTypeData::Golem::iStrengthDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fStrengthLevelUpRate);
        m_iReward = (MonsterGenerator::MonsterTypeData::BaseStats::iReward + MonsterGenerator::MonsterTypeData::Golem::iRewardDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fRewardLevelUpRate);
    }
    else if (m_eType == MonsterGenerator::MonsterType::Minotaur) {
        m_iMaxHealth = (MonsterGenerator::MonsterTypeData::BaseStats::iHealth + MonsterGenerator::MonsterTypeData::Minotaur::iHealthDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fHealthLevelUpRate);
        m_iHealth = m_iMaxHealth;
        m_fSpeed = (MonsterGenerator::MonsterTypeData::BaseStats::fSpeed + MonsterGenerator::MonsterTypeData::Minotaur::fSpeedDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fSpeedLevelUpRate);
        m_iStrength = (MonsterGenerator::MonsterTypeData::BaseStats::iStrength + MonsterGenerator::MonsterTypeData::Minotaur::iStrengthDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fStrengthLevelUpRate);
        m_iReward = (MonsterGenerator::MonsterTypeData::BaseStats::iReward + MonsterGenerator::MonsterTypeData::Minotaur::iRewardDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fRewardLevelUpRate);
    }
    else if (m_eType == MonsterGenerator::MonsterType::Ogre) {
        m_iMaxHealth = (MonsterGenerator::MonsterTypeData::BaseStats::iHealth + MonsterGenerator::MonsterTypeData::Ogre::iHealthDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fHealthLevelUpRate);
        m_iHealth = m_iMaxHealth;
        m_fSpeed = (MonsterGenerator::MonsterTypeData::BaseStats::fSpeed + MonsterGenerator::MonsterTypeData::Ogre::fSpeedDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fSpeedLevelUpRate);
        m_iStrength = (MonsterGenerator::MonsterTypeData::BaseStats::iStrength + MonsterGenerator::MonsterTypeData::Ogre::iStrengthDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fStrengthLevelUpRate);
        m_iReward = (MonsterGenerator::MonsterTypeData::BaseStats::iReward + MonsterGenerator::MonsterTypeData::Ogre::iRewardDifference)*MonsterGenerator::GetLevelUpRateAtLevel(m_iLevel, MonsterGenerator::StatsLevelUpRate::fRewardLevelUpRate);
    }
    NotifyStatsChanged();
}


