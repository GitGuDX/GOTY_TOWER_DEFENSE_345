#include "Monster_Generator.h"
#include <iostream>
#include <vector>

MonsterGenerator::MonsterGenerator(int baseMonsters, int monsterIncreaseRate)
    : m_BaseMonsters(baseMonsters), m_MonsterIncreaseRate(monsterIncreaseRate), m_CurrentMonsterIndex(0)
{
}

void MonsterGenerator::generateMonster(int level, std::vector<Monster>& monsters, sf::Texture& monsterTexture, sf::Vector2f entryTile) {
    /////// Logic for generating monsters according to the game level
    int numMonsters = m_BaseMonsters + level * m_MonsterIncreaseRate;

    // Check if we have any monsters left to spawn then generate a monster if true
    if (m_CurrentMonsterIndex < numMonsters) {
        Monster newMonster;
        newMonster.SetTexture(monsterTexture);
        newMonster.SetScale(sf::Vector2f(0.06f, 0.06f));
        // Get Monster sprite width and height
        FloatRect monsterSize = newMonster.m_Sprite.getLocalBounds();
        // Set Monster anchor to the center of the sprite
        newMonster.SetOrigin(sf::Vector2f(monsterSize.width / 2, monsterSize.height / 2));
        // Set test monster's starting position to the entry tile
        newMonster.SetPosition(entryTile);
        // Set Monster speed
        newMonster.SetSpeed(100.f);
        newMonster.SetCurrentPathIndex(0);
        monsters.emplace_back(newMonster);
        m_CurrentMonsterIndex++;
    }
}
