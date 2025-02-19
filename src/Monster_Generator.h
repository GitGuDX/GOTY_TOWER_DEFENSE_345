/**

@file Monster_Generator.h

@brief Declares the MonsterGenerator class for managing enemy waves.
*/

#ifndef MONSTER_GENERATOR_H
#define MONSTER_GENERATOR_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <vector>

class Game;                             // Forward declare Game class so MonsterGenerator as refernce to what Game type is

/////// ADD more logic for generating monster
/////// Currently, the logic covers how many monsters to generate depending on the current level of the game multiplied by 
/////// the number of base monsters and the monster increase rate. 
/////// Need to also cover what type of monster to generate (high hp, high speed, or both). Possibly through random choice while 
/////// keeping the intigrity of increasing difficulty each level

/*
Base monster stat - Level 1, Health 100, Speed 100.0f, Strength 10, Reward 20

There are ___ classes of monsters
    Normal monster - Speed +0, Health +0, Strength +0, Wave strength +0, reward +0
    Rogue monster - Speed +2, Health -2, Strength +2, Wave strength +0, reward +1
    Tank monster - Speed -2, Health +5, Strength +2, Wave strength -1, reward +3
    Swarm monster - Speed +3, Health -3, Strength -1, Wave strength +3, reward -3
    Elite Monster - Speed +2, Health +4, Strength +3, Wave strength - 3, reward +5
    ... anything else?

For every level increase, all of its stats increase. At the rate of what?
    Let's start with 5% increase in health, 3% increase in speed, 3% increase in strength, and 2% increase in reward.
Each wave will consist of only one class ... for now.
All classes of monster of the same level must have been spawned before the next level monsters are introduced
The order of waves based on class can be randomized.
E.g.) 
    wave 1 (Average - lvl 1) -> wave 2 (Tank - lvl 1) -> wave 3 (Rogue - lvl 1) -> wave 4 (Swarm - lvl 1) ->
    wave 5 (Tank - lvl 2) -> wave 6 (Swarm - lvl 2) -> wave 7 (Rogue - lvl 2) -> wave 8 (Average - lvl 2) -> etc.
*/

class Monster;          // Forward declaration to know what Monster class is

class MonsterGenerator
{
public:
    // Constructor initializes base number of monsters and their increase rate per level
    MonsterGenerator(int baseMonsters);

    enum class Type
    {
        Skeleton,
        Reaper,
        Golem,
        Minotaur,
        Ogre,
        SIZE,
    };

    
    // Generate a new monster if needed, pass Game instance as reference
    void generateMonster(Game& game);
    void updateNextRoundMonsterGenerator();

    float getTimeSinceLastGeneration()
    {
        return m_fTimeSinceLastGeneration;
    }
    float getGenerationCoolDown()
    {
        return m_fGenerationCooldown;
    }
    bool getIsAllMonstersSpawned()
    {
        return isAllMonstersSpawned;
    }
    bool hasPassedGenerationCoolDown()
    {
        return m_fTimeSinceLastGeneration >= m_fGenerationCooldown;
    }

    void resetTimeSinceLastGeneration()
    {
        m_fTimeSinceLastGeneration = 0.f;
    }
    void incrementTimeSinceLastGeneration(float addedTime)
    {
        m_fTimeSinceLastGeneration += addedTime;
    }
    

private:
    void updateMonsterRoster();
    template <Type type>
    void updateMonsterStats(Monster& monster);
    int getWaveStrength(MonsterGenerator::Type currentType);
    float getLevelUpRateAtLevel(int level, float baseRate);

private:
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

    int m_iBaseMonsters;                                                // Starting monster number
    int m_iNumberOfMonsterSpawned;                                         // To track how many monsters have been generated for this wave
    int m_iMonsterLevel;                                                // Current monster level
    std::vector<Type> m_aCurrentMonsterRoaster;             // Store Monster roaster size depend on the size of the Type enum
    float m_fTimeSinceLastGeneration = 0.f;                 // Time elapsed since the last monster was generated
    const float m_fGenerationCooldown = 0.5f;               // The cooldown time (in seconds) between monster generations
    bool isAllMonstersSpawned = false;
};


#endif
