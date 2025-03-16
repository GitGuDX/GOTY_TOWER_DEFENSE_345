#ifndef MONSTER_ENTITY_VIEW_H
#define MONSTER_ENTITY_VIEW_H

#include "../Platform.h"
#include "../GameEvents.h"
#include "../Entities/MonsterEntity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace sf;

class MonsterEntityView : public IGameObserver
{
public:
    struct MonsterEntityData 
    {
        Sprite sprite;
        MonsterGenerator::MonsterType type;
        int health;
        int maxHealth;
        float speed;
        int level;
        int strength;
        int reward;
        int activeMonsterFrameIndex;
        int dyingMonsterFrameIndex;
        bool isDying;
    };

    MonsterEntityView(RenderWindow& window);
    ~MonsterEntityView() = default;

    void LoadActiveMonsterTextures();

    void LoadDyingMonsterTextures();

    void Update(const IGameSubject& subject);

    void Draw();

    void SetTemplateMonsterSprite(MonsterEntityData& data, MonsterGenerator::MonsterType type);

    void SetMonsterTexture(MonsterEntityData& data, MonsterGenerator::MonsterType type);

    void SyncMonsterData(MonsterEntityData& data, const MonsterEntity& monster);

    void SyncMonsters(const std::vector<MonsterEntity>& activeMonsters);

private:
    std::unordered_map<const MonsterEntity*, MonsterEntityData> m_MonsterEntitySubjects;

    RenderWindow& m_Window;

    std::vector<sf::Texture> m_SkeletonTextures;
    std::vector<sf::Texture> m_ReaperTextures;
    std::vector<sf::Texture> m_GolemTextures;
    std::vector<sf::Texture> m_MinotaurTextures;
    std::vector<sf::Texture> m_OgreTextures;

    std::vector<sf::Texture> m_SkeletonDeathTextures;
    std::vector<sf::Texture> m_ReaperDeathTextures;
    std::vector<sf::Texture> m_GolemDeathTextures;
    std::vector<sf::Texture> m_MinotaurDeathTextures;
    std::vector<sf::Texture> m_OgreDeathTextures;

    Clock m_monsterAnimationDelay;

};

#endif  // MONSTER_ENTITY_VIEW_H