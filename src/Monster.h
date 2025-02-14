#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"

class Monster : public Entity
{
public:
    Monster();
    ~Monster();

    float GetSpeed()
    {
        return m_fSpeed;
    }
    
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
        return m_istrength;
    }

    void SetHealth(int newHealth)
    {
        m_iHealth = newHealth;
    }

    void SetSpeed(float newSpeed)
    {
        m_fSpeed = newSpeed;
    }

    void SetCurrentPathIndex(size_t newIndex)
    {
        m_stCurrentPathIndex = newIndex;
    }

    void SetLevel(int newLevel)
    {
        m_iLevel = newLevel;
    }

    void SetStrength(int newStrength)
    {
        m_istrength = newStrength;
    }

private:
    size_t m_stCurrentPathIndex;           // index of the monster's current path
    int m_iHealth;
    float m_fSpeed;
    int m_iLevel;
    int m_istrength;                           // Determines the rate that the monster steals coin from the player
    /////// add monster type, levels, etc
};

#endif
