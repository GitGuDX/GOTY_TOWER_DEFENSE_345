#ifndef MONSTER_GENERATOR_H
#define MONSTER_GENERATOR_H

#include <vector>
#include <SFML/Graphics.hpp>

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
    Swarm monster - Speed +3, Health -3, Strength -1, Wave strength +2, reward -3
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

class MonsterGenerator
{
public:
    // Constructor initializes base number of monsters and their increase rate per level
    MonsterGenerator(int baseMonsters, int monsterSpawnRate);

    enum class Type
    {
        Normal, 
        Rogue,
        Tank,
        Swarm,
        Elite
    };

    // Create monster according to their type and level

    // Generate a new monster if needed, pass Game instance as reference
    void generateMonster(Game& game);

private:
    struct BaseStats
    {
        int iLevel = 1;
        int iHealth = 100;
        float fSpeed = 100.f;
        int iStrength = 10;
        int iReward = 20;
    };

    struct StatsLevelUpRate
    {
        float fHealthLevelUpRate = 1.05f;
        float fSpeedLevelUpRate = 1.03f;
        float fStrengthLevelUpRate = 1.03f;
        float fRewardLevelUpRate = 1.02f;
    };

    int m_iBaseMonsters;
    int m_iMonsterSpawnRate;
    int m_iCurrentMonsterIndex;  // To track how many monsters have been generated for this wave
};


#endif
