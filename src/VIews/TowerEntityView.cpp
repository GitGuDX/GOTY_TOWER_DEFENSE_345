#include "TowerEntityView.h"

#include <iostream>

using namespace sf;

TowerEntityView::TowerEntityView(RenderWindow &window)
    : m_Window(window)
{
    LoadTemplateTowerTextures();

    LoadActiveTowerTextures();
}

void TowerEntityView::LoadTemplateTowerTextures()
{
    #ifdef LINUX
    //m_BasicTowerTexture.loadFromFile("../src/Images/Tower1_Frame_1.png");
    m_TemplateSniperTowerTexture.loadFromFile("../src/Images/Tower2_Frame_1.png");
    m_TemplateRapidTowerTexture.loadFromFile("../src/Images/Tower1_Frame_1.png");
    #endif
    #ifdef MAC
    //m_BasicTowerTexture.loadFromFile("Images/basic_tower.png");
    m_TemplateSniperTowerTexture.loadFromFile("Images/Tower2_Frame_1.png");
    m_TemplateRapidTowerTexture.loadFromFile("Images/Tower1_Frame_1.png");
    #endif
}

void TowerEntityView::LoadActiveTowerTextures()
{
    for (int i = 1; i <= 6; ++i) {
        sf::Texture texture;
        #ifdef MAC
        if (!texture.loadFromFile("Images/Tower1_Frame_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Skeleton frame " << i << std::endl;
        }
        m_RapidTowerTextures.push_back(texture);

        if (!texture.loadFromFile("Images/Tower2_Frame_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Skeleton frame " << i << std::endl;
        }
        m_SniperTowerTextures.push_back(texture);
       #endif
       #ifdef LINUX
        if (!texture.loadFromFile("../src/Images/Tower1_Frame_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Skeleton frame " << i << std::endl;
        }
        m_RapidTowerTextures.push_back(texture);

        if (!texture.loadFromFile("../src/Images/Tower2_Frame_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Skeleton frame " << i << std::endl;
        }
        m_SniperTowerTextures.push_back(texture);
        #endif
    }
}

void TowerEntityView::Update(const IGameSubject &subject)
{
    //std::cout << "subject pointer: " << &subject << std::endl;
    const TowerEntity *towerEntity = dynamic_cast<const TowerEntity *>(&subject);
    //std::cout << "tower entity pointer: " << towerEntity << std::endl;
    if (!towerEntity)
    {
        //std::cout << "TowerEntityView::Update() - Not a TowerEntity\n";
        return;
    }

    // Remove towers that are no longer valid
    auto it = m_TowerEntitySubjects.begin();
    while (it != m_TowerEntitySubjects.end())
    {
        if (it->first == nullptr)  // If the pointer is invalid
        {
            it = m_TowerEntitySubjects.erase(it);
        }
        else
        {
            ++it;
        }
    }

    if (towerEntity)
    {
        // Check if the TowerEntity is already in the map. If not, create a new data, give it a texture based on its type
        // and add it to the map
        auto it = m_TowerEntitySubjects.find(towerEntity);
        if (it == m_TowerEntitySubjects.end())
        {
            // New tower, so create a new entry in the map
            TowerEntityData data;
            SetTemplateTowerSprite(data, towerEntity->GetType());
            data.sprite.setPosition(towerEntity->GetPosition());
            m_TowerEntitySubjects[towerEntity] = data;
        }
        else
        {
            // Existing tower, so update its data
            TowerEntityData &data = it->second;
            // Update the position if it has changed
            if (data.sprite.getPosition() != towerEntity->GetPosition())
            {
                data.sprite.setPosition(towerEntity->GetPosition());
            }
        }
        // Access the data variable after ensuring the TowerEntity is in the map
        auto &data = m_TowerEntitySubjects[towerEntity];
        data.range = towerEntity->GetRange();
        data.maxCooldown = towerEntity->GetMaxCooldown();
        data.damage = towerEntity->GetDamage();
        data.speed = towerEntity->GetSpeed();
        data.cost = towerEntity->GetCost();
        data.level = towerEntity->GetLevel();
        data.type = towerEntity->GetType();
        data.isTemplate = towerEntity->GetIsTemplate();
    }
    //std::cout << "Notified TowerEntityView\n";
}

void TowerEntityView::SyncTowerData(TowerEntityData& data, const TowerEntity& tower)
{
    SetTemplateTowerSprite(data, tower.GetType());
    data.sprite.setPosition(tower.GetPosition());
    data.range = tower.GetRange();
    data.maxCooldown = tower.GetMaxCooldown();
    data.damage = tower.GetDamage();
    data.speed = tower.GetSpeed();
    data.cost = tower.GetCost();
    data.level = tower.GetLevel();
    data.type = tower.GetType();
    data.isTemplate = tower.GetIsTemplate();
}

void TowerEntityView::SyncTowers(const std::vector<TowerEntity>& templateTowers, const std::vector<TowerEntity> &activeTowers)
{
    //std::cout << "Syncing towers" << std::endl;
    // Clear the existing map to start fresh
    m_TowerEntitySubjects.clear();

    // Sync template towers
    for (const TowerEntity& tower : templateTowers)
    {
        TowerEntityData data;
        SyncTowerData(data, tower);
        m_TowerEntitySubjects[&tower] = data;
    }

    // Sync active towers
    for (const TowerEntity& tower : activeTowers)
    {
        TowerEntityData data;
        SyncTowerData(data, tower);
        m_TowerEntitySubjects[&tower] = data;
    }
}

TowerEntityView::TowerEntityData *TowerEntityView::GetTowerEntityData(const TowerEntity *tower)
{
    // Debugging
    // for (const auto &pair : m_TowerEntitySubjects)
    // {
    //     std::cout << "TowerEntityView::GetTowerEntityData() - TowerEntity at: " << pair.first << std::endl;
    // }
    // std::cout << "passed tower pointer: " << tower << std::endl;
    
    auto it = m_TowerEntitySubjects.find(tower);
    if (it != m_TowerEntitySubjects.end())
    {
        return &(it->second);
    }
    //std::cout << "Tower not found" << std::endl;
    return nullptr; // Return nullptr if not found
}

void TowerEntityView::StartDraggingTower(const TowerEntityView::TowerEntityData* towerData)
{
    //std::cout << "TowerEntityView::StartDraggingTower() - Tower type: " << static_cast<int>(towerType) << std::endl;
    // Prevent memory leak by deleting old dragged tower data if it exists
    if (m_draggedTowerData)
    {
        delete m_draggedTowerData;
    }

    m_isDraggingTower = true;
    m_draggedTowerData = new TowerEntityData();  // Create new data for the dragged tower

    m_draggedTowerData->type = towerData->type;
    m_draggedTowerData->cost = towerData->cost;

    
    
    // Set the type and other properties of the dragged tower based on the tower type
    SetTemplateTowerSprite(*m_draggedTowerData, towerData->type);
    //std::cout << "dragged tower type: " << static_cast<int>(m_draggedTowerData->type) << std::endl;
    // Additional properties like scale, position, etc. can be set here.
}

void TowerEntityView::UpdateDraggedTower(sf::Vector2f mousePos)
{
    if (m_isDraggingTower && m_draggedTowerData)
    {
        // Clamp the mouse position within window bounds
        float clampedX = std::min(std::max(mousePos.x, 0.f), static_cast<float>(m_Window.getSize().x));
        float clampedY = std::min(std::max(mousePos.y, 0.f), static_cast<float>(m_Window.getSize().y));
        m_draggedTowerData->sprite.setPosition(clampedX, clampedY);
    }
}

void TowerEntityView::StopDraggingTower()
{
    m_isDraggingTower = false;
    
    // Once the tower is placed, you could do further processing like adding it to the active towers list.
    // If the dragged tower is dropped on a valid tile, create and place the new tower in the game.
    
    delete m_draggedTowerData;  // Clean up the dragged tower data
    m_draggedTowerData = nullptr; // Reset the pointer

    //std::cout << "Tower stopped dragging" << std::endl;
}

void TowerEntityView::Draw()
{
    for (const auto &pair : m_TowerEntitySubjects)
    {
        // For debug //
        // const TowerEntity *towerEntity = pair.first;
        // const Vector2f &position = towerEntity->GetPosition();
        // std::cout << "TowerEntityView::Draw() - TowerEntity at: " << position.x << ", " << position.y << std::endl;
        //////////////

        const TowerEntityData &data = pair.second;

        if (data.isTemplate && !m_isHoveringOnTower)
        {
            m_Window.draw(data.sprite);
        }
        else if (!data.isTemplate)
        {
            m_Window.draw(data.sprite);
        }
    }

    // If a tower is being dragged, draw it
    if (m_isDraggingTower && m_draggedTowerData)
    {
        m_Window.draw(m_draggedTowerData->sprite);
    }
}

void TowerEntityView::SetActiveTowerTexture(TowerEntityData* data)
{
    switch (data->type)
    {
        case TowerGenerator::TowerType::Basic:
            //data->sprite.setTexture(m_BasicTowerTextures[m_curentTowerFrameIndex]);
            break;
        case TowerGenerator::TowerType::Sniper:
            data->sprite.setTexture(m_SniperTowerTextures[m_curentTowerFrameIndex]);
            break;
        case TowerGenerator::TowerType::Rapid:
            data->sprite.setTexture(m_RapidTowerTextures[m_curentTowerFrameIndex]);
            break;
        default:
            break;
    }
}

void TowerEntityView::IncrementCurentTowerFrameIndex()
{
    m_curentTowerFrameIndex++;
    if (m_curentTowerFrameIndex >= 5)
    {
        m_curentTowerFrameIndex = 0;
    }
}

void TowerEntityView::SetTemplateTowerSprite(TowerEntityData &data, TowerGenerator::TowerType type)
{
    switch (type)
    {
    case TowerGenerator::TowerType::Basic:
        //data.sprite.setTexture(m_TemplateBasicTowerTexture);
        break;
    case TowerGenerator::TowerType::Sniper:
        data.sprite.setTexture(m_TemplateSniperTowerTexture);
        break;
    case TowerGenerator::TowerType::Rapid:
        data.sprite.setTexture(m_TemplateRapidTowerTexture);
        break;
    default:
        break;
    }

    data.sprite.setScale(Vector2f(0.7f, 0.7f));
    data.sprite.setOrigin(data.sprite.getLocalBounds().width / 2, data.sprite.getLocalBounds().height / 2);
    data.sprite.setTextureRect(sf::IntRect(0, 0, 70, 100));
}
