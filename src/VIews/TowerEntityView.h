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
        TowerGeneratorData::TowerType type;
        bool isTemplate;
    };

    TowerEntityView(RenderWindow& window);
    ~TowerEntityView() = default;

    void LoadTemplateTowerTextures();

    void LoadActiveTowerTextures();

    void Update(const IGameSubject& subject);

    void RemoveSubject(const TowerEntity* towerPtr);

    void SyncTowerData(TowerEntityData& data, const TowerEntity* towerPtr);

    void SyncTowers(const std::vector<TowerEntity*>& templateTowers, const std::vector<TowerEntity*>& activeTowers);

    const TowerEntityData* GetDraggedTowerEntityData() const
    {
        return m_draggedTowerData;
    }

    TowerEntityData* GetTowerEntityData(const TowerEntity* tower);

    void StartDraggingTower(const TowerEntityData* towerData);

    void UpdateDraggedTower(sf::Vector2f mousePos);
    
    void StopDraggingTower();

    void SetHoveringOnTower(bool isHovering)
    {
        m_isHoveringOnTower = isHovering;
    }

    void Draw();

    Clock& GetTowerAnimationDelay() { return m_towerAnimationDelay; }

    void SetActiveTowerTexture(TowerEntityData* data);

    void IncrementCurentTowerFrameIndex();

    void EmptyTowerEntitySubjects() { m_TowerEntitySubjects.clear(); }

    std::unordered_map<const TowerEntity*, TowerEntityData>& GetSubjects() { return m_TowerEntitySubjects; }

private:
    void SetTemplateTowerSprite(TowerEntityData &data, TowerGeneratorData::TowerType type);

private:
    std::unordered_map<const TowerEntity*, TowerEntityData> m_TowerEntitySubjects;

    RenderWindow& m_Window;

    Texture m_TemplateRapidTowerTexture;
    Texture m_TemplateSniperTowerTexture;
    Texture m_TemplateFlameThrowerTexture;

    std::vector<sf::Texture> m_RapidTowerTextures;
    std::vector<sf::Texture> m_SniperTowerTextures;
    std::vector<sf::Texture> m_FlameThrowerTextures;
    //std::vector<sf::Texture> m_BasicTowerTextures;

    TowerEntityData* m_draggedTowerData = nullptr; // Pointer to the dragged tower data
    bool m_isDraggingTower = false; // Flag to track if a tower is being dragged
    bool m_isHoveringOnTower = false; // Flag to track if the mouse is hovering over a tower

    int m_curentTowerFrameIndex = 0;
    Clock m_towerAnimationDelay;
};  

#endif  // Tower_Entity_View_H