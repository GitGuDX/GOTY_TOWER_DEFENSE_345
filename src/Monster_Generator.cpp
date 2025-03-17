// /**

// @file Monster_Generator.cpp

// @brief Implements monster spawning and wave progression.
// */

// // Include Game.h so that Monster_Generator.cpp has full definition of Game
// // The reason for including Game.h here and not in Monster_Generator.h is because
// // Game.h already includes Monster_Generator.h and if Monster_Generator.h includes Game.h, this presents circular dependency.
// // Circular dependency means neither files can be fully defined without the other.
// // Now, .cpp files are compiled individually, so having the Game.h included here and not in the .h file avoids circular dependencies.
// #include "Game.h"
// #include "Monster_Generator.h"
// #include <iostream>
// #include <vector>
// #include <random>
// #include <algorithm>

// Monster_Generator::Monster_Generator(int baseMonsters, MonsterView& monsterView)
//     : m_iBaseMonsters(baseMonsters)
//     , m_iNumberOfMonsterSpawned(0)
//     , m_iMonsterLevel(0)                                                                            // Set initial monster level
//     // Set initial monster roaster to teach players about the types of monster 
//     , m_aCurrentMonsterRoaster{Type::Minotaur, Type::Golem, Type::Reaper, Type::Ogre, Type::Skeleton}
//     , m_MonsterView(monsterView)        
// {
// }

// // Update monster roster when all types of monster have spawned
// void Monster_Generator::updateMonsterRoster()
// {
//     // There will be only one type of monster spawned each round
//     // Types of monsters spwaned for each round follows the order (from right to left) of monster types in m_aCurrentMonsterRoaster
//     // Once the monster
//     // Once m_aCurrentMonsterRoaster is empty, it is time to use a new monster roster that is randomized

//     // first make sure the vector is empty
//     m_aCurrentMonsterRoaster.clear();

//     // Refill m_aCurrentMonsterRoaster
//     m_aCurrentMonsterRoaster = {Type::Ogre, Type::Minotaur, Type::Golem, Type::Reaper, Type::Skeleton};

//     // To randomize monster roster, use Fisher-Yates shuffle on m_aCurrentMonsterRoaster
//     // Set up random number generator
//     std::random_device rd;
//     std::mt19937 gen(rd());

//     // Shuffle the enum vector
//     std::shuffle(m_aCurrentMonsterRoaster.begin(), m_aCurrentMonsterRoaster.end(), gen);
// }

// template <Monster_Generator::Type type>
// void Monster_Generator::updateMonsterStats(Monster& monster)
// {
//     if (type == Monster_Generator::Type::Skeleton) {
//         monster.SetSpeed((Monster_Generator::MonsterTypeData::BaseStats::fSpeed + Monster_Generator::MonsterTypeData::Skeleton::fSpeedDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fSpeedLevelUpRate));
//         monster.SetHealth((Monster_Generator::MonsterTypeData::BaseStats::iHealth + Monster_Generator::MonsterTypeData::Skeleton::iHealthDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fHealthLevelUpRate));
//         monster.SetMaxHealth((Monster_Generator::MonsterTypeData::BaseStats::iHealth + Monster_Generator::MonsterTypeData::Skeleton::iHealthDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fHealthLevelUpRate));
//         monster.SetStrength((Monster_Generator::MonsterTypeData::BaseStats::iStrength + Monster_Generator::MonsterTypeData::Skeleton::iStrengthDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fStrengthLevelUpRate));
//         monster.SetReward((Monster_Generator::MonsterTypeData::BaseStats::iReward + Monster_Generator::MonsterTypeData::Skeleton::iRewardDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fRewardLevelUpRate));
//     }
//     else if (type == Monster_Generator::Type::Reaper) {
//         monster.SetSpeed((Monster_Generator::MonsterTypeData::BaseStats::fSpeed + Monster_Generator::MonsterTypeData::Reaper::fSpeedDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fSpeedLevelUpRate));
//         monster.SetHealth((Monster_Generator::MonsterTypeData::BaseStats::iHealth + Monster_Generator::MonsterTypeData::Reaper::iHealthDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fHealthLevelUpRate));
//         monster.SetMaxHealth((Monster_Generator::MonsterTypeData::BaseStats::iHealth + Monster_Generator::MonsterTypeData::Reaper::iHealthDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fHealthLevelUpRate));
//         monster.SetStrength((Monster_Generator::MonsterTypeData::BaseStats::iStrength + Monster_Generator::MonsterTypeData::Reaper::iStrengthDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fStrengthLevelUpRate));
//         monster.SetReward((Monster_Generator::MonsterTypeData::BaseStats::iReward + Monster_Generator::MonsterTypeData::Reaper::iRewardDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fRewardLevelUpRate));
//     }
//     else if (type == Monster_Generator::Type::Golem) {
//         monster.SetSpeed((Monster_Generator::MonsterTypeData::BaseStats::fSpeed + Monster_Generator::MonsterTypeData::Golem::fSpeedDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fSpeedLevelUpRate));
//         monster.SetHealth((Monster_Generator::MonsterTypeData::BaseStats::iHealth + Monster_Generator::MonsterTypeData::Golem::iHealthDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fHealthLevelUpRate));
//         monster.SetMaxHealth((Monster_Generator::MonsterTypeData::BaseStats::iHealth + Monster_Generator::MonsterTypeData::Golem::iHealthDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fHealthLevelUpRate));
//         monster.SetStrength((Monster_Generator::MonsterTypeData::BaseStats::iStrength + Monster_Generator::MonsterTypeData::Golem::iStrengthDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fStrengthLevelUpRate));
//         monster.SetReward((Monster_Generator::MonsterTypeData::BaseStats::iReward + Monster_Generator::MonsterTypeData::Golem::iRewardDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fRewardLevelUpRate));
//     }
//     else if (type == Monster_Generator::Type::Minotaur) {
//         monster.SetSpeed((Monster_Generator::MonsterTypeData::BaseStats::fSpeed + Monster_Generator::MonsterTypeData::Minotaur::fSpeedDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fSpeedLevelUpRate));
//         monster.SetHealth((Monster_Generator::MonsterTypeData::BaseStats::iHealth + Monster_Generator::MonsterTypeData::Minotaur::iHealthDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fHealthLevelUpRate));
//         monster.SetMaxHealth((Monster_Generator::MonsterTypeData::BaseStats::iHealth + Monster_Generator::MonsterTypeData::Minotaur::iHealthDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fHealthLevelUpRate));
//         monster.SetStrength((Monster_Generator::MonsterTypeData::BaseStats::iStrength + Monster_Generator::MonsterTypeData::Minotaur::iStrengthDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fStrengthLevelUpRate));
//         monster.SetReward((Monster_Generator::MonsterTypeData::BaseStats::iReward + Monster_Generator::MonsterTypeData::Minotaur::iRewardDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fRewardLevelUpRate));
//     }
//     else if (type == Monster_Generator::Type::Ogre) {
//         monster.SetSpeed((Monster_Generator::MonsterTypeData::BaseStats::fSpeed + Monster_Generator::MonsterTypeData::Ogre::fSpeedDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fSpeedLevelUpRate));
//         monster.SetHealth((Monster_Generator::MonsterTypeData::BaseStats::iHealth + Monster_Generator::MonsterTypeData::Ogre::iHealthDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fHealthLevelUpRate));
//         monster.SetMaxHealth((Monster_Generator::MonsterTypeData::BaseStats::iHealth + Monster_Generator::MonsterTypeData::Ogre::iHealthDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fHealthLevelUpRate));
//         monster.SetStrength((Monster_Generator::MonsterTypeData::BaseStats::iStrength + Monster_Generator::MonsterTypeData::Ogre::iStrengthDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fStrengthLevelUpRate));
//         monster.SetReward((Monster_Generator::MonsterTypeData::BaseStats::iReward + Monster_Generator::MonsterTypeData::Ogre::iRewardDifference)*getLevelUpRateAtLevel(m_iMonsterLevel, Monster_Generator::StatsLevelUpRate::fRewardLevelUpRate));
//     }
//     m_MonsterView.Update(monster);
// }

// int Monster_Generator::getWaveStrength(Monster_Generator::Type currentType)
// {
//     int waveStrength = 0;
//     switch (currentType)
//     {
//         case Type::Skeleton:
//             waveStrength = MonsterTypeData::Skeleton::iWaveStrength;
//             break;
//         case Type::Reaper:
//             waveStrength = MonsterTypeData::Reaper::iWaveStrength;
//             break;
//         case Type::Golem:
//             waveStrength = MonsterTypeData::Golem::iWaveStrength;
//             break;
//         case Type::Minotaur:
//             waveStrength = MonsterTypeData::Minotaur::iWaveStrength;
//             break;
//         case Type::Ogre:
//             waveStrength = MonsterTypeData::Ogre::iWaveStrength;
//             break;
//         default:
//             waveStrength = 0; // Default case, shouldn't happen, but just in case.
//             break;
//     }
//     return waveStrength;
// }

// // Pass Game by refrence and since MonsterGenerator class is a friend of Game class, it has access to all Game class's private members
// void Monster_Generator::generateMonster(Game& game)
// {
//     ////////////////FOR TESTING///////////////
//     // std::cout << m_aCurrentMonsterRoaster.size() <<'\n';
//     // updateMonsterRoster();
//     // for (Type type : m_aCurrentMonsterRoaster)
//     // {
//     //     std::cout << static_cast<int>(type) << '\n';
//     // }
//     ///////////////////////////////////////////

//     /////// Logic for generating monsters according to the game level

//     // Get the current monster type from the roster
//     Monster_Generator::Type currentType = m_aCurrentMonsterRoaster.back();
//     //std::cout << "Current monster type is " << static_cast<int>(currentType) << '\n';
//     //std::cout << "Roster size is " << m_aCurrentMonsterRoaster.size() << '\n';
//     // Get the total number of monster to be spawned depending on the monster level and its spawn rate depanding on its type
//     int waveStrength = getWaveStrength(currentType);
//     int numMonsters = m_iBaseMonsters + std::pow(1, 1.2) * waveStrength;
//     //std::cout << "num of monster to be spawned are " << numMonsters << '\n';

//     // Check if we have any monsters left to spawn then generate a monster if true
//     if (m_iNumberOfMonsterSpawned < numMonsters) {
//         // Initialize a new monster class
//         Monster newMonster;
//         // Set universal properties


//         switch (currentType)
//         {
//         case Type::Skeleton:
//         {
//             newMonster.SetMonsterType(Type::Skeleton);                         // Set monster type
//             updateMonsterStats<Type::Skeleton>(newMonster);                     // Set monster stat accoring to its type
//             break;
//         }
//         case Type::Reaper:
//         {
//             newMonster.SetMonsterType(Type::Reaper);
//             updateMonsterStats<Type::Reaper>(newMonster);                     // Set monster stat accoring to its type
//             break;
//         }
//         case Type::Golem:
//         {
//             newMonster.SetMonsterType(Type::Golem);
//             updateMonsterStats<Type::Golem>(newMonster);                     // Set monster stat accoring to its type
//             break;
//         }
//         case Type::Minotaur:
//         {
//             newMonster.SetMonsterType(Type::Minotaur);
//             updateMonsterStats<Type::Minotaur>(newMonster);                     // Set monster stat accoring to its type
//             break;
//         }
//         case Type::Ogre:
//         {
//             newMonster.SetMonsterType(Type::Ogre);
//             updateMonsterStats<Type::Ogre>(newMonster);                     // Set monster stat accoring to its type
//             break;
//         }
//         default:
//             break;
//         }
//         //newMonster.SetPosition(game.m_vEntryTile);                                              // Set test monster's starting position to the entry tile
//         newMonster.SetPosition(game.m_GUIManager.GetMapSetup()->GetEntryTile()); 
//         newMonster.SetCurrentPathIndex(0);                                                      // Initiliaze Monster's current path index

//         game.m_aMonstersQueue.emplace_back(newMonster);                 // Add the newly created monster to the monster array
//         m_iNumberOfMonsterSpawned++;                                    // Count how many monsters created

//         // std::cout << "monster health is: " << newMonster.GetHealth() << '\n';
//         // std::cout << "monster speed is: " << newMonster.GetSpeed() << '\n';
//         // std::cout << "monster strength is: " << newMonster.GetStrength() << '\n';
//         // std::cout << "monster reward is: " << newMonster.GetReward() << '\n';
//         // std::cout << "monster level is: " << m_iMonsterLevel << '\n';
//         // Check if all monsters have spawned for this wave
//         if (m_iNumberOfMonsterSpawned == numMonsters)
//         {
//             isAllMonstersSpawned = true;
//         }
//     }
// }

// void Monster_Generator::updateNextRoundMonsterGenerator()
// {
//     //std::cout << "Preparing next round of monsters\n";
//     // remove the last monster type that has been played form the roster
//     m_aCurrentMonsterRoaster.pop_back();
//     // Reset number of monster spawned
//     m_iNumberOfMonsterSpawned = 0;
//     // Reset all monsters spawned flag
//     isAllMonstersSpawned = false;

//     // If all monster types in the roster have been played, refill roster
//     if (m_aCurrentMonsterRoaster.empty())
//     {
//         //std::cout << "Monster roster updated\n";
//         //Increase monster level after every roster
//         m_iMonsterLevel += 1;
//         updateMonsterRoster();
//     }

//     // 
// }

// float Monster_Generator::getLevelUpRateAtLevel(int level, float baseRate)
// {
//     return baseRate * std::pow(1.1f, level - 1); // Assuming a 10% increase per level.
// }