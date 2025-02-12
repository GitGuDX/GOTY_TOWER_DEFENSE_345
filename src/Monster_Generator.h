#ifndef MONSTER_GENERATOR_H
#define MONSTER_GENERATOR_H

#include <vector>
#include <SFML/Graphics.hpp>

class Monster;

class MonsterGenerator
{
public:
    // Constructor initializes base number of monsters and their increase rate per level
    MonsterGenerator(int baseMonsters, int monsterIncreaseRate);
    // Generate a new monster if needed, based on the level and the existing monsters
    void generateMonster(int level, std::vector<Monster>& monsters, sf::Texture& monsterTexture, sf::Vector2f entryTile);

private:
    int m_BaseMonsters;
    int m_MonsterIncreaseRate;
    int m_CurrentMonsterIndex;  // To track how many monsters have been spawned
};


#endif
