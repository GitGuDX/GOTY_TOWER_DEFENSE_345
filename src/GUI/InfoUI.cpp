#include "InfoUI.h"

InfoUI::InfoUI()
    : m_iCurrentLevel(0)
    , m_iCurrentWealth(0)
    , m_hoverTowerDamage(0.0f)
    , m_hoverTowerCooldown(0.0f)
    , m_hoverTowerRange(0.0f)
    , m_hoverTowerSpeed(0.0f)
{
}

void InfoUI::InitializeInfoUI()
{
    m_scoreString = "Score: " + std::to_string(m_iCurrentWealth);
    m_levelString = "Level: " + std::to_string(m_iCurrentLevel);   
    m_instructionString = "Choose an entry Tile...";
    m_towerDamagStringe = "Damage: " + std::to_string(m_hoverTowerDamage);
    m_towerCooldownString = "Cooldown: " + std::to_string(m_hoverTowerCooldown);
    m_towerRangeString = "Range: " + std::to_string(m_hoverTowerRange);
    m_towerSpeedString = "Speed: " + std::to_string(m_hoverTowerSpeed);
    m_warningString = "";
    m_modeString = "";
    m_woodTowerPriceString = "Cost: 200";
    m_stoneTowerPriceString = "Cost: 300";
    m_gameOverString = "Game Over!";
    m_nextRoundString = "Press Enter for next round";
    m_nextRoundString = "";
    m_upgradeString = "";

    notifyObservers();
}