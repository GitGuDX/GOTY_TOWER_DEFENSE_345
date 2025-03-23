#include "InfoUI.h"

InfoUI::InfoUI()
    : m_InfoUIWidth(380)
    , m_iCurrentLevel(0)
    , m_iCurrentWealth(0)
{
}

void InfoUI::InitializeInfoUI()
{
    m_scoreString = "Score: " + std::to_string(m_iCurrentWealth);
    m_levelString = "Level: " + std::to_string(m_iCurrentLevel);   
    m_instructionString = "Choose an entry Tile...";
    m_towerInstructionString_1 = "Press E to upgrade tower";
    m_towerInstructionString_2 = "Right click to destroy tower";
    m_TowerSelectionTitleString = "Tower Selection";
    m_gameOverString1 = "Game Over";
    m_gameOverString2 = "Press S to set up a new game";
    m_gameOverString3 = "Press R to restart with the same map.";

    notifyObservers();
}