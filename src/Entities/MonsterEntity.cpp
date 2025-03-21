#include "MonsterEntity.h"

MonsterEntity::MonsterEntity()
    : m_eType(MonsterGeneratorData::MonsterType::SIZE)
    , m_stCurrentPathIndex(0)
    , m_iLevel(0)
    , m_iActiveFrameIndex(0)
    , m_iDyingFrameIndex(0)
    , m_bIsDying(false)
    , m_bIsFinishedDying(false)
    , m_bIsDead(false)
    , m_bIsTemplate(true)
{
}

MonsterEntity::MonsterEntity(MonsterGeneratorData::MonsterType type, int level)
    : m_eType(type)
    , m_stCurrentPathIndex(0)
    , m_iLevel(level)
    , m_iActiveFrameIndex(0)
    , m_iDyingFrameIndex(0)
    , m_bIsDying(false)
    , m_bIsFinishedDying(false)
    , m_bIsDead(false)
    , m_bIsTemplate(false)
{
    SetInitialStats();
}

void MonsterEntity::IncrementActiveFrameIndex(int indexLimit)
{
    m_iActiveFrameIndex++;
    if (m_iActiveFrameIndex >= indexLimit) {
        m_iActiveFrameIndex = 0;
    }
    NotifyStatsChanged();
}

void MonsterEntity::IncrementDyingFrameIndex(int indexLimit)
{
    m_iDyingFrameIndex++;
    if (m_bIsFinishedDying == false && m_iDyingFrameIndex >= indexLimit) {
        m_bIsFinishedDying = true;
        //m_iDyingFrameIndex = 0;
    }
    NotifyStatsChanged();
}

void MonsterEntity::SetInitialStats()
{
    // Calculate and set the stats based on typeData and level
    if (m_eType == MonsterGeneratorData::MonsterType::Skeleton) {
        m_iMaxHealth = (MonsterGeneratorData::MonsterTypeData::BaseStats::iHealth + MonsterGeneratorData::MonsterTypeData::Skeleton::iHealthDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fHealthLevelUpRate);
        m_iHealth = m_iMaxHealth;
        m_fSpeed = (MonsterGeneratorData::MonsterTypeData::BaseStats::fSpeed + MonsterGeneratorData::MonsterTypeData::Skeleton::fSpeedDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fSpeedLevelUpRate);
        m_iStrength = (MonsterGeneratorData::MonsterTypeData::BaseStats::iStrength + MonsterGeneratorData::MonsterTypeData::Skeleton::iStrengthDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fStrengthLevelUpRate);
        m_iReward = (MonsterGeneratorData::MonsterTypeData::BaseStats::iReward + MonsterGeneratorData::MonsterTypeData::Skeleton::iRewardDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fRewardLevelUpRate);
    }
    else if (m_eType == MonsterGeneratorData::MonsterType::Reaper) {
        m_iMaxHealth = (MonsterGeneratorData::MonsterTypeData::BaseStats::iHealth + MonsterGeneratorData::MonsterTypeData::Reaper::iHealthDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fHealthLevelUpRate);
        m_iHealth = m_iMaxHealth;
        m_fSpeed = (MonsterGeneratorData::MonsterTypeData::BaseStats::fSpeed + MonsterGeneratorData::MonsterTypeData::Reaper::fSpeedDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fSpeedLevelUpRate);
        m_iStrength = (MonsterGeneratorData::MonsterTypeData::BaseStats::iStrength + MonsterGeneratorData::MonsterTypeData::Reaper::iStrengthDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fStrengthLevelUpRate);
        m_iReward = (MonsterGeneratorData::MonsterTypeData::BaseStats::iReward + MonsterGeneratorData::MonsterTypeData::Reaper::iRewardDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fRewardLevelUpRate);
    }
    else if (m_eType == MonsterGeneratorData::MonsterType::Golem) {
        m_iMaxHealth = (MonsterGeneratorData::MonsterTypeData::BaseStats::iHealth + MonsterGeneratorData::MonsterTypeData::Golem::iHealthDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fHealthLevelUpRate);
        m_iHealth = m_iMaxHealth;
        m_fSpeed = (MonsterGeneratorData::MonsterTypeData::BaseStats::fSpeed + MonsterGeneratorData::MonsterTypeData::Golem::fSpeedDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fSpeedLevelUpRate);
        m_iStrength = (MonsterGeneratorData::MonsterTypeData::BaseStats::iStrength + MonsterGeneratorData::MonsterTypeData::Golem::iStrengthDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fStrengthLevelUpRate);
        m_iReward = (MonsterGeneratorData::MonsterTypeData::BaseStats::iReward + MonsterGeneratorData::MonsterTypeData::Golem::iRewardDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fRewardLevelUpRate);
    }
    else if (m_eType == MonsterGeneratorData::MonsterType::Minotaur) {
        m_iMaxHealth = (MonsterGeneratorData::MonsterTypeData::BaseStats::iHealth + MonsterGeneratorData::MonsterTypeData::Minotaur::iHealthDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fHealthLevelUpRate);
        m_iHealth = m_iMaxHealth;
        m_fSpeed = (MonsterGeneratorData::MonsterTypeData::BaseStats::fSpeed + MonsterGeneratorData::MonsterTypeData::Minotaur::fSpeedDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fSpeedLevelUpRate);
        m_iStrength = (MonsterGeneratorData::MonsterTypeData::BaseStats::iStrength + MonsterGeneratorData::MonsterTypeData::Minotaur::iStrengthDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fStrengthLevelUpRate);
        m_iReward = (MonsterGeneratorData::MonsterTypeData::BaseStats::iReward + MonsterGeneratorData::MonsterTypeData::Minotaur::iRewardDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fRewardLevelUpRate);
    }
    else if (m_eType == MonsterGeneratorData::MonsterType::Ogre) {
        m_iMaxHealth = (MonsterGeneratorData::MonsterTypeData::BaseStats::iHealth + MonsterGeneratorData::MonsterTypeData::Ogre::iHealthDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fHealthLevelUpRate);
        m_iHealth = m_iMaxHealth;
        m_fSpeed = (MonsterGeneratorData::MonsterTypeData::BaseStats::fSpeed + MonsterGeneratorData::MonsterTypeData::Ogre::fSpeedDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fSpeedLevelUpRate);
        m_iStrength = (MonsterGeneratorData::MonsterTypeData::BaseStats::iStrength + MonsterGeneratorData::MonsterTypeData::Ogre::iStrengthDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fStrengthLevelUpRate);
        m_iReward = (MonsterGeneratorData::MonsterTypeData::BaseStats::iReward + MonsterGeneratorData::MonsterTypeData::Ogre::iRewardDifference)*GetLevelUpRateAtLevel(m_iLevel, MonsterGeneratorData::StatsLevelUpRate::fRewardLevelUpRate);
    }
    NotifyStatsChanged();
}


