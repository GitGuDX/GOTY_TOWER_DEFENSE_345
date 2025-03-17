#include "MonsterManager.h"

MonsterManager::MonsterManager(RenderWindow &window)
    : m_Window(window)
    , m_MonsterEntityView(window)
    , m_MonsterGenerator()
    , m_CurrentWaveStrength(0)
    , m_iNumberOfMonsterSpawned(0)
    , m_iNumberOfMonsterDead(0)
    , m_fTimeSinceLastGeneration(0.f)
    , m_fGenerationCooldown(0.5f)
{
}

void MonsterManager::InitializeMonsters(const Vector2f& position)
{
    m_EntryTilePosition = position;

    PrepareFirstWave();
}

void MonsterManager::ClearMonsters()
{
    // Remove all observers
    // for (MonsterEntity& monster : m_activeMonsters)
    // {
    //     //monster.RemoveObserver(&m_MonsterEntityView);
    // }
    m_activeMonsters.clear();
    m_activeMonsters.shrink_to_fit();   // Request capacity reduction

    #ifdef DEBUG
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
    PrepareWave();
}

void MonsterManager::PrepareNextWave()
{
    m_MonsterGenerator.UpdateNextRoundMonsterGenerator();

    PrepareWave();
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
        m_activeMonsters.push_back(m_MonsterGenerator.GenerateMonster());
        MonsterEntity &monster = m_activeMonsters.back();
        monster.AddObserver(&m_MonsterEntityView);
        monster.SetPosition(m_EntryTilePosition);

        #ifdef DEBUG
        std::cout << "Monster " << static_cast<int>(monster.GetType()) << " spawned at position: " << monster.GetPosition().x << ", " << monster.GetPosition().y << std::endl;
        std::cout << "Current monster health is: " << monster.GetHealth() << '\n';
        std::cout << "Current monster speed is: " << monster.GetSpeed() << '\n';
        std::cout << "Current monster strength is: " << monster.GetStrength() << '\n';
        std::cout << "Current monster reward is: " << monster.GetReward() << '\n';
        std::cout << "Current monster level is: " << monster.GetLevel() << '\n';
        #endif

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

void MonsterManager::RemoveMonster(MonsterEntity& monster)
{
    m_iNumberOfMonsterDead++;
    monster.SetIsDead(true);
    m_MonsterEntityView.RemoveMonster(&monster);
    monster.RemoveObserver(&m_MonsterEntityView);
}

void MonsterManager::UpdateMonsterAnimations(const float m_fFrameTime)
{
    Clock& monsterAnimationDelay = m_MonsterEntityView.GetMonsterAnimationDelay();
    if (monsterAnimationDelay.getElapsedTime().asSeconds() >= m_fFrameTime) 
    {
        //RUNNING ANIMATION
        std::vector<MonsterEntity>& activeMonsters = GetActiveMonsters();
        for (MonsterEntity& monster : activeMonsters)
        {
            UpdateMonsterTexture(monster);
            IncrementMonsterFrameIndex(monster);
        }
        monsterAnimationDelay.restart();
    }
}

void MonsterManager::IncrementActiveMonsterFrameIndex(MonsterEntity& monster)
{
    int indexLimit = m_MonsterEntityView.GetActiveTextureArraySize(monster.GetType());
    monster.IncrementActiveFrameIndex(indexLimit);
}

void MonsterManager::IncrementDyingMonsterFrameIndex(MonsterEntity &monster)
{
    int indexLimit = m_MonsterEntityView.GetDyingTextureArraySize(monster.GetType());
    monster.IncrementDyingFrameIndex(indexLimit);
}

void MonsterManager::IncrementMonsterFrameIndex(MonsterEntity &monster)
{
    if (monster.GetIsDying())
    {
        IncrementDyingMonsterFrameIndex(monster);
    }
    else
    {
        IncrementActiveMonsterFrameIndex(monster);
    }
}

void MonsterManager::UpdateMonsterTexture(MonsterEntity &monster)
{
    MonsterEntityView::MonsterEntityData *data = m_MonsterEntityView.GetMonsterEntityData(&monster);
    if (data != nullptr)
    {
        m_MonsterEntityView.SetMonsterTexture(*data, monster.GetType());
    }
    else
    {
        std::cerr << "MonsterManager::UpdateMonsterTexture() - Monster data not found\n";
    }
}
