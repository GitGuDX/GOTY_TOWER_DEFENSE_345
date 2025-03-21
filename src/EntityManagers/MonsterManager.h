#ifndef MONSTER_MANAGER_H
#define MONSTER_MANAGER_H

#include "../Platform.h"
#include "../Entities/MonsterEntity.h"
#include "../Views/MonsterEntityView.h"
#include "../Generators/MonsterGenerator.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

using namespace sf;

class MonsterManager
{
public:
    MonsterManager(RenderWindow& window);
    ~MonsterManager() = default;

    void LoadMonsterAssets();

    void InitializeMonsters(const Vector2f& position);

    void PrepareFirstWave();

    void PrepareNextWave();

    void UpdateNextMonster();

    void GenerateCurrentWave(float addedTime);

    bool IsAllMonstersSpawned();

    bool IsAllMonstersDead();

    MonsterEntityView& GetMonsterEntityView() { return m_MonsterEntityView; }

    MonsterGenerator& GetMonsterGenerator() { return m_MonsterGenerator; }

    std::vector<MonsterEntity>& GetActiveMonsters() { return m_activeMonsters; }

    MonsterEntity& GetNextMonster() { return m_nextMonsters[0]; }

    void RemoveMonster(MonsterEntity& monster);

    void UpdateMonsterAnimations(const float m_fFrameTime);

    void SetMapSize(Vector2i mapSize) { m_mapSize = mapSize; }

    void SetInfoUIWidth(int infoUIWidth) { m_infoUIWidth = infoUIWidth; }

private:

    void IncrementTimeSinceLastGeneration(float addedTime)
    {
        //std::cout << "added time: " << addedTime << std::endl;
        m_fTimeSinceLastGeneration += addedTime;
    }

    void IncrementMonsterFrameIndex(MonsterEntity& monster);

    void UpdateMonsterTexture(MonsterEntity& monster);

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
    Vector2i m_mapSize;
    int m_infoUIWidth;

    MonsterEntityView m_MonsterEntityView;
    MonsterGenerator m_MonsterGenerator;

    Vector2f m_EntryTilePosition;

    int m_CurrentWaveStrength;

    std::vector<MonsterEntity> m_activeMonsters;

    std::array<MonsterEntity, 1> m_nextMonsters;

    int m_iNumberOfMonsterSpawned;

    int m_iNumberOfMonsterDead;

    float m_fTimeSinceLastGeneration;                 // Time elapsed since the last monster was generated
    float m_fGenerationCooldown;               // The cooldown time (in seconds) between monster generations
};


#endif // MONSTER_MANAGER_H