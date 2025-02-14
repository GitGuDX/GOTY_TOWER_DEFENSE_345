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

class MonsterGenerator
{
public:
    // Constructor initializes base number of monsters and their increase rate per level
    MonsterGenerator(int baseMonsters, int monsterIncreaseRate);
    // Generate a new monster if needed, pass Game instance as reference
    void generateMonster(Game& game);

private:
    int m_BaseMonsters;
    int m_MonsterIncreaseRate;
    int m_CurrentMonsterIndex;  // To track how many monsters have been generated for this wave
};


#endif
