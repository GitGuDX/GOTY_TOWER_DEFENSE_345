#include "InfoUI.h"

InfoUI::InfoUI()
    : m_InfoUIWidth(380)
    , m_iCurrentLevel(0)
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
    m_towerUpgradeCostString = "Upgrade Cost: 100";
    m_towerInstructionString_1 = "Press E to upgrade tower";
    m_towerInstructionString_2 = "Right click to destroy tower";
    m_warningString = "";
    m_modeString = "";
    m_woodTowerPriceString = "Cost: 200";
    m_stoneTowerPriceString = "Cost: 300";
    m_nextRoundString = "Press Enter to Begin the Round!";
    m_upgradeString = "";
    m_gameOverString1 = "Game Over";
    m_gameOverString2 = "Press S to set up a new game";
    m_gameOverString3 = "Press R to restart with the same map.";

    notifyObservers();
}