#include "MonsterManager.h"

MonsterManager::MonsterManager(RenderWindow &window)
    : m_Window(window)
    , m_MonsterEntityView(window)
    , m_MonsterGenerator()
    , m_CurrentWaveStrength(0)
    , m_iNumberOfMonsterSpawned(0)
    , m_isAllMonstersSpawned(false)
    , m_fTimeSinceLastGeneration(0.f)
    , m_fGenerationCooldown(0.5f)
{
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

void MonsterManager::PrepareNextWave()
{
    // If so, prepare the next round
    m_iNumberOfMonsterSpawned = 0;
    
    m_MonsterGenerator.UpdateNextRoundMonsterGenerator();

    ClearMonsters();

    m_CurrentWaveStrength = m_MonsterGenerator.GetMonsterCountForRound();

    m_activeMonsters.reserve(m_CurrentWaveStrength);
}

void MonsterManager::GenerateCurrentWave()
{
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

void MonsterManager::RemoveMonster(MonsterEntity& monster)
{
    // Remove the monster from the active monsters vector
    for (auto it = m_activeMonsters.begin(); it != m_activeMonsters.end(); ++it)
    {
        if (&(*it) == &monster)
        {
            it->RemoveObserver(&m_MonsterEntityView);
            m_activeMonsters.erase(it);
            m_MonsterEntityView.SyncMonsters(m_activeMonsters);
            break;
        }
    }
}
