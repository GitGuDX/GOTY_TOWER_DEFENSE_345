#include "TowerManager.h"
#include "Tower.h"
#include "Math_Helpers.h"
/*

void TowerManager::UpdateTowers()
{
    // Check if the mouse is hovering over a tower
    hoveringOnTower = false;
    for (Tower& tower : a_allActiveTowers) {
        if (tower.GetGlobalBounds().contains(xPosition)) {
            hoveringOnTower = true;
            break;
        }
    }

    // If hovering over a tower, show tower stats
    if (hoveringOnTower) {
        if (dragTimer.getElapsedTime().asMilliseconds() > 800) {
            // Show tower stats
            for (Tower& tower : a_allActiveTowers) {
                if (tower.GetGlobalBounds().contains(xPosition)) {
                    hoverTowerDamage = round(tower.GetDamage() * 100.0f) / 100.0f;
                    hoverTowerCooldown = round(tower.GetCooldown() * 100.0f) / 100.0f;
                    hoverTowerRange = round(tower.GetRange() * 100.0f) / 100.0f;
                    hoverTowerSpeed = round(tower.GetSpeed() * 100.0f) / 100.0f;
                }
            }
        }
    }
}*/