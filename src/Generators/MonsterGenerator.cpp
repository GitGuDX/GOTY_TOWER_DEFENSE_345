#include "MonsterGenerator.h"
#include "../Entities/MonsterEntity.h"

MonsterGenerator::MonsterGenerator()
    : m_iBaseMonsters(3)
{
}

/**
 * @brief Updates the monster roster for the next round of spawning.
 * 
 * This function updates the list of monsters to be spawned in the next round. Initially, the roster
 * is cleared, and then refilled with a predefined set of monster types (Ogre, Minotaur, Golem, Reaper, Skeleton).
 * The roster is randomized using the Fisher-Yates shuffle to ensure varied monster types each round.
 * 
 * @note The monster types for each round follow the order specified in the vector `m_aCurrentMonsterRoaster`.
 *       Once all the monsters from the current roster have been spawned, a new randomized roster is created.
 * 
 * @see std::shuffle() for randomizing the roster using Fisher-Yates.
 */
void MonsterGenerator::UpdateMonsterRoster()
{
    // There will be only one type of monster spawned each round
    // Types of monsters spwaned for each round follows the order (from right to left) of monster types in m_aCurrentMonsterRoaster
    // Once the monster
    // Once m_aCurrentMonsterRoaster is empty, it is time to use a new monster roster that is randomized

    // first make sure the vector is empty
    m_aNextMonsterRoster.clear();

    // Refill m_aCurrentMonsterRoaster
    m_aNextMonsterRoster = {MonsterGeneratorData::MonsterType::Ogre, MonsterGeneratorData::MonsterType::Minotaur, MonsterGeneratorData::MonsterType::Golem, MonsterGeneratorData::MonsterType::Reaper, MonsterGeneratorData::MonsterType::Skeleton};

    // To randomize monster roster, use Fisher-Yates shuffle on m_aCurrentMonsterRoaster
    // Set up random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Shuffle the enum vector
    std::shuffle(m_aNextMonsterRoster.begin(), m_aNextMonsterRoster.end(), gen);
}

MonsterEntity MonsterGenerator::GenerateMonster()
{
    // Initialize a new monster class
    return MonsterEntity(m_aCurrentMonsterRoster.back(), m_iMonsterLevel);
}

MonsterEntity MonsterGenerator::GetNextMonster() const
{
    if (m_aCurrentMonsterRoster.size() > 1)
    {
        return MonsterEntity(m_aCurrentMonsterRoster[m_aCurrentMonsterRoster.size() - 2], m_iMonsterLevel);
    }
    else
    {
        return MonsterEntity(m_aNextMonsterRoster.back(), m_iMonsterLevel + 1);
    }
}

MonsterEntity MonsterGenerator::GetCurrentMonster() const
{
    if (!m_aCurrentMonsterRoster.empty())
    {
        return MonsterEntity(m_aCurrentMonsterRoster.back(), m_iMonsterLevel);
    }
    else
    {
        return MonsterEntity(m_aNextMonsterRoster.back(), m_iMonsterLevel);
    }
}

int MonsterGenerator::GetWaveStrength(MonsterGeneratorData::MonsterType currentType)
{
    int waveStrength = 0;
    switch (currentType)
    {
        case MonsterGeneratorData::MonsterType::Skeleton:
            waveStrength = MonsterGeneratorData::MonsterTypeData::Skeleton::iWaveStrength;
            break;
        case MonsterGeneratorData::MonsterType::Reaper:
            waveStrength = MonsterGeneratorData::MonsterTypeData::Reaper::iWaveStrength;
            break;
        case MonsterGeneratorData::MonsterType::Golem:
            waveStrength = MonsterGeneratorData::MonsterTypeData::Golem::iWaveStrength;
            break;
        case MonsterGeneratorData::MonsterType::Minotaur:
            waveStrength = MonsterGeneratorData::MonsterTypeData::Minotaur::iWaveStrength;
            break;
        case MonsterGeneratorData::MonsterType::Ogre:
            waveStrength = MonsterGeneratorData::MonsterTypeData::Ogre::iWaveStrength;
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
    MonsterGeneratorData::MonsterType currentType = m_aCurrentMonsterRoster.back();

    int waveStrength = GetWaveStrength(currentType);
    //std::cout << "Wave strength: " << waveStrength << '\n';
    // Game balance: change 1 in pow to be dependent on a game difficulty setting ie. m_iMonsterLevel
    return m_iBaseMonsters + std::pow(1, 1.2) * waveStrength;
}

/**
 * @brief Updates the monster generator for the next round of spawning.
 * 
 * This function updates the current monster roster by removing the last spawned monster type. If only one
 * monster type remains in the roster, it refills the next roster using `UpdateMonsterRoster`. If all the monster
 * types have been played, the roster is swapped with the new roster, and the monster level is incremented.
 * 
 * @note This function ensures that the monster types are cycled through and increases the monster level after each full roster.
 */
void MonsterGenerator::UpdateNextRoundMonsterGenerator()
{
    //std::cout << "Preparing next round of monsters\n";
    // remove the last monster type that has been played form the roster
    m_aCurrentMonsterRoster.pop_back();

    // If only one monster type is left in the roster, refill the next roster
    if (m_aCurrentMonsterRoster.size() == 1)
    {
        UpdateMonsterRoster();
    }
    // If all monster types in the roster have been played, refill roster
    else if (m_aCurrentMonsterRoster.empty())
    {
        //std::cout << "Monster roster updated\n";
        //Increase monster level after every roster
        m_iMonsterLevel += 1;
        m_aCurrentMonsterRoster.swap(m_aNextMonsterRoster);
    }

}

void MonsterGenerator::InitializeFirstRoaster()
{
    m_iMonsterLevel = 0;
    m_aNextMonsterRoster.clear();
    m_aCurrentMonsterRoster.clear();
    m_aCurrentMonsterRoster = {MonsterGeneratorData::MonsterType::Ogre, MonsterGeneratorData::MonsterType::Minotaur, MonsterGeneratorData::MonsterType::Golem, MonsterGeneratorData::MonsterType::Reaper, MonsterGeneratorData::MonsterType::Skeleton};
}
