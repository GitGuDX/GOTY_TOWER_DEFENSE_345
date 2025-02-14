#ifndef TOWER_H
#define TOWER_H

#include "Entity.h"
#include <iostream>


class Tower : public Entity
{
public:
    Tower();
    ~Tower();

    void DebugPrint() const 
    {
        std::cout << "Tower Position: " << GetPosition().x << "," << GetPosition().y << "\n"
                  << "Health: " << m_iHealth << "\n"
                  << "Speed: " << m_fDamage << "\n";
    }

    float GetDamage()
    {
        return m_fDamage;
    }
    
    size_t GetCurrentPathIndex()
    {
        return m_stCurrentPathIndex;
    }

    void SetDamage(float newDamage)
    {
        m_fDamage = newDamage;
    }

    void SetCurrentPathIndex(size_t newIndex)
    {
        m_stCurrentPathIndex = newIndex;
    }
private:
    int m_iHealth;
    float m_fDamage;
    size_t m_stCurrentPathIndex;           // index of the Tower's current path
    /////// add Tower type, levels, etc
};

#endif