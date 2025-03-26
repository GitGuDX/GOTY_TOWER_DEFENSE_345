#include "MonsterEntity.h"

/**
 * @brief Default constructor for MonsterEntity.
 * 
 * Initializes a MonsterEntity with default values. The monster is marked as a template and not yet leveled up.
 */
MonsterEntity::MonsterEntity()
    : m_eType(MonsterGeneratorData::MonsterType::SIZE)
    , m_stCurrentPathIndex(0)
    , m_iLevel(0)
    , m_iActiveFrameIndex(0)
    , m_iDyingFrameIndex(0)
    , m_bIsDying(false)
    , m_bIsFinishedDying(false)
    , m_bIsDead(false)
    , m_bIsOnSlowDebuff(false)
    , m_bIsOnBurnEffect(false)
    , m_bIsTemplate(true)
{
}

/**
 * @brief Constructor for MonsterEntity with specified type and level.
 * 
 * Initializes the MonsterEntity with the given type and level, and calls SetInitialStats() to calculate the stats.
 * 
 * @param type The type of the monster.
 * @param level The level of the monster.
 */
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

/**
 * @brief Sets the initial stats for the monster based on its type and level.
 * 
 * This function calculates and sets the monster's maximum health, health, speed, strength,
 * and reward based on its type (Skeleton, Reaper, Golem, Minotaur, Ogre) and its current level.
 * The stats are adjusted using predefined differences and the level-up rate for each attribute.
 * 
 * @note The stats are dynamically updated by multiplying the base stats with the level-up rate
 *       at the given level. The stats for each monster type are calculated individually.
 * 
 * @see GetLevelUpRateAtLevel()
 */
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


