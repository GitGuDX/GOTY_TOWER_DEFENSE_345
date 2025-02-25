#include "TowerView.h"



void TowerView::Draw(sf::RenderWindow& window, std::vector<Tower>& activeTowersType)
{
    for (Tower& tower : activeTowersType) {
        window.draw(tower);
    }
};
void TowerView::OnTowerStatsChanged(const Tower& tower)
{
    auto& stats = m_towerStats[&tower];
        stats.damage = tower.GetDamage();
        stats.range = tower.GetRange();
        stats.cooldown = tower.GetCooldown();
        stats.speed = tower.GetSpeed();
        stats.level = tower.GetLevel();

    /*
    m_fDamage = tower.GetDamage();
    m_fRange = tower.GetRange();
    m_fCooldown = tower.GetCooldown();
    m_fSpeed = tower.GetSpeed();
    m_iLevel = tower.GetLevel();
    m_bHasStats = true;
    */
}

const TowerStats* TowerView::GetTowerStats(const Tower* tower) const
{
    auto it = m_towerStats.find(tower);
    if (it != m_towerStats.end()) {
        return &it->second;
    }
    return nullptr;
}