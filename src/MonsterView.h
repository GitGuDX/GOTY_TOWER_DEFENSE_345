#ifndef MONSTERVIEW_H
#define MONSTERVIEW_H

#include "GameEvents.h"
#include "Monster.h"
#include "Tower.h"
#include <SFML/Graphics.hpp>

#include <vector>
#include <unordered_map>

class Monster;

class MonsterView : public IGameObserver
{
private:
    struct MonsterStats 
    {
        float speed;
        int health;
        int strength;
        int reward;
        int level;
        int maxHealth;
    };
    
public:
    MonsterView() = default;
    ~MonsterView() = default;

    
    void Draw(sf::RenderWindow& window, std::vector<Monster> m_aMonstersQueue, int m_aPathSize);
    void RemoveMonster(const Monster& monster);
    void Update(const IGameSubject& subject);
    const MonsterStats* GetMonsterStats(const Monster* monster) const;


private:
    std::vector<Monster> monsters; // Declare the monsters container
    std::unordered_map<const Monster*, MonsterStats> m_monsterStats;
};

#endif