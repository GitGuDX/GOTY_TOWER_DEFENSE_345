#ifndef MONSTER_MANAGER_H
#define MONSTER_MANAGER_H

#include "../Platform.h"
#include "../Entities/MonsterEntity.h"
#include "../MonsterDecorators/MonsterDecorator.h"
#include "../MonsterDecorators/SpeedDebuffDecorator.h"
#include "../MonsterDecorators/BurnEffectDecorator.h"
#include "../Views/HealthBarView.h"
#include "../Views/MonsterEntityView.h"
#include "../Generators/MonsterGenerator.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <memory>

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

    HealthBarView& GetHealthBarView() { return m_HealthBarView; }

    MonsterEntityView& GetMonsterEntityView() { return m_MonsterEntityView; }

    MonsterGenerator& GetMonsterGenerator() { return m_MonsterGenerator; }

    std::vector<std::unique_ptr<MonsterEntity>>& GetActiveMonsters() { return m_activeMonsters; }

    std::unique_ptr<MonsterEntity>& GetNextMonster() { return m_nextMonsterPtr; }

    void RemoveMonster(MonsterEntity* monsterPtr);

    void UpdateMonsterAnimations(const float m_fFrameTime);

    void SetMapSize(Vector2i mapSize) { m_mapSize = mapSize; }

    void SetInfoUIWidth(int infoUIWidth) { m_infoUIWidth = infoUIWidth; }

    void ApplySpeedDebuffToMonster(std::unique_ptr<MonsterEntity>& monsterPtr);

    void ApplyBurnEffectToMonster(std::unique_ptr<MonsterEntity>& monsterPtr);

    void UpdateSpeedDebuff(std::unique_ptr<MonsterEntity>& monsterPtr, float deltaTime);

    void UpdateBurnEffect(std::unique_ptr<MonsterEntity>& monsterPtr, float deltaTime);

private:

    void IncrementTimeSinceLastGeneration(float addedTime)
    {
        //std::cout << "added time: " << addedTime << std::endl;
        m_fTimeSinceLastGeneration += addedTime;
    }

    void IncrementMonsterFrameIndex(MonsterEntity* monsterPtr);

    void UpdateMonsterTexture(MonsterEntity* monsterPtr);

    void ClearMonsters();

    void PrepareWave();
    
    void IncrementActiveMonsterFrameIndex(MonsterEntity* monsterPtr);

    void IncrementDyingMonsterFrameIndex(MonsterEntity* monsterPtr);

    void resetTimeSinceLastGeneration()
    {
        m_fTimeSinceLastGeneration = 0.f;
    }

    void RemoveExpiredSpeedDebuffDecorator(std::unique_ptr<MonsterEntity>& monster);

    std::unique_ptr<MonsterEntity> RemoveDecorator(std::unique_ptr<MonsterEntity> monster, MonsterEntityDecorator* decoratorToRemove); 

private:
    //RenderWindow& m_Window;
    Vector2i m_mapSize;
    int m_infoUIWidth;

    HealthBarView m_HealthBarView;
    MonsterEntityView m_MonsterEntityView;
    MonsterGenerator m_MonsterGenerator;

    Vector2f m_EntryTilePosition;

    int m_CurrentWaveStrength;

    std::vector<std::unique_ptr<MonsterEntity>> m_activeMonsters;

    std::unique_ptr<MonsterEntity> m_nextMonsterPtr;

    int m_iNumberOfMonsterSpawned;

    int m_iNumberOfMonsterDead;

    float m_fTimeSinceLastGeneration;                 // Time elapsed since the last monster was generated
    float m_fGenerationCooldown;               // The cooldown time (in seconds) between monster generations
};


#endif // MONSTER_MANAGER_H