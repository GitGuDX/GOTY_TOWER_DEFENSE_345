#ifndef MONSTER_GENERATOR_DATA_H
#define MONSTER_GENERATOR_DATA_H

/**
 * @namespace MonsterGeneratorData
 * @brief Contains data related to monster types and their stats in the game.
 * 
 * This namespace defines enumerations and structures for different types of monsters, their base stats, and
 * how they evolve as they level up. It includes:
 * - `MonsterType`: An enumeration representing the different types of monsters.
 * - `MonsterTypeData`: A structure containing nested structures for each monster type with their specific stats.
 * - `StatsLevelUpRate`: A structure that defines the level-up rate for different stats like health, speed, strength, and reward.
 * 
 * @note The `MonsterTypeData` structure defines base stats for all monster types as well as differences in stats 
 * specific to each monster type, including health, speed, strength, reward, and wave strength.
 */
namespace MonsterGeneratorData {  // Renamed namespace to TowerGeneratorData
    enum class MonsterType
    {
        Skeleton,
        Reaper,
        Golem,
        Minotaur,
        Ogre,
        SIZE,
    };

    struct MonsterTypeData
    {
        struct BaseStats
        {
            static constexpr int iHealth = 100;
            static constexpr float fSpeed = 100.f;
            static constexpr int iStrength = 10;
            static constexpr int iReward = 5;
            static constexpr int iWaveStrength = 0;
        };

        struct Skeleton
        {
            static constexpr int iHealthDifference = 0;
            static constexpr float fSpeedDifference = 0;
            static constexpr int iStrengthDifference = 5;
            static constexpr int iRewardDifference = 7;
            static constexpr int iWaveStrength = 3;
        };

        struct Reaper
        {
            static constexpr int iHealthDifference = 25;
            static constexpr float fSpeedDifference = 10.f;
            static constexpr int iStrengthDifference = 8;
            static constexpr int iRewardDifference = 12;
            static constexpr int iWaveStrength = 3;
        };

        struct Golem
        {
            static constexpr int iHealthDifference = 220;
            static constexpr float fSpeedDifference = -40.f;
            static constexpr int iStrengthDifference = 20;
            static constexpr int iRewardDifference = 13;
            static constexpr int iWaveStrength = 2;
        };

        struct Ogre
        {
            static constexpr int iHealthDifference = 5;
            static constexpr float fSpeedDifference = 5.f;
            static constexpr int iStrengthDifference = 4;
            static constexpr int iRewardDifference = 9;
            static constexpr int iWaveStrength = 4;
        };

        struct Minotaur
        {
            static constexpr int iHealthDifference = 80;
            static constexpr float fSpeedDifference = 25.f;
            static constexpr int iStrengthDifference = 25;
            static constexpr int iRewardDifference = 15;
            static constexpr int iWaveStrength = 2;
        };
    };

    struct StatsLevelUpRate
    {
        static constexpr float fHealthLevelUpRate = 1.35f;
        static constexpr float fSpeedLevelUpRate = 1.06f;
        static constexpr float fStrengthLevelUpRate = 1.10f;
        static constexpr float fRewardLevelUpRate = 1.03f;
    };

}

#endif // MONSTER_GENERATOR_DATA_H