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
    m_TemplateFlameThrowerTexture.loadFromFile("../src/Images/Tower3_Frame_1.png");
    #endif
    #ifdef MAC
    //m_BasicTowerTexture.loadFromFile("Images/basic_tower.png");
    m_TemplateSniperTowerTexture.loadFromFile("Images/Tower2_Frame_1.png");
    m_TemplateRapidTowerTexture.loadFromFile("Images/Tower1_Frame_1.png");
    m_TemplateFlameThrowerTexture.loadFromFile("Images/Tower3_Frame_1.png");
    #endif
}

void TowerEntityView::LoadActiveTowerTextures()
{
    for (int i = 1; i <= 6; ++i) {
        sf::Texture texture;
        #ifdef MAC
        if (!texture.loadFromFile("Images/Tower1_Frame_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load tower frame " << i << std::endl;
        }
        m_RapidTowerTextures.push_back(texture);

        if (!texture.loadFromFile("Images/Tower2_Frame_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load tower frame " << i << std::endl;
        }
        m_SniperTowerTextures.push_back(texture);

        if (!texture.loadFromFile("Images/Tower3_Frame_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load tower frame " << i << std::endl;
        }
        m_FlameThrower.push_back(texture);
       #endif
       #ifdef LINUX
        if (!texture.loadFromFile("../src/Images/Tower1_Frame_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load tower frame " << i << std::endl;
        }
        m_RapidTowerTextures.push_back(texture);

        if (!texture.loadFromFile("../src/Images/Tower2_Frame_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load tower frame " << i << std::endl;
        }
        m_SniperTowerTextures.push_back(texture);

        if (!texture.loadFromFile("../src/Images/Tower3_Frame_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load tower frame " << i << std::endl;
        }
        m_FlameThrowerTextures.push_back(texture);
        #endif
    }
}

void TowerEntityView::Update(const IGameSubject &subject)
{
    //std::cout << "subject pointer: " << &subject << std::endl;
    // Cast the subject (which is of type IGameSubject) to a const TowerEntity*.
    // This assumes that subject is a type of TowerEntity or a derived class (e.g., TowerEntityDecorator).
    // Then, call GetBaseTowerEntity() to retrieve the base TowerEntity pointer that the decorator wraps.
    // The final result is the actual base TowerEntity pointer, not the decorator object itself.
    const TowerEntity *towerEntity = (dynamic_cast<const TowerEntity *>(&subject))->GetBaseTowerEntity();
    //std::cout << "tower entity base pointer: " << towerEntity << std::endl;
    //std::cout << "Subjects size before update: " << m_TowerEntitySubjects.size() << std::endl;
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
    //std::cout << "Subjects size after update: " << m_TowerEntitySubjects.size() << std::endl;
}

void TowerEntityView::RemoveSubject(const TowerEntity * towerPtr)
{
    //std::cout << "remove - passed tower pointer: " << towerPtr << std::endl;
    
    if (towerPtr)  // Ensure the pointer is valid
    {
        //std::cout << "Remove subject: " << towerPtr << std::endl;
        // Call GetBaseTowerEntity() on the towerPtr (which is a TowerEntity or a decorator).
        // This function returns the base TowerEntity pointer, removing any decorations that might be applied.
        // The result is a pointer to the core TowerEntity object, not the decorated version.
        const TowerEntity* towerBasePtr = towerPtr->GetBaseTowerEntity();
        //std::cout << "tower base address: " << towerBasePtr << std::endl;
        m_TowerEntitySubjects.erase(towerBasePtr);
       
    }
    else
    {
        std::cerr << "TowerEntityView::RemoveSubject() - Invalid tower pointer\n";
    }
}

void TowerEntityView::SyncTowerData(TowerEntityData& data, const TowerEntity* towerPtr)
{
    SetTemplateTowerSprite(data, towerPtr->GetType());
    data.sprite.setPosition(towerPtr->GetPosition());
    data.range = towerPtr->GetRange();
    data.maxCooldown = towerPtr->GetMaxCooldown();
    data.damage = towerPtr->GetDamage();
    data.speed = towerPtr->GetSpeed();
    data.cost = towerPtr->GetCost();
    data.level = towerPtr->GetLevel();
    data.type = towerPtr->GetType();
    data.isTemplate = towerPtr->GetIsTemplate();
}

void TowerEntityView::SyncTowers(const std::vector<TowerEntity*>& templateTowers, const std::vector<TowerEntity*> &activeTowers)
{
    // Clear the existing map to start fresh
    m_TowerEntitySubjects.clear();

    // Sync template towers
    for (const TowerEntity* towerPtr : templateTowers)
    {
        TowerEntityData data;
        SyncTowerData(data, towerPtr);
        m_TowerEntitySubjects[towerPtr] = data;
    }

    // Sync active towers
    for (const TowerEntity* towerPtr : activeTowers)
    {
        TowerEntityData data;
        SyncTowerData(data, towerPtr);
        m_TowerEntitySubjects[towerPtr] = data;
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
        case TowerGeneratorData::TowerType::Basic:
            //data->sprite.setTexture(m_BasicTowerTextures[m_curentTowerFrameIndex]);
            break;
        case TowerGeneratorData::TowerType::Sniper:
            data->sprite.setTexture(m_SniperTowerTextures[m_curentTowerFrameIndex]);
            break;
        case TowerGeneratorData::TowerType::Rapid:
            data->sprite.setTexture(m_RapidTowerTextures[m_curentTowerFrameIndex]);
            break;
        case TowerGeneratorData::TowerType::FlameThrower:
            data->sprite.setTexture(m_FlameThrowerTextures[m_curentTowerFrameIndex]);
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

void TowerEntityView::SetTemplateTowerSprite(TowerEntityData &data, TowerGeneratorData::TowerType type)
{
    switch (type)
    {
    case TowerGeneratorData::TowerType::Basic:
        //data.sprite.setTexture(m_TemplateBasicTowerTexture);
        break;
    case TowerGeneratorData::TowerType::Sniper:
        data.sprite.setTexture(m_TemplateSniperTowerTexture);
        break;
    case TowerGeneratorData::TowerType::Rapid:
        data.sprite.setTexture(m_TemplateRapidTowerTexture);
        break;
    case TowerGeneratorData::TowerType::FlameThrower:
        data.sprite.setTexture(m_TemplateFlameThrowerTexture);
        break;
    default:
        break;
    }

    data.sprite.setScale(Vector2f(0.7f, 0.7f));
    data.sprite.setOrigin(data.sprite.getLocalBounds().width / 2, data.sprite.getLocalBounds().height / 2);
    data.sprite.setTextureRect(sf::IntRect(0, 0, 70, 100));
}
