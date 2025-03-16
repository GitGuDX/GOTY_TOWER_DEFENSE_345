#include "MonsterGenerator.h"
#include "../Entities/MonsterEntity.h"

MonsterGenerator::MonsterGenerator()
    : m_iBaseMonsters(3)
    , m_aCurrentMonsterRoaster{MonsterType::Minotaur, MonsterType::Golem, MonsterType::Reaper, MonsterType::Ogre, MonsterType::Skeleton}
    , m_iMonsterLevel(0)
{
}

// Update monster roster when all types of monster have spawned
void MonsterGenerator::UpdateMonsterRoster()
{
    // There will be only one type of monster spawned each round
    // Types of monsters spwaned for each round follows the order (from right to left) of monster types in m_aCurrentMonsterRoaster
    // Once the monster
    // Once m_aCurrentMonsterRoaster is empty, it is time to use a new monster roster that is randomized

    // first make sure the vector is empty
    m_aCurrentMonsterRoaster.clear();

    // Refill m_aCurrentMonsterRoaster
    m_aCurrentMonsterRoaster = {MonsterType::Ogre, MonsterType::Minotaur, MonsterType::Golem, MonsterType::Reaper, MonsterType::Skeleton};

    // To randomize monster roster, use Fisher-Yates shuffle on m_aCurrentMonsterRoaster
    // Set up random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Shuffle the enum vector
    std::shuffle(m_aCurrentMonsterRoaster.begin(), m_aCurrentMonsterRoaster.end(), gen);
}

MonsterEntity MonsterGenerator::GenerateMonster()
{
    // Initialize a new monster class
    return MonsterEntity(m_aCurrentMonsterRoaster.back(), m_iMonsterLevel);
}

int MonsterGenerator::GetWaveStrength(MonsterGenerator::MonsterType currentType)
{
    int waveStrength = 0;
    switch (currentType)
    {
        case MonsterType::Skeleton:
            waveStrength = MonsterTypeData::Skeleton::iWaveStrength;
            break;
        case MonsterType::Reaper:
            waveStrength = MonsterTypeData::Reaper::iWaveStrength;
            break;
        case MonsterType::Golem:
            waveStrength = MonsterTypeData::Golem::iWaveStrength;
            break;
        case MonsterType::Minotaur:
            waveStrength = MonsterTypeData::Minotaur::iWaveStrength;
            break;
        case MonsterType::Ogre:
            waveStrength = MonsterTypeData::Ogre::iWaveStrength;
            break;
        default:
            waveStrength = 0; // Default case, shouldn't happen, but just in case.
            break;
    }
    return waveStrength;
}

// Calculate how many monsters to spawn on this round depending on the monster level and its spawn rate
int MonsterGenerator::GetMonsterCountForRound()
{
    MonsterGenerator::MonsterType currentType = m_aCurrentMonsterRoaster.back();

    int waveStrength = GetWaveStrength(currentType);
    std::cout << "Wave strength: " << waveStrength << '\n';
    // Game balance: change 1 in pow to be dependent on a game difficulty setting ie. m_iMonsterLevel
    return m_iBaseMonsters + std::pow(1, 1.2) * waveStrength;
}

float MonsterGenerator::GetLevelUpRateAtLevel(int level, float baseRate)
{
    return baseRate * std::pow(1.1f, level - 1); // Assuming a 10% increase per level.
}

void MonsterGenerator::UpdateNextRoundMonsterGenerator()
{
    //std::cout << "Preparing next round of monsters\n";
    // remove the last monster type that has been played form the roster
    m_aCurrentMonsterRoaster.pop_back();
    // Reset number of monster spawned
    // m_iNumberOfMonsterSpawned = 0;
    // Reset all monsters spawned flag
    //isAllMonstersSpawned = false;

    // If all monster types in the roster have been played, refill roster
    if (m_aCurrentMonsterRoaster.empty())
    {
        //std::cout << "Monster roster updated\n";
        //Increase monster level after every roster
        m_iMonsterLevel += 1;
        UpdateMonsterRoster();
    }

}