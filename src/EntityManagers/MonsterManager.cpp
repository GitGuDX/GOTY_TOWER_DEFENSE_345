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
    std::cout << "Size of subjects: " << m_MonsterEntityView.GetSize() << std::endl;
    std::cout << "MonsterManager::ClearMonsters() - Cleared all monsters" << std::endl;
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
    std::cout << "Preparing first wave" << std::endl;
    m_MonsterGenerator.InitializeFirstRoaster();

    PrepareWave();
}

void MonsterManager::PrepareNextWave()
{
    std::cout << "Preparing next wave" << std::endl;
    m_MonsterGenerator.UpdateNextRoundMonsterGenerator();

    PrepareWave();
}

void MonsterManager::UpdateNextMonster()
{
    // Clear the previous monster (if any) and remove observer
    //m_MonsterEntityView.RemoveMonster(&m_nextMonsters[0]);
    //m_nextMonsters[0].RemoveObserver(&m_MonsterEntityView);
    
    // The size of m_nextMonsters is fixed at 1, so we directly update the first element
    m_nextMonsters[0] = m_MonsterGenerator.GetNextMonster();
    
    MonsterEntity &monster = m_nextMonsters[0];  // Use the first (and only) monster in the array
    monster.AddObserver(&m_MonsterEntityView);
    monster.SetPosition(Vector2f(m_mapSize.x + m_infoUIWidth/2, m_mapSize.y / 3 + 210));
    monster.SetIsTemplate(true);
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
        std::cout << "Generating monster\n";
        //m_activeMonsters.push_back(m_MonsterGenerator.GenerateMonster());
        //MonsterEntity &monster = m_activeMonsters.back();
        auto newMonster = std::make_unique<MonsterEntity>(m_MonsterGenerator.GenerateMonster());
        newMonster->AddObserver(&m_HealthBarView);
        newMonster->AddObserver(&m_MonsterEntityView);
        newMonster->SetPosition(m_EntryTilePosition);
        
        #ifdef DEBUG
        std::cout << "Monster " << static_cast<int>(newMonster->GetType()) << " spawned at position: " << newMonster->GetPosition().x << ", " << newMonster->GetPosition().y << std::endl;
        std::cout << "Current monster health is: " << newMonster->GetHealth() << '\n';
        std::cout << "Current monster speed is: " << newMonster->GetSpeed() << '\n';
        std::cout << "Current monster strength is: " << newMonster->GetStrength() << '\n';
        std::cout << "Current monster reward is: " << newMonster->GetReward() << '\n';
        std::cout << "Current monster level is: " << newMonster->GetLevel() << '\n';
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
        std::cerr << "MonsterManager::UpdateMonsterTexture() - Monster data not found\n";
    }
}
