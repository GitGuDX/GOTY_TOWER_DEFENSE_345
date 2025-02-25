#include "GameEvents.h"
#include "Tower.h"
#include <SFML/Graphics.hpp>
#include <vector>

#ifndef TOWERVIEW_H
#define TOWERVIEW_H
/// add interface later 
class TowerView : public IGameObserver{
    private:
    float m_fDamage;
    float m_fRange;
    float m_fCooldown;
    float m_fSpeed;
    int m_iLevel;
    bool m_bHasStats;

public:
    TowerView() = default;
    ~TowerView() = default;
    void Draw(sf::RenderWindow& window, std::vector<Tower>& activeTowersType);
    void OnTowerStatsChanged(const Tower& tower);
    float GetDamage() const
    {
        return m_fDamage;
    }

    float GetCooldown() const{
        return m_fCooldown;
    }
    float GetSpeed() const 
    {
        return m_fSpeed;
    }
    float GetRange() const { 
        return m_fRange; }
    

};

#endif