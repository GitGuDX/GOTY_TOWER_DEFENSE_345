#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"

////////// Monster Class ////////////
/*
**Feel free to make any suggestions

Monsters will have five stats.
    Level
    Health
    Speed
    Strength (Strength impacts the amount of coin it steals from the player once it reaches the exit tile)
    Reward  (Reward is amount of coin the player wins for eliminating the monster)
Monster also has a m_stCurrentPathIndex member variable that keeps track of the index of its current tile it is on.

There are ___ classes of monsters
    Average monster - Speed +0, Health +0, Strength +0, Wave strength +0, reward +0
    Rogue monster - Speed +1, Health -1, Strength +1, Wave strength +0, reward +1
    Tank monster - Speed -2, Health +3, Strength +2, Wave strength -1, reward +2
    Swarm monster - Speed +2, Health -2, Strength -2, Wave strength +2, reward -2
    Elite Monster - Speed +2, Health +2, Strength +2, Wave strength - 3, reward +3
    ... anything else?

For every level increase, all of its stats increase. At the rate of what?
Each wave will consist of only one class ... for now.
All classes of monster of the same level must have been spawned before the next level monsters are introduced
The order of waves based on class can be randomized.
E.g.) 
    wave 1 (Average - lvl 1) -> wave 2 (Tank - lvl 1) -> wave 3 (Rogue - lvl 1) -> wave 4 (Swarm - lvl 1) ->
    wave 5 (Tank - lvl 2) -> wave 6 (Swarm - lvl 2) -> wave 7 (Rogue - lvl 2) -> wave 8 (Average - lvl 2) -> etc.
*/

class Monster : public Entity
{
public:
    Monster();
    ~Monster();
    
    size_t GetCurrentPathIndex()
    {
        return m_stCurrentPathIndex;
    }

    int GetHealth()
    {
        return m_iHealth;
    }

    float GetSpeed()
    {
        return m_fSpeed;
    }

    int GetLevel()
    {
        return m_iLevel;
    }

    int GetStrength()
    {
        return m_iStrength;
    }

    int GetReward()
    {
        return m_iReward;
    }

    void SetCurrentPathIndex(size_t newIndex)
    {
        m_stCurrentPathIndex = newIndex;
    }

    void SetHealth(int newHealth)
    {
        m_iHealth = newHealth;
    }

    void SetSpeed(float newSpeed)
    {
        m_fSpeed = newSpeed;
    }

    void SetLevel(int newLevel)
    {
        m_iLevel = newLevel;
    }

    void SetStrength(int newStrength)
    {
        m_iStrength = newStrength;
    }

    void SetReward(int newReward)
    {
        m_iReward = newReward;
    }

private:
    size_t m_stCurrentPathIndex;           // index of the monster's current path
    int m_iHealth;
    float m_fSpeed;
    int m_iLevel;
    int m_iStrength;                           // Determines the rate that the monster steals coin from the player
    int m_iReward;
    /////// add monster type, levels, etc
};

#endif
