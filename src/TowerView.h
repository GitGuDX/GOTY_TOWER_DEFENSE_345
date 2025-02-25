#ifndef TOWERVIEW_H
#define TOWERVIEW_H


#include "GameEvents.h"
#include "Tower.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map> 



struct TowerStats {
    float damage;
    float range;
    float cooldown;
    float speed;
    int level;
};
/// add interface later 
class TowerView : public IGameObserver{
    private:
    

    std::unordered_map<const Tower*, TowerStats> m_towerStats;

    float m_fDamage;
    float m_fRange;
    float m_fCooldown;
    float m_fSpeed;
    int m_iLevel;
    bool m_bHasStats;

public:
TowerView() = default;
    
// Virtual destructor since we inherit from IGameObserver
virtual ~TowerView() override {
    m_towerStats.clear();
}
    void Draw(sf::RenderWindow& window, std::vector<Tower>& activeTowersType);
    void OnTowerStatsChanged(const Tower& tower);
    const TowerStats* GetTowerStats(const Tower* tower) const;
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