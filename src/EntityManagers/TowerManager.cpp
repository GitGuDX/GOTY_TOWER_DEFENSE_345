#include "TowerManager.h"
#include "../Strategies/TowerTargetStrategies.h"

TowerManager::TowerManager(RenderWindow &window, MonsterManager &monsterManager)
    : m_MonsterManager(monsterManager)// Set the sell rate to 50%
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
    auto rapidTower = std::make_unique<TowerEntity>(m_TowerGenerator.GenerateTower(TowerGeneratorData::TowerType::Rapid));
    rapidTower->AddObserver(&m_TowerEntityView);
    rapidTower->SetPosition(Vector2f(m_mapSize.x + m_infoUIWidth*1/4, m_mapSize.y / 3 + 75));
    rapidTower->SetIsTemplate(true);

    m_templateTowers.push_back(std::move(rapidTower));

    // Create a sniper Tower template
    // Allocate TowerEntity on the heap using std::make_unique<TowerEntity>().
    auto sniperTower = std::make_unique<TowerEntity>(m_TowerGenerator.GenerateTower(TowerGeneratorData::TowerType::Sniper));
    sniperTower->AddObserver(&m_TowerEntityView);
    sniperTower->SetPosition(Vector2f(m_mapSize.x + m_infoUIWidth*2/4, m_mapSize.y / 3 + 75));
    sniperTower->SetIsTemplate(true);

    m_templateTowers.push_back(std::move(sniperTower));
    std::cout << m_templateTowers.size() << std::endl;

    // Create a flame thrower Tower template
    // Allocate TowerEntity on the heap using std::make_unique<TowerEntity>().
    auto flameTower = std::make_unique<TowerEntity>(m_TowerGenerator.GenerateTower(TowerGeneratorData::TowerType::FlameThrower));
    flameTower->AddObserver(&m_TowerEntityView);
    flameTower->SetPosition(Vector2f(m_mapSize.x + m_infoUIWidth*2/4 + 100, m_mapSize.y / 3 + 75));
    flameTower->SetIsTemplate(true);

    m_templateTowers.push_back(std::move(flameTower));
    std::cout << m_templateTowers.size() << std::endl;

}

void TowerManager::CreateTower(TowerGeneratorData::TowerType towerType, const sf::Vector2f &position)
{
    try {
        // Create tower
        //std::cout << "Creating tower..." << std::endl;
        auto newTower = std::make_unique<TowerEntity>(m_TowerGenerator.GenerateTower(towerType));
        
        // Wrap in decorator
        newTower = std::make_unique<TowerEntityDecorator>(std::move(newTower));
        //std::cout << "Tower created at: " << newTower.get() << std::endl;
        
        try {
            // Initialize tower
            newTower->AddObserver(&m_TowerEntityView);
            newTower->SetPosition(position);
            
            // Set strategy
            try {
                TowerTargetStrategy* strategy = nullptr;
                switch(towerType) {
                    case TowerGeneratorData::TowerType::Rapid:
                        strategy = new WeakestTargetStrategy();
                        //std::cout << "Setting Closest Target Strategy" << std::endl;
                        break;
                    case TowerGeneratorData::TowerType::Sniper:
                        strategy = new StrongestTargetStrategy();
                        //std::cout << "Setting Strongest Target Strategy" << std::endl;
                        break;
                    case TowerGeneratorData::TowerType::FlameThrower:
                        strategy = new ClosestTargetStrategy();
                        //std::cout << "Setting Weakest Target Strategy" << std::endl;
                        break;
                    default:
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
            //std::cout << "Adding tower to active towers..." << std::endl;
            m_activeTowers.push_back(std::move(newTower));
            //std::cout << "Tower creation complete" << std::endl;
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
