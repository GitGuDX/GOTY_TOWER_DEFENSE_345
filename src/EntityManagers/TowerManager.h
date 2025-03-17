#ifndef TOWER_MANAGER_H
#define TOWER_MANAGER_H

#include "../Platform.h"
#include "../Entities/TowerEntity.h"
#include "../Views/TowerEntityView.h"
#include "../Generators/TowerGenerator.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class TowerManager
{
public:
    TowerManager(RenderWindow& window);
    ~TowerManager() = default;

    void SetMapSize(Vector2i mapSize) { m_mapSize = mapSize; }

    void InitializeGameSetup();

    std::vector<TowerEntity>& GetTemplateTowers() { return m_templateTowers; }

    std::vector<TowerEntity>& GetActiveTowers() { return m_activeTowers; }

    TowerEntityView& GetTowerEntityView() { return m_TowerEntityView; }

    void CreateTower(TowerGenerator::TowerType towerType, const sf::Vector2f& position);

    void RemoveTower(const sf::Vector2f& position);

    void UpdateTowerAnimations(const float m_fFrameTime);

    float GetSellRate() const { return m_sellRate; }

private:
    RenderWindow& m_Window;

    Vector2i m_mapSize;

    TowerEntityView m_TowerEntityView;
    TowerGenerator m_TowerGenerator;

    std::vector<TowerEntity> m_templateTowers;
    std::vector<TowerEntity> m_activeTowers;

    float m_sellRate;
};

#endif  // TOWER_MANAGER_H