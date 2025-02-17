/**

@file Monster.h

@brief Defines the Monster class with movement, health, and attack mechanics.
*/

#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"
#include "Monster_Generator.h"

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
*/

class Monster : public Entity
{
public:
    Monster();
    ~Monster();


public:
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

    MonsterGenerator::Type GetMonsterType()
    {
        return m_eMonsterType;
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

    void SetMonsterType(MonsterGenerator::Type newType)
    {
        m_eMonsterType = newType;
    }

private:
    size_t m_stCurrentPathIndex;           // index of the monster's current path
    int m_iHealth;
    float m_fSpeed;
    int m_iLevel;
    int m_iStrength;                           // Determines the rate that the monster steals coin from the player
    int m_iReward;
    MonsterGenerator::Type m_eMonsterType;
};

#endif
