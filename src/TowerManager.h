#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tower.h"
#include "Entity.h"
#include "Monster.h"
class TowerManager{

    private:
        Tower* m_pSelectedTower = nullptr;
        std::vector<Tower> a_allActiveTowers;
        std::vector<Tower> a_activeWoodTowers;
        std::vector<Tower> a_activeStoneTowers;
        std::vector<Tower> a_towerMenu;
        bool hoveringOnTower;
        float hoverTowerDamage;
        float hoverTowerCooldown;
        float hoverTowerRange;
        float hoverTowerSpeed;
        sf::Vector2f xPosition; // Center the X at the hovered tower
        Sprite* draggedSprite = nullptr;
        Texture m_towerTexture1;
        Texture m_towerTexture2;
        Tower tower1;
        Tower tower2;
        Tower draggedTower;
        bool isDraggingTower = false;
        sf::Clock dragTimer;
    public:
    void UpdateTowers();
    void DrawTowers();
};