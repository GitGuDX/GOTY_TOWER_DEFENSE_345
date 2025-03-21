#include "TowerManager.h"
#include "../Strategies/TowerTargetStrategies.h"

TowerManager::TowerManager(RenderWindow &window, MonsterManager &monsterManager)
    : m_Window(window)
    , m_MonsterManager(monsterManager)// Set the sell rate to 50%
    , m_TowerEntityView(window)
    , m_TowerGenerator()
    , m_sellRate(0.5f)
{
}

void TowerManager::InitializeGameSetup()
{
    RemoveAllTowers();

    m_templateTowers.reserve(3);   // Reserve space to avoid memory reallocation
    m_activeTowers.reserve(m_mapSize.x/50 * m_mapSize.y/50);   // Reserve space to avoid memory reallocation. Divide by 50 since each title is 50 by 50 pixels

    // Create a Rapid Tower template
    // Allocate TowerEntity on the heap using std::make_unique<TowerEntity>().
    auto rapidTower = std::make_unique<TowerEntity>(m_TowerGenerator.GenerateRapidTowerTemplate());
    rapidTower->AddObserver(&m_TowerEntityView);
    rapidTower->SetPosition(Vector2f(m_mapSize.x + m_infoUIWidth*1/4, m_mapSize.y / 3 + 75));
    rapidTower->SetCost(200);
    rapidTower->SetIsTemplate(true);

    // std::move(newTower) transfers ownership to m_templateTowers.
    m_templateTowers.push_back(std::move(rapidTower));

    // Create a sniper Tower template
    // Allocate TowerEntity on the heap using std::make_unique<TowerEntity>().
    auto sniperTower = std::make_unique<TowerEntity>(m_TowerGenerator.GenerateSniperTowerTemplate());
    sniperTower->AddObserver(&m_TowerEntityView);
    sniperTower->SetPosition(Vector2f(m_mapSize.x + m_infoUIWidth*2/4, m_mapSize.y / 3 + 75));
    sniperTower->SetCost(200);
    sniperTower->SetIsTemplate(true);

    // std::move(newTower) transfers ownership to m_templateTowers.
    m_templateTowers.push_back(std::move(sniperTower));
    std::cout << m_templateTowers.size() << std::endl;

    // //// Create a rapid tower template ////
    // // Add a new Rapid Tower to the template tower list using emplace_back.
    // // This constructs the object in-place, avoiding an extra copy/move operation.
    // m_templateTowers.emplace_back(m_TowerGenerator.GenerateRapidTowerTemplate());
    // //std::cout << "Tower 1 added at address: " << &m_templateTowers.back() << std::endl;
    
    // // Store the index of the newly added tower to access it safely.
    // // This ensures we reference the correct object even if the vector resizes.
    // size_t rapidTowerIndex = m_templateTowers.size() - 1;

    // // Set the position of the tower in the game world.
    // // Accessing it via index ensures stability in case of vector reallocation.
    // m_templateTowers[rapidTowerIndex].AddObserver(&m_TowerEntityView);
    // m_templateTowers[rapidTowerIndex].SetPosition(Vector2f(m_mapSize.x + m_infoUIWidth*1/4, m_mapSize.y / 3 + 75));
    // m_templateTowers[rapidTowerIndex].SetCost(200);
    // m_templateTowers[rapidTowerIndex].SetIsTemplate(true);
    // //std::cout << "rapid tower addres: " << &m_templateTowers[rapidTowerIndex] << std::endl;

    // // Note: Using indices instead of references to `m_templateTowers.back()` prevents 
    // // potential invalid references if the vector resizes due to reallocation.

    // //// Create a sniper tower template ////
    // m_templateTowers.emplace_back(m_TowerGenerator.GenerateSniperTowerTemplate());
    // //std::cout << "Tower 2 added at address: " << &m_templateTowers.back() << std::endl;
    // size_t sniperTowerIndex = m_templateTowers.size() - 1;
    // m_templateTowers[sniperTowerIndex].AddObserver(&m_TowerEntityView);
    // m_templateTowers[sniperTowerIndex].SetPosition(Vector2f(m_mapSize.x + m_infoUIWidth*2/4, m_mapSize.y / 3 + 75));
    // m_templateTowers[sniperTowerIndex].SetCost(300);
    // m_templateTowers[sniperTowerIndex].SetIsTemplate(true);
    // //std::cout << "sniper tower addres: " << &m_templateTowers[rapidTowerIndex] << std::endl;
}

std::vector<TowerEntity *> TowerManager::GetTemplateTowers()
{
    std::vector<TowerEntity*> result;
    for (auto& tower : m_templateTowers)
    {
        result.push_back(tower.get());
    }
    return result;
}

// std::vector<TowerEntity *> TowerManager::GetActiveTowers()
// {
//     std::vector<TowerEntity*> result;
//     for (auto& tower : m_activeTowers)
//     {
//         result.push_back(tower.get());
//     }
//     return result;
// }

void TowerManager::CreateTower(TowerGeneratorData::TowerType towerType, const sf::Vector2f &position)
{
    try {
        // Create tower
        std::cout << "Creating tower..." << std::endl;
        auto newTower = std::make_unique<TowerEntity>(m_TowerGenerator.GenerateTower(towerType));
        
        // Wrap in decorator
        newTower = std::make_unique<TowerEntityDecorator>(std::move(newTower));
        std::cout << "Tower created at: " << newTower.get() << std::endl;
        
        try {
            // Initialize tower
            newTower->AddObserver(&m_TowerEntityView);
            newTower->InitializeStat();
            newTower->SetPosition(position);
            
            // Set strategy
            try {
                TowerTargetStrategy* strategy = nullptr;
                switch(towerType) {
                    case TowerGeneratorData::TowerType::Rapid:
                        strategy = new ClosestTargetStrategy();
                        std::cout << "Setting Closest Target Strategy" << std::endl;
                        break;
                    case TowerGeneratorData::TowerType::Sniper:
                        strategy = new StrongestTargetStrategy();
                        std::cout << "Setting Strongest Target Strategy" << std::endl;
                        break;
                    default:
                        strategy = new WeakestTargetStrategy();
                        std::cout << "Setting Weakest Target Strategy" << std::endl;
                        break;
                }
                if (strategy) {
                    newTower->SetTargetStrategy(strategy);
                }
            }
            catch (const std::exception& e) {
                std::cout << "Strategy creation failed: " << e.what() << std::endl;
                throw;
            }
            
            // Add to active towers
            std::cout << "Adding tower to active towers..." << std::endl;
            m_activeTowers.push_back(std::move(newTower));
            std::cout << "Tower creation complete" << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Tower initialization failed: " << e.what() << std::endl;
            throw;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Tower creation failed: " << e.what() << std::endl;
    }
}
void TowerManager::RemoveTowerAtPosition(const sf::Vector2f &position)
{
    // Use std::find_if to find the tower by position.
    auto it = std::find_if(m_activeTowers.begin(), m_activeTowers.end(),
        [&](const std::unique_ptr<TowerEntity>& tower) {
            return std::abs(tower->GetPosition().x - position.x) < 0.5f &&
                    std::abs(tower->GetPosition().y - position.y) < 0.5f;
        });

    // Check if the tower was found.
    if (it != m_activeTowers.end()) {
        // Remove the observer from the tower.
        (*it)->RemoveObserver(&m_TowerEntityView);

        // Notify the TowerEntityView of the removal.
        m_TowerEntityView.RemoveSubject((*it)->GetBaseTowerEntity());
        
        // Erase the tower from the vector.
        m_activeTowers.erase(it);
    }


    // for (auto it = m_activeTowers.begin(); it != m_activeTowers.end(); ++it)
    // {
    //     //std::cout << "Removing tower" << std::endl;
    //     if (std::abs(it->GetPosition().x - position.x) < 0.5f &&
    //         std::abs(it->GetPosition().y - position.y) < 0.5f)
    //     {
    //         it->RemoveObserver(&m_TowerEntityView); // Remove observer before deleting

    //         // Remove the tower from active towers
    //         m_activeTowers.erase(it);

    //         // Re-sync TowerEntityView after removal to update the visual representation
    //         m_TowerEntityView.SyncTowers(m_templateTowers, m_activeTowers);

    //         return; // Exit after removing to avoid iterator issues
    //     }
    // }
}

void TowerManager::RemoveAllTowers()
{
    for (auto& tower : m_templateTowers)
    {
        tower->RemoveObserver(&m_TowerEntityView);
    }

    for (auto& tower : m_activeTowers)
    {
        tower->RemoveObserver(&m_TowerEntityView);
    }

    m_templateTowers.clear();
    m_activeTowers.clear();
    m_TowerEntityView.EmptyTowerEntitySubjects();

    // for (TowerEntity &tower : m_templateTowers)
    // {
    //     tower.RemoveObserver(&m_TowerEntityView);
    // }

    // for (TowerEntity &tower : m_activeTowers)
    // {
    //     tower.RemoveObserver(&m_TowerEntityView);
    // }

    // m_templateTowers.clear();
    // m_activeTowers.clear();
    // m_TowerEntityView.EmptyTowerEntitySubjects();
}

void TowerManager::UpdateTowerAnimations(const float m_fFrameTime)
{
    Clock& towerAnimationDelay = m_TowerEntityView.GetTowerAnimationDelay();
    if (towerAnimationDelay.getElapsedTime().asSeconds() >= m_fFrameTime) {
        // Update each tower's targeting and animation
        for (auto& tower : m_activeTowers) 
        {
            // Update tower shooting cooldown
            tower->UpdateCooldown(m_fFrameTime);
            
            // Check for targets if tower can shoot
            if (tower->CanShoot()) {
                if (tower->SelectTarget(m_MonsterManager.GetActiveMonsters())) {
                    tower->ResetCooldown();
                }
            }

            // Update tower animation
            TowerEntityView::TowerEntityData* towerData = m_TowerEntityView.GetTowerEntityData(tower.get());
            if (towerData) {
                m_TowerEntityView.SetActiveTowerTexture(towerData);
            }
        }

        m_TowerEntityView.IncrementCurentTowerFrameIndex();
        towerAnimationDelay.restart();
    }
}
    // Clock& towerAnimationDelay = m_TowerEntityView.GetTowerAnimationDelay();
    // if (towerAnimationDelay.getElapsedTime().asSeconds() >= m_fFrameTime) {
    //     // Set the texture for each tower
    //     std::vector<TowerEntity>& activeTowers = GetActiveTowers();
    //     for (TowerEntity& tower : activeTowers) 
    //     {
    //         TowerEntityView::TowerEntityData* towerData = m_TowerEntityView.GetTowerEntityData(&tower);

    //         if (towerData != nullptr)
    //         {
    //             m_TowerEntityView.SetActiveTowerTexture(towerData);
    //         }
    //     }

    //     m_TowerEntityView.IncrementCurentTowerFrameIndex();
    //     // Restart the clock after updating the frame
    //     towerAnimationDelay.restart();
    // }


// Function to apply all decorators to a tower
void TowerManager::ApplyUpgrades(std::unique_ptr<TowerEntity>* towerPtr)
{
    #ifdef DEBUG
    std::cout << "applying upgrade to " << (*towerPtr).get() << std::endl;
    #endif

    // Apply decorators for range, speed, damage, and cooldown
    *towerPtr = std::make_unique<RangeBoostDecorator>(std::move(*towerPtr));  // Always wrap with RangeBoostDecorator
    *towerPtr = std::make_unique<SpeedBoostDecorator>(std::move(*towerPtr));  // Always wrap with SpeedBoostDecorator
    *towerPtr = std::make_unique<DamageBoostDecorator>(std::move(*towerPtr)); // Always wrap with DamageBoostDecorator
    *towerPtr = std::make_unique<CooldownBoostDecorator>(std::move(*towerPtr)); // Always wrap with CooldownBoostDecorator

    #ifdef DEBUG
    std::cout << "applied range decorator: " << (*towerPtr)->GetRange() << std::endl;
    std::cout << "applied tower speed: " << (*towerPtr)->GetSpeed() << std::endl;
    std::cout << "applied tower damage: " << (*towerPtr)->GetDamage() << std::endl;
    std::cout << "applied tower cooldown: " << (*towerPtr)->GetMaxCooldown() << std::endl;
    #endif
}
