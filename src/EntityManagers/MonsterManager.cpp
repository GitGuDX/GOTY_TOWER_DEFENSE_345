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

void MonsterManager::ApplySpeedDebuffToMonster(std::unique_ptr<MonsterEntity>& monsterPtr)
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
}

void MonsterManager::UpdateSpeedDebuff(std::unique_ptr<MonsterEntity>& monsterPtr, float deltaTime)
{
    // Start with the outermost decorator
    MonsterEntityDecorator* decorator = dynamic_cast<MonsterEntityDecorator*>(monsterPtr.get());
    // Will hold the previous decorator in the chain
    MonsterEntityDecorator* outerPtr = nullptr;
    
    // Traverse the decorator chain
    while (decorator)
    {
        //std::cout << "Decorator type: " << typeid(*decorator).name() << std::endl;
        
        // Check if the current decorator is a SpeedDebuffDecorator
        if (SpeedDebuffDecorator* speedDebuff = dynamic_cast<SpeedDebuffDecorator*>(decorator))
        {
            //std::cout << "Decorator type: " << typeid(*speedDebuff).name() << std::endl;
            //std::cout << "Found the Speed Debuff Decorator" <<std::endl;
            
            // Update the SpeedDebuffDecorator elapsed time with deltaTime
            speedDebuff->Update(deltaTime);
            
            // If the decorator is marked for removal, handle it
            if (speedDebuff->IsMarkedForRemoval())
            {
                // If outerPtr is nullptr, this is the outermost decorator
                if(outerPtr == nullptr)
                {
                    // Transfer the ownership of the decorator one below the SpeedDebuffDecorator to the monsterPtr (the main entry point)
                    monsterPtr = std::move(speedDebuff->GetDecoratedMonster());
                }
                else
                {
                    // Otherwise, link the previous decorator (outerPtr) to the next decorator (Inner decorator)
                    outerPtr->SetDecoratedMonster(speedDebuff->GetDecoratedMonster());
                }
                // Exit the loop after removal (no need to check further decorators)
                break;
            }
        }
        // Update outerPtr to the current decorator (before moving to the next)
        outerPtr = decorator;
        // Move to the next inner decorator in the chain
        decorator = dynamic_cast<MonsterEntityDecorator*>(decorator->GetDecoratedMonsterRef());
    }
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
