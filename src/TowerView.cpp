#include "TowerView.h"



void TowerView::Draw(sf::RenderWindow& window, std::vector<Tower>& activeTowersType)
{
    for (Tower& tower : activeTowersType) {
        window.draw(tower);
    }
};
void TowerView::Update(const IGameSubject& subject)
{
    const Tower* tower = dynamic_cast<const Tower*>(&subject);
    if (tower) {
        auto& stats = m_towerStats[tower];
        stats.damage = tower->GetDamage();
        stats.range = tower->GetRange();
        stats.cooldown = tower->GetCooldown();
        stats.speed = tower->GetSpeed();
        stats.level = tower->GetLevel();
    }
    std::cout << "Notified TowerView\n";
}

const TowerStats* TowerView::GetTowerStats(const Tower* tower) const
{
    auto it = m_towerStats.find(tower);
    if (it != m_towerStats.end()) {
        return &it->second;
    }
    return nullptr;
}