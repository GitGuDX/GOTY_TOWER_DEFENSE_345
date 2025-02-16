// Include Game.h so that Monster_Generator.cpp has full definition of Game
// The reason for including Game.h here and not in Monster_Generator.h is because
// Game.h already includes Monster_Generator.h and if Monster_Generator.h includes Game.h, this presents circular dependency.
// Circular dependency means neither files can be fully defined without the other.
// Now, .cpp files are compiled individually, so having the Game.h included here and not in the .h file avoids circular dependencies.
#include "Game.h"                          
#include "Monster_Generator.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

MonsterGenerator::MonsterGenerator(int baseMonsters)
    : m_iBaseMonsters(baseMonsters)
    , m_iNumberOfMonsterSpawned(0)
    , m_iMonsterLevel(0)                                                                            // Set initial monster level
    // Set initial monster roaster to teach players about the types of monster 
    , m_aCurrentMonsterRoaster{Type::Elite, Type::Swarm, Type::Tank, Type::Rogue, Type::Normal}        
{
}

// Update monster roster when all types of monster have spawned
void MonsterGenerator::updateMonsterRoster()
{
    // There will be only one type of monster spawned each round
    // Types of monsters spwaned for each round follows the order (from right to left) of monster types in m_aCurrentMonsterRoaster
    // Once the monster
    // Once m_aCurrentMonsterRoaster is empty, it is time to use a new monster roster that is randomized

    // first make sure the vector is empty
    m_aCurrentMonsterRoaster.clear();

    // Refill m_aCurrentMonsterRoaster
    m_aCurrentMonsterRoaster = {Type::Elite, Type::Swarm, Type::Tank, Type::Rogue, Type::Normal};

    // To randomize monster roster, use Fisher-Yates shuffle on m_aCurrentMonsterRoaster
    // Set up random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Shuffle the enum vector
    std::shuffle(m_aCurrentMonsterRoaster.begin(), m_aCurrentMonsterRoaster.end(), gen);
}

template <MonsterGenerator::Type type>
void MonsterGenerator::updateMonsterStats(Monster& monster)
{
    if (type == MonsterGenerator::Type::Normal) {
        monster.SetSpeed(MonsterGenerator::MonsterTypeData::BaseStats::fSpeed + MonsterGenerator::MonsterTypeData::Normal::fSpeedDifference);
        monster.SetHealth(MonsterGenerator::MonsterTypeData::BaseStats::iHealth + MonsterGenerator::MonsterTypeData::Normal::iHealthDifference);
        monster.SetStrength(MonsterGenerator::MonsterTypeData::BaseStats::iStrength + MonsterGenerator::MonsterTypeData::Normal::iStrengthDifference);
        monster.SetReward(MonsterGenerator::MonsterTypeData::BaseStats::iReward + MonsterGenerator::MonsterTypeData::Normal::iRewardDifference);
    }
    else if (type == MonsterGenerator::Type::Rogue) {
        monster.SetSpeed(MonsterGenerator::MonsterTypeData::BaseStats::fSpeed + MonsterGenerator::MonsterTypeData::Rogue::fSpeedDifference);
        monster.SetHealth(MonsterGenerator::MonsterTypeData::BaseStats::iHealth + MonsterGenerator::MonsterTypeData::Rogue::iHealthDifference);
        monster.SetStrength(MonsterGenerator::MonsterTypeData::BaseStats::iStrength + MonsterGenerator::MonsterTypeData::Rogue::iStrengthDifference);
        monster.SetReward(MonsterGenerator::MonsterTypeData::BaseStats::iReward + MonsterGenerator::MonsterTypeData::Rogue::iRewardDifference);
    }
    else if (type == MonsterGenerator::Type::Tank) {
        monster.SetSpeed(MonsterGenerator::MonsterTypeData::BaseStats::fSpeed + MonsterGenerator::MonsterTypeData::Tank::fSpeedDifference);
        monster.SetHealth(MonsterGenerator::MonsterTypeData::BaseStats::iHealth + MonsterGenerator::MonsterTypeData::Tank::iHealthDifference);
        monster.SetStrength(MonsterGenerator::MonsterTypeData::BaseStats::iStrength + MonsterGenerator::MonsterTypeData::Tank::iStrengthDifference);
        monster.SetReward(MonsterGenerator::MonsterTypeData::BaseStats::iReward + MonsterGenerator::MonsterTypeData::Tank::iRewardDifference);
    }
    else if (type == MonsterGenerator::Type::Swarm) {
        monster.SetSpeed(MonsterGenerator::MonsterTypeData::BaseStats::fSpeed + MonsterGenerator::MonsterTypeData::Swarm::fSpeedDifference);
        monster.SetHealth(MonsterGenerator::MonsterTypeData::BaseStats::iHealth + MonsterGenerator::MonsterTypeData::Swarm::iHealthDifference);
        monster.SetStrength(MonsterGenerator::MonsterTypeData::BaseStats::iStrength + MonsterGenerator::MonsterTypeData::Swarm::iStrengthDifference);
        monster.SetReward(MonsterGenerator::MonsterTypeData::BaseStats::iReward + MonsterGenerator::MonsterTypeData::Swarm::iRewardDifference);
    }
    else if (type == MonsterGenerator::Type::Elite) {
        monster.SetSpeed(MonsterGenerator::MonsterTypeData::BaseStats::fSpeed + MonsterGenerator::MonsterTypeData::Elite::fSpeedDifference);
        monster.SetHealth(MonsterGenerator::MonsterTypeData::BaseStats::iHealth + MonsterGenerator::MonsterTypeData::Elite::iHealthDifference);
        monster.SetStrength(MonsterGenerator::MonsterTypeData::BaseStats::iStrength + MonsterGenerator::MonsterTypeData::Elite::iStrengthDifference);
        monster.SetReward(MonsterGenerator::MonsterTypeData::BaseStats::iReward + MonsterGenerator::MonsterTypeData::Elite::iRewardDifference);
    }
}

int MonsterGenerator::getWaveStrength(MonsterGenerator::Type currentType)
{
    int waveStrength = 0;
    switch (currentType)
    {
        case Type::Normal:
            waveStrength = MonsterTypeData::Normal::iWaveStrength;
            break;
        case Type::Rogue:
            waveStrength = MonsterTypeData::Rogue::iWaveStrength;
            break;
        case Type::Tank:
            waveStrength = MonsterTypeData::Tank::iWaveStrength;
            break;
        case Type::Swarm:
            waveStrength = MonsterTypeData::Swarm::iWaveStrength;
            break;
        case Type::Elite:
            waveStrength = MonsterTypeData::Elite::iWaveStrength;
            break;
        default:
            waveStrength = 0; // Default case, shouldn't happen, but just in case.
            break;
    }
    return waveStrength;
}

// Pass Game by refrence and since MonsterGenerator class is a friend of Game class, it has access to all Game class's private members
void MonsterGenerator::generateMonster(Game& game)          
{
    ////////////////FOR TESTING///////////////
    // std::cout << m_aCurrentMonsterRoaster.size() <<'\n';
    // updateMonsterRoster();
    // for (Type type : m_aCurrentMonsterRoaster)
    // {
    //     std::cout << static_cast<int>(type) << '\n';
    // }
    ///////////////////////////////////////////

    /////// Logic for generating monsters according to the game level

    // Get the current monster type from the roster
    MonsterGenerator::Type currentType = m_aCurrentMonsterRoaster.back();
    std::cout << "Current monster type is " << static_cast<int>(currentType) << '\n';
    std::cout << "Roster size is " << m_aCurrentMonsterRoaster.size() << '\n';
    // Get the total number of monster to be spawned depending on the monster level and its spawn rate depanding on its type
    int waveStrength = getWaveStrength(currentType);
    int numMonsters = m_iBaseMonsters + std::pow(1, 1.2) * waveStrength;
    std::cout << "num of monster to be spawned are " << numMonsters << '\n';

    // Check if we have any monsters left to spawn then generate a monster if true
    if (m_iNumberOfMonsterSpawned < numMonsters) {
        // Initialize a new monster class
        Monster newMonster;
        // Set universal properties
        newMonster.SetScale(sf::Vector2f(0.06f, 0.06f));

        switch (currentType)
        {
        case Type::Normal:
        {
            newMonster.SetTexture(game.m_MonsterTexture);
            updateMonsterStats<Type::Normal>(newMonster);                     // Set monster stat accoring to its type
            break;
        }
        case Type::Rogue:
        {
            newMonster.SetTexture(game.m_MonsterTexture);
            updateMonsterStats<Type::Rogue>(newMonster);                     // Set monster stat accoring to its type
            break;
        }
        case Type::Tank:
        {
            newMonster.SetTexture(game.m_MonsterTexture);
            updateMonsterStats<Type::Tank>(newMonster);                     // Set monster stat accoring to its type
            break;
        }
        case Type::Swarm:
        {
            newMonster.SetTexture(game.m_MonsterTexture);
            updateMonsterStats<Type::Swarm>(newMonster);                     // Set monster stat accoring to its type
            break;
        }
        case Type::Elite:
        {
            newMonster.SetTexture(game.m_MonsterTexture);
            updateMonsterStats<Type::Elite>(newMonster);                     // Set monster stat accoring to its type
            break;
        }
        default:
            break;    
        }

        FloatRect monsterSize = newMonster.m_Sprite.getLocalBounds();                           // Get Monster sprite width and height
        newMonster.SetOrigin(sf::Vector2f(monsterSize.width / 2, monsterSize.height / 2));      // Set Monster anchor to the center of the sprite
        newMonster.SetPosition(game.m_vEntryTile);                                              // Set test monster's starting position to the entry tile
        newMonster.SetCurrentPathIndex(0);                                                      // Initiliaze Monster's current path index

        game.m_aMonstersQueue.emplace_back(newMonster);                 // Add the newly created monster to the monster array
        m_iNumberOfMonsterSpawned++;                                    // Count how many monsters created
    }
}

void MonsterGenerator::updateNextRoundMonsterGenerator()
{
    std::cout << "Preparing next round of monsters\n";
    // remove the last monster type that has been played form the roster
    m_aCurrentMonsterRoaster.pop_back();
    // Reset number of monster spawned
    m_iNumberOfMonsterSpawned = 0;

    // If all monster types in the roster have been played, refill roster
    if (m_aCurrentMonsterRoaster.empty())
    {
        std::cout << "Monster roster updated\n";
        //Increase monster level after every roster
        m_iMonsterLevel += 1;
        updateMonsterRoster();
    }

    // 
}
