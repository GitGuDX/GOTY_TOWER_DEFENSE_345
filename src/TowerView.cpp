#include "TowerView.h"



void TowerView::Draw(sf::RenderWindow& window, std::vector<Tower>& activeTowersType)
{
    for (Tower& tower : activeTowersType) {
        window.draw(tower);
    }
};
void TowerView::OnTowerStatsChanged(const Tower& tower)
{
    m_fDamage = tower.GetDamage();
    m_fRange = tower.GetRange();
    m_fCooldown = tower.GetCooldown();
    m_fSpeed = tower.GetSpeed();
    m_iLevel = tower.GetLevel();
    m_bHasStats = true;
}