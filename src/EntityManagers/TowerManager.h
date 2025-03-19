#ifndef TOWER_MANAGER_H
#define TOWER_MANAGER_H

#include "../Platform.h"
#include "../Entities/TowerEntity.h"
#include "../Views/TowerEntityView.h"
#include "../Generators/TowerGenerator.h"
#include "../EntityDecorators/TowerDecorator.h"
#include "../EntityDecorators/CooldownBoostDecorator.h"
#include "../EntityDecorators/DamageBoostDecorator.h"
#include "../EntityDecorators/RangeBoostDecorator.h"
#include "../EntityDecorators/SpeedBoostDecorator.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../EntityManagers/MonsterManager.h"
#include <memory>

using namespace sf;

class TowerManager
{
public:
    TowerManager(RenderWindow& window, MonsterManager& monsterManager);
    ~TowerManager() = default;

    void SetMapSize(Vector2i mapSize) { m_mapSize = mapSize; }

    void SetInfoUIWidth(int infoUIWidth) { m_infoUIWidth = infoUIWidth; }

    void InitializeGameSetup();

    // std::vector<TowerEntity>& GetTemplateTowers() { return m_templateTowers; }

    // std::vector<TowerEntity>& GetActiveTowers() { return m_activeTowers; }

    std::vector<TowerEntity*> GetTemplateTowers();

    std::vector<std::unique_ptr<TowerEntity>>& GetActiveTowers() { return m_activeTowers; };

    TowerEntityView& GetTowerEntityView() { return m_TowerEntityView; }

    void CreateTower(TowerGenerator::TowerType towerType, const sf::Vector2f& position);

    void RemoveTowerAtPosition(const sf::Vector2f& position);

    void RemoveAllTowers();

    void UpdateTowerAnimations(const float m_fFrameTime);

    float GetSellRate() const { return m_sellRate; }

    void ApplyUpgrades(std::unique_ptr<TowerEntity>* towerPtr);

private:
    RenderWindow& m_Window;

    Vector2i m_mapSize;
    MonsterManager& m_MonsterManager;

    int m_infoUIWidth;

    TowerEntityView m_TowerEntityView;
    TowerGenerator m_TowerGenerator;

    std::vector<std::unique_ptr<TowerEntity>> m_templateTowers;
    std::vector<std::unique_ptr<TowerEntity>> m_activeTowers;

    float m_sellRate;
};

#endif  // TOWER_MANAGER_H