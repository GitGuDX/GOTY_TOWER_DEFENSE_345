#ifndef TOWER_H
#define TOWER_H

#include "Entity.h"


class Tower : public Entity
{
public:
    Tower();
    ~Tower();

    float GetSpeed()
    {
        return m_fSpeed;
    }
    
    size_t GetCurrentPathIndex()
    {
        return m_stCurrentPathIndex;
    }

    void SetSpeed(float newSpeed)
    {
        m_fSpeed = newSpeed;
    }

    void SetCurrentPathIndex(size_t newIndex)
    {
        m_stCurrentPathIndex = newIndex;
    }
private:
    int m_iHealth;
    float m_fSpeed;
    size_t m_stCurrentPathIndex;           // index of the Tower's current path
    /////// add Tower type, levels, etc
};

#endif