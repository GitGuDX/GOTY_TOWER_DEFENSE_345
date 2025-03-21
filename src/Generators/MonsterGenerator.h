#ifndef MONSTER_GENERATOR_H
#define MONSTER_GENERATOR_H

#include "MonsterGeneratorData.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

class MonsterEntity;

class MonsterGenerator
{
public: 
    MonsterGenerator();
    ~MonsterGenerator() = default;

    // enum class MonsterType
    // {
    //     Skeleton,
    //     Reaper,
    //     Golem,
    //     Minotaur,
    //     Ogre,
    //     SIZE,
    // };

    // struct MonsterTypeData
    // {
    //     struct BaseStats
    //     {
    //         static constexpr int iHealth = 100;
    //         static constexpr float fSpeed = 100.f;
    //         static constexpr int iStrength = 10;
    //         static constexpr int iReward = 5;
    //         static constexpr int iWaveStrength = 0;
    //     };

    //     struct Skeleton
    //     {
    //         static constexpr int iHealthDifference = 0;
    //         static constexpr float fSpeedDifference = 0;
    //         static constexpr int iStrengthDifference = 5;
    //         static constexpr int iRewardDifference = 7;
    //         static constexpr int iWaveStrength = 3;
    //     };

    //     struct Reaper
    //     {
    //         static constexpr int iHealthDifference = 25;
    //         static constexpr float fSpeedDifference = 10.f;
    //         static constexpr int iStrengthDifference = 8;
    //         static constexpr int iRewardDifference = 12;
    //         static constexpr int iWaveStrength = 3;
    //     };

    //     struct Golem
    //     {
    //         static constexpr int iHealthDifference = 220;
    //         static constexpr float fSpeedDifference = -40.f;
    //         static constexpr int iStrengthDifference = 20;
    //         static constexpr int iRewardDifference = 13;
    //         static constexpr int iWaveStrength = 2;
    //     };

    //     struct Ogre
    //     {
    //         static constexpr int iHealthDifference = 5;
    //         static constexpr float fSpeedDifference = 5.f;
    //         static constexpr int iStrengthDifference = 4;
    //         static constexpr int iRewardDifference = 9;
    //         static constexpr int iWaveStrength = 4;
    //     };

    //     struct Minotaur
    //     {
    //         static constexpr int iHealthDifference = 80;
    //         static constexpr float fSpeedDifference = 25.f;
    //         static constexpr int iStrengthDifference = 25;
    //         static constexpr int iRewardDifference = 15;
    //         static constexpr int iWaveStrength = 2;
    //     };
    // };

    // struct StatsLevelUpRate
    // {
    //     static constexpr float fHealthLevelUpRate = 1.35f;
    //     static constexpr float fSpeedLevelUpRate = 1.06f;
    //     static constexpr float fStrengthLevelUpRate = 1.10f;
    //     static constexpr float fRewardLevelUpRate = 1.03f;
    // };

    void UpdateMonsterRoster();

    int GetMonsterCountForRound();

    MonsterEntity GenerateMonster();

    //static float GetLevelUpRateAtLevel(int level, float baseRate);

    void UpdateNextRoundMonsterGenerator();

    void InitializeFirstRoaster();

    MonsterGeneratorData::MonsterType GetCurrentMonsterType() const { return m_aCurrentMonsterRoster.back(); }

    MonsterEntity GetNextMonster() const;

private:
    int GetWaveStrength(MonsterGeneratorData::MonsterType currentType);

    

private:
    int m_iBaseMonsters;                                                // Starting monster number
    std::vector<MonsterGeneratorData::MonsterType> m_aCurrentMonsterRoster;             // Store Monster roaster size depend on the size of the Type enum
    std::vector<MonsterGeneratorData::MonsterType> m_aNextMonsterRoster;      
    int m_iMonsterLevel;                                                // Current monster level
};


#endif // MONSTER_GENERATOR_H