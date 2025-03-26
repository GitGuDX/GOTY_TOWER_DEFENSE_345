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