#include "TowerManager.h"

TowerManager::TowerManager(RenderWindow &window)
    : m_Window(window)
    , m_TowerEntityView(window)
    , m_TowerGenerator()
    , m_sellRate(0.5f) // Set the sell rate to 50%
{
}

void TowerManager::InitializeGameSetup()
{
    m_templateTowers.reserve(3);   // Reserve space to avoid memory reallocation
    m_activeTowers.reserve(m_mapSize.x/50 * m_mapSize.y/50);   // Reserve space to avoid memory reallocation. Divide by 50 since each title is 50 by 50 pixels

    //// Create a rapid tower template ////
    // Add a new Rapid Tower to the template tower list using emplace_back.
    // This constructs the object in-place, avoiding an extra copy/move operation.
    m_templateTowers.emplace_back(m_TowerGenerator.GenerateRapidTowerTemplate());
    //std::cout << "Tower 1 added at address: " << &m_templateTowers.back() << std::endl;
    
    // Store the index of the newly added tower to access it safely.
    // This ensures we reference the correct object even if the vector resizes.
    size_t rapidTowerIndex = m_templateTowers.size() - 1;

    // Set the position of the tower in the game world.
    // Accessing it via index ensures stability in case of vector reallocation.
    m_templateTowers[rapidTowerIndex].AddObserver(&m_TowerEntityView);
    m_templateTowers[rapidTowerIndex].SetPosition(Vector2f(m_mapSize.x + 100, m_mapSize.y / 3 + 75));
    m_templateTowers[rapidTowerIndex].SetCost(200);
    m_templateTowers[rapidTowerIndex].SetIsTemplate(true);
    //std::cout << "rapid tower addres: " << &m_templateTowers[rapidTowerIndex] << std::endl;

    // Note: Using indices instead of references to `m_templateTowers.back()` prevents 
    // potential invalid references if the vector resizes due to reallocation.

    //// Create a sniper tower template ////
    m_templateTowers.emplace_back(m_TowerGenerator.GenerateSniperTowerTemplate());
    //std::cout << "Tower 2 added at address: " << &m_templateTowers.back() << std::endl;
    size_t sniperTowerIndex = m_templateTowers.size() - 1;
    m_templateTowers[sniperTowerIndex].AddObserver(&m_TowerEntityView);
    m_templateTowers[sniperTowerIndex].SetPosition(Vector2f(m_mapSize.x + 200, m_mapSize.y / 3 + 75));
    m_templateTowers[sniperTowerIndex].SetCost(300);
    m_templateTowers[sniperTowerIndex].SetIsTemplate(true);
    //std::cout << "sniper tower addres: " << &m_templateTowers[rapidTowerIndex] << std::endl;
}

void TowerManager::CreateTower(TowerGenerator::TowerType towerType, const sf::Vector2f &position)
{
    //std::cout << "position: " << position.x << ", " << position.y << std::endl;
    m_activeTowers.emplace_back(m_TowerGenerator.GenerateTower(towerType));
    TowerEntity &newTower = m_activeTowers.back();
    newTower.AddObserver(&m_TowerEntityView);
    //std::cout << "Tower created at address: " << &newTower << std::endl;
    // Update the tower's stats based on the tower type
    newTower.InitializeStat();

    // Set tower position
    newTower.SetPosition(position);
   //std::cout << "Tower position: " << newTower.GetPosition().x << ", " << newTower.GetPosition().y << std::endl;
    
}

void TowerManager::RemoveTower(const sf::Vector2f &position)
{
    for (auto it = m_activeTowers.begin(); it != m_activeTowers.end(); ++it)
    {
        //std::cout << "Removing tower" << std::endl;
        if (std::abs(it->GetPosition().x - position.x) < 0.5f &&
            std::abs(it->GetPosition().y - position.y) < 0.5f)
        {
            it->RemoveObserver(&m_TowerEntityView); // Remove observer before deleting

            // Remove the tower from active towers
            m_activeTowers.erase(it);

            // Re-sync TowerEntityView after removal to update the visual representation
            m_TowerEntityView.SyncTowers(m_templateTowers, m_activeTowers);

            return; // Exit after removing to avoid iterator issues
        }
    }
}

void TowerManager::UpdateTowerAnimations(const float m_fFrameTime)
{
    Clock& towerAnimationDelay = m_TowerEntityView.GetTowerAnimationDelay();
    if (towerAnimationDelay.getElapsedTime().asSeconds() >= m_fFrameTime) {
        // Set the texture for each tower
        std::vector<TowerEntity>& activeTowers = GetActiveTowers();
        for (TowerEntity& tower : activeTowers) 
        {
            TowerEntityView::TowerEntityData* towerData = m_TowerEntityView.GetTowerEntityData(&tower);

            if (towerData != nullptr)
            {
                m_TowerEntityView.SetActiveTowerTexture(towerData);
            }
        }

        m_TowerEntityView.IncrementCurentTowerFrameIndex();
        // Restart the clock after updating the frame
        towerAnimationDelay.restart();
    }
}
