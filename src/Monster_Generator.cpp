#include "Game.h"                           // Include Game.h so that Monster_Generator.cpp has full definition of Game
#include "Monster_Generator.h"
#include <iostream>
#include <vector>

MonsterGenerator::MonsterGenerator(int baseMonsters, int monsterIncreaseRate)
    : m_BaseMonsters(baseMonsters), m_MonsterIncreaseRate(monsterIncreaseRate), m_CurrentMonsterIndex(0)
{
}

// Pass Game by refrence and since MonsterGenerator class is a friend of Game class, it has access to all Game class's private members
void MonsterGenerator::generateMonster(Game& game)          
{
    /////// Logic for generating monsters according to the game level
    int numMonsters = m_BaseMonsters + game.m_iCurrentLevel * m_MonsterIncreaseRate;

    // Check if we have any monsters left to spawn then generate a monster if true
    if (m_CurrentMonsterIndex < numMonsters) {
        Monster newMonster;
        newMonster.SetTexture(game.m_MonsterTexture);
        newMonster.SetScale(sf::Vector2f(0.06f, 0.06f));
        // Get Monster sprite width and height
        FloatRect monsterSize = newMonster.m_Sprite.getLocalBounds();
        // Set Monster anchor to the center of the sprite
        newMonster.SetOrigin(sf::Vector2f(monsterSize.width / 2, monsterSize.height / 2));
        // Set test monster's starting position to the entry tile
        newMonster.SetPosition(game.m_vEntryTile);
        // Set Monster speed
        newMonster.SetSpeed(100.f);
        newMonster.SetCurrentPathIndex(0);
        game.m_aMonstersQueue.emplace_back(newMonster);
        m_CurrentMonsterIndex++;
    }
}
