#ifndef MONSTER_MANAGER_H
#define MONSTER_MANAGER_H

#include "../Platform.h"
#include "../Entities/MonsterEntity.h"
#include "../Views/MonsterEntityView.h"
#include "../Generators/MonsterGenerator.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class MonsterManager
{
public:
    MonsterManager(RenderWindow& window);
    ~MonsterManager() = default;

    void SetEntryTilePosition(const Vector2f& position) { m_EntryTilePosition = position; }

    void PrepareFirstWave();

    void PrepareNextWave();

    void GenerateCurrentWave();

    bool IsAllMonstersSpawned();

    bool IsAllMonstersDead();

    MonsterEntityView& GetMonsterEntityView() { return m_MonsterEntityView; }

    MonsterGenerator& GetMonsterGenerator() { return m_MonsterGenerator; }

    std::vector<MonsterEntity>& GetActiveMonsters() { return m_activeMonsters; }

    void RemoveMonster(MonsterEntity& monster);

    void IncrementTimeSinceLastGeneration(float addedTime)
    {
        //std::cout << "added time: " << addedTime << std::endl;
        m_fTimeSinceLastGeneration += addedTime;
    }

    void IncrementMonsterFrameIndex(MonsterEntity& monster);

    void UpdateMonsterTexture(MonsterEntity& monster);

private:
    void ClearMonsters();

    void PrepareWave();
    
    void IncrementActiveMonsterFrameIndex(MonsterEntity& monster);

    void IncrementDyingMonsterFrameIndex(MonsterEntity& monster);

    void resetTimeSinceLastGeneration()
    {
        m_fTimeSinceLastGeneration = 0.f;
    }

private:
    //RenderWindow& m_Window;

    MonsterEntityView m_MonsterEntityView;
    MonsterGenerator m_MonsterGenerator;

    Vector2f m_EntryTilePosition;

    int m_CurrentWaveStrength;

    std::vector<MonsterEntity> m_activeMonsters;

    int m_iNumberOfMonsterSpawned;

    int m_iNumberOfMonsterDead;

    float m_fTimeSinceLastGeneration;                 // Time elapsed since the last monster was generated
    float m_fGenerationCooldown;               // The cooldown time (in seconds) between monster generations
};


#endif // MONSTER_MANAGER_H