#ifndef Tower_Entity_View_H
#define Tower_Entity_View_H

#include "../Platform.h"
#include "../GameEvents.h"
#include "../Entities/TowerEntity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace sf;

class TowerEntityView : public IGameObserver
{
public:
    struct TowerEntityData
    {
        Sprite sprite;
        float range;
        float maxCooldown;
        float damage;
        float speed;
        int cost;
        int level;
        TowerGenerator::TowerType type;
        bool isTemplate;
    };

    TowerEntityView(RenderWindow& window);
    ~TowerEntityView() = default;

    void LoadTemplateTowerTextures();

    void LoadActiveTowerTextures();

    void Update(const IGameSubject& subject);

    void SyncTowerData(TowerEntityData& data, const TowerEntity& tower);

    void SyncTowers(const std::vector<TowerEntity>& templateTowers, const std::vector<TowerEntity>& activeTowers);

    const TowerEntityData* GetDraggedTowerEntityData() const
    {
        return m_draggedTowerData;
    }

    const TowerEntityData* GetTowerEntityData(const TowerEntity* tower) const;

    void StartDraggingTower(const TowerEntityData* towerData);

    void UpdateDraggedTower(sf::Vector2f mousePos);
    
    void StopDraggingTower();

    void SetHoveringOnTower(bool isHovering)
    {
        m_isHoveringOnTower = isHovering;
    }

    void Draw();

private:
    void SetTemplateTowerSprite(TowerEntityData& data, TowerGenerator::TowerType type);

private:
    std::unordered_map<const TowerEntity*, TowerEntityData> m_TowerEntitySubjects;

    RenderWindow& m_Window;

    Texture m_TemplateRapidTowerTexture;
    Texture m_TemplateSniperTowerTexture;

    std::vector<sf::Texture> m_RapidTowerTextures;
    std::vector<sf::Texture> m_SniperTowerTextures;

    TowerEntityData* m_draggedTowerData = nullptr; // Pointer to the dragged tower data
    bool m_isDraggingTower = false; // Flag to track if a tower is being dragged
    bool m_isHoveringOnTower = false; // Flag to track if the mouse is hovering over a tower
};  

#endif  // Tower_Entity_View_H