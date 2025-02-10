#ifndef MONSTER_H
#define MOSNTER_H

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

    void SetCurrentPathIndex(size_t newIndex)
    {
        m_stCurrentPathIndex = newIndex;
    }
private:
    int m_iHealth;
    float m_fSpeed;
    size_t m_stCurrentPathIndex;           // index of the monster's current path
    /////// add monster type, levels, etc
};

#endif
