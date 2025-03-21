#include "MonsterManager.h"

MonsterManager::MonsterManager(RenderWindow &window)
    : m_Window(window)
    , m_HealthBarView(window)
    , m_MonsterEntityView(window)
    , m_MonsterGenerator()
    , m_CurrentWaveStrength(0)
    , m_iNumberOfMonsterSpawned(0)
    , m_iNumberOfMonsterDead(0)
    , m_fTimeSinceLastGeneration(0.f)
    , m_fGenerationCooldown(0.5f)
{
}

void MonsterManager::LoadMonsterAssets()
{
    m_MonsterEntityView.LoadActiveMonsterTextures();
    m_MonsterEntityView.LoadDyingMonsterTextures();
}

void MonsterManager::InitializeMonsters(const Vector2f &position)
{
    m_EntryTilePosition = position;

    PrepareFirstWave();
}

void MonsterManager::ClearMonsters()
{
    // Remove all observers
    for (std::unique_ptr<MonsterEntity>& monsterPtr : m_activeMonsters)
    {
        //m_MonsterEntityView.RemoveMonster(&monster);
        //m_HealthBarView.RemoveMonster(&monster);
        monsterPtr->RemoveAllObservers();
    }
    m_activeMonsters.clear();
    m_activeMonsters.shrink_to_fit();   // Request capacity reduction

    m_HealthBarView.ClearSubjects();
    m_MonsterEntityView.ClearSubjects();

    #ifdef DEBUG
    //std::cout << "Size of subjects: " << m_MonsterEntityView.GetSize() << std::endl;
    //std::cout << "MonsterManager::ClearMonsters() - Cleared all monsters" << std::endl;
    #endif
}

void MonsterManager::PrepareWave()
{
    m_iNumberOfMonsterSpawned = 0;

    m_iNumberOfMonsterDead = 0;

    ClearMonsters();

    m_CurrentWaveStrength = m_MonsterGenerator.GetMonsterCountForRound();

    m_activeMonsters.reserve(m_CurrentWaveStrength);
}

void MonsterManager::PrepareFirstWave()
{
    //std::cout << "Preparing first wave" << std::endl;
    m_MonsterGenerator.InitializeFirstRoaster();

    PrepareWave();
}

void MonsterManager::PrepareNextWave()
{
    //std::cout << "Preparing next wave" << std::endl;
    m_MonsterGenerator.UpdateNextRoundMonsterGenerator();

    PrepareWave();
}

void MonsterManager::UpdateNextMonster()
{
    // Clear the previous monster (if any) and remove observer
    //m_MonsterEntityView.RemoveMonster(&m_nextMonsters[0]);
    //m_nextMonsters[0].RemoveObserver(&m_MonsterEntityView);
    
    // The size of m_nextMonsters is fixed at 1, so we directly update the first element
    //m_nextMonsters[0] = m_MonsterGenerator.GetNextMonster();
    // MonsterEntity &monster = m_nextMonsters[0];  // Use the first (and only) monster in the array

    m_nextMonsterPtr = std::make_unique<MonsterEntity>(m_MonsterGenerator.GetNextMonster());
    m_nextMonsterPtr->AddObserver(&m_MonsterEntityView);
    m_nextMonsterPtr->SetPosition(Vector2f(m_mapSize.x + m_infoUIWidth/2, m_mapSize.y / 3 + 210));
    m_nextMonsterPtr->SetIsTemplate(true);
}

void MonsterManager::GenerateCurrentWave(float addedTime)
{
    IncrementTimeSinceLastGeneration(addedTime);

    // std::cout << "Time since last generation: " << m_fTimeSinceLastGeneration << '\n';
    // std::cout << "Generation cooldown: " << m_fGenerationCooldown << '\n';
    // std::cout << "Number of monster spawned: " << m_iNumberOfMonsterSpawned << '\n';
    // std::cout << "Current wave strength: " << m_CurrentWaveStrength << '\n';
    if (m_fTimeSinceLastGeneration >= m_fGenerationCooldown && m_iNumberOfMonsterSpawned < m_CurrentWaveStrength)
    {
        //std::cout << "Generating monster\n";
        //m_activeMonsters.push_back(m_MonsterGenerator.GenerateMonster());
        //MonsterEntity &monster = m_activeMonsters.back();
        auto newMonster = std::make_unique<MonsterEntity>(m_MonsterGenerator.GenerateMonster());
        // Wrap in decorator
        newMonster = std::make_unique<MonsterEntityDecorator>(std::move(newMonster));
        newMonster->AddObserver(&m_HealthBarView);
        newMonster->AddObserver(&m_MonsterEntityView);
        newMonster->SetPosition(m_EntryTilePosition);
        
        #ifdef DEBUG
        //std::cout << "Monster " << static_cast<int>(newMonster->GetType()) << " spawned at position: " << newMonster->GetPosition().x << ", " << newMonster->GetPosition().y << std::endl;
        //std::cout << "Current monster health is: " << newMonster->GetHealth() << '\n';
        //std::cout << "Current monster speed is: " << newMonster->GetSpeed() << '\n';
        //std::cout << "Current monster strength is: " << newMonster->GetStrength() << '\n';
        //std::cout << "Current monster reward is: " << newMonster->GetReward() << '\n';
        //std::cout << "Current monster level is: " << newMonster->GetLevel() << '\n';
        #endif

        m_activeMonsters.push_back(std::move(newMonster));

        m_iNumberOfMonsterSpawned++;

        resetTimeSinceLastGeneration();
    }    
}

bool MonsterManager::IsAllMonstersSpawned()
{
    return m_iNumberOfMonsterSpawned >= m_CurrentWaveStrength;
}

bool MonsterManager::IsAllMonstersDead()
{
    return m_iNumberOfMonsterDead >= m_CurrentWaveStrength;
}

void MonsterManager::RemoveMonster(MonsterEntity* monsterPtr)
{
    m_iNumberOfMonsterDead++;
    monsterPtr->SetIsDead(true);
    m_HealthBarView.RemoveMonster(monsterPtr);
    m_MonsterEntityView.RemoveMonster(monsterPtr);
    monsterPtr->RemoveAllObservers();
}

void MonsterManager::UpdateMonsterAnimations(const float m_fFrameTime)
{
    Clock& monsterAnimationDelay = m_MonsterEntityView.GetMonsterAnimationDelay();
    if (monsterAnimationDelay.getElapsedTime().asSeconds() >= m_fFrameTime) 
    {
        //RUNNING ANIMATION
        for (std::unique_ptr<MonsterEntity>& monsterPtr : m_activeMonsters)
        {
            UpdateMonsterTexture(monsterPtr.get());
            IncrementMonsterFrameIndex(monsterPtr.get());
        }
        monsterAnimationDelay.restart();
    }
}

std::unique_ptr<MonsterEntity> MonsterManager::ApplySpeedDebuffToMonster(std::unique_ptr<MonsterEntity> monsterPtr)
{
    // Check if the monster already has a SpeedDebuffDecorator
    if (auto* debuff = dynamic_cast<SpeedDebuffDecorator*>(monsterPtr.get())) {
        // If the monster has the debuff, reset the elapsed time
        debuff->ResetElapsedTime();
        std::cout << "Speed debuff elapsed time reset" << std::endl;
    } else {
        // If the monster doesn't have a debuff, apply the SpeedDebuffDecorator
        monsterPtr = std::make_unique<SpeedDebuffDecorator>(std::move(monsterPtr));
        std::cout << "Monster is now wrapped with: " << typeid(*monsterPtr).name() << std::endl;
    }
    return monsterPtr;
}

void MonsterManager::UpdateMonsterBuffs(std::unique_ptr<MonsterEntity>& monsterPtr, float /*deltaTime*/)
{
    // Try to cast to MonsterEntityDecorator (or its subclass)
    // if (auto* decorator = dynamic_cast<MonsterEntityDecorator*>(monsterPtr.get())) {
    //     //decorator->RemoveExpiredDecorators(); // Now you can call RemoveExpiredDecorators
    //     //findSpeedDebuffDecorator(monsterPtr);
    //     // Try to find and remove the SpeedDebuffDecorator if applied
    //     //findSpeedDebuffDecorator(monsterPtr);
        
    //     // If we found and updated the monster pointer, we update it
    //     // if (updatedMonsterPtr) {
    //     //     monsterPtr = std::move(updatedMonsterPtr);
    //     // }
    //     // If the decorator exists, remove it from the chain
    //     //if (speedDebuffDecorator) {
    //     //    monsterPtr = RemoveDecorator(std::move(monsterPtr), speedDebuffDecorator);
    //     //    decorator->Update(deltaTime); // The update will reflect the debuff if applied
    //     //}
    //     //decorator->Update(deltaTime); // The update will reflect the debuff if applied
    // }
    findSpeedDebuffDecorator(monsterPtr);
}

void MonsterManager::findSpeedDebuffDecorator(std::unique_ptr<MonsterEntity>& monster) 
{
    auto* decorator = dynamic_cast<MonsterEntityDecorator*>(monster.get());
    
    while (decorator) {
        // Check if it's a SpeedDebuffDecorator
        auto* speedDebuff = dynamic_cast<SpeedDebuffDecorator*>(decorator->GetDecoratedMonster().get());
        if (speedDebuff) {
            std::cout << "Found speed debuff decorator" << std::endl;

            // Set the original decorator on the inner monster (if needed)
            auto* innerMonster = dynamic_cast<MonsterEntityDecorator*>(speedDebuff->GetDecoratedMonster().get());
            if (innerMonster) {
                std::cout << "Removing speed debuff" << std::endl;
                innerMonster->SetDecoratedMonster(decorator);
            }

            return;
        }

        // Move to the next decorator in the chain
        decorator = dynamic_cast<MonsterEntityDecorator*>(decorator->GetDecoratedMonster().get());
    }
    
}

std::unique_ptr<MonsterEntity> MonsterManager::RemoveDecorator(std::unique_ptr<MonsterEntity> monster, MonsterEntityDecorator* decoratorToRemove) 
{
    if (!monster) return nullptr;

    // If the monster is already a base entity (not a decorator), return it unchanged
    auto* decorator = dynamic_cast<MonsterEntityDecorator*>(monster.get());
    if (!decorator) return monster;  

    // If the current decorator is the one to remove, return the wrapped entity
    if (decorator == decoratorToRemove) {
        std::cout << "Removed speed buff" << std::endl;
        return std::move(decorator->GetDecoratedMonster());
    }

    // // Otherwise, recurse deeper
    // if (auto* decorator = dynamic_cast<MonsterEntityDecorator*>(monster.get())) {
    //     decorator->SetDecoratedMonster(RemoveDecorator(std::move(decorator->GetDecoratedMonster()), decoratorToRemove));
    // }
    return RemoveDecorator(std::move(decorator->GetDecoratedMonster()), decoratorToRemove);
    // return monster;
}

void MonsterManager::IncrementActiveMonsterFrameIndex(MonsterEntity* monsterPtr)
{
    int indexLimit = m_MonsterEntityView.GetActiveTextureArraySize(monsterPtr->GetType());
    monsterPtr->IncrementActiveFrameIndex(indexLimit);
}

void MonsterManager::IncrementDyingMonsterFrameIndex(MonsterEntity* monsterPtr)
{
    int indexLimit = m_MonsterEntityView.GetDyingTextureArraySize(monsterPtr->GetType());
    monsterPtr->IncrementDyingFrameIndex(indexLimit);
}

void MonsterManager::IncrementMonsterFrameIndex(MonsterEntity* monsterPtr)
{
    if (monsterPtr->GetIsDying())
    {
        IncrementDyingMonsterFrameIndex(monsterPtr);
    }
    else
    {
        IncrementActiveMonsterFrameIndex(monsterPtr);
    }
}

void MonsterManager::UpdateMonsterTexture(MonsterEntity* monsterPtr)
{
    MonsterEntityView::MonsterEntityData *data = m_MonsterEntityView.GetMonsterEntityData(monsterPtr);
    if (data != nullptr)
    {
        m_MonsterEntityView.SetMonsterTexture(*data, monsterPtr->GetType());
    }
    else
    {
        //std::cerr << "MonsterManager::UpdateMonsterTexture() - Monster data not found\n";
    }
}
