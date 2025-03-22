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
        MonsterGeneratorData::MonsterType type;
        int health;
        int maxHealth;
        float speed;
        int level;
        int strength;
        int reward;
        int activeMonsterFrameIndex;
        int dyingMonsterFrameIndex;
        bool isDying;
        bool isDead;
        
        bool isOnSlowDebuff;
        bool isOnBurnEffect;

        bool isTemplate;
    };

    MonsterEntityView(RenderWindow& window);
    ~MonsterEntityView() = default;

    void LoadActiveMonsterTextures();

    void LoadDyingMonsterTextures();

    void Update(const IGameSubject& subject);

    void Draw();

    void SetTemplateMonsterSprite(MonsterEntityData& data, MonsterGeneratorData::MonsterType type);

    void SetMonsterTexture(MonsterEntityData& data, MonsterGeneratorData::MonsterType type);

    void SetMonsterTint(MonsterEntityData& data);

    void SetHoveringOnTower(bool isHovering) { m_isHoveringOnTower = isHovering; }

    void RemoveMonster(const MonsterEntity* monsterPtr);

    void ClearSubjects() { m_MonsterEntitySubjects.clear(); }

    MonsterEntityView::MonsterEntityData* GetMonsterEntityData(const MonsterEntity* monster);

    Clock& GetMonsterAnimationDelay() { return m_monsterAnimationDelay; }

    int GetActiveTextureArraySize(MonsterGeneratorData::MonsterType type);

    int GetDyingTextureArraySize(MonsterGeneratorData::MonsterType type);

    int GetSize() { return m_MonsterEntitySubjects.size(); }

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

    bool m_isHoveringOnTower = false; // Flag to track if the mouse is hovering over a tower. If so don't show next monster

};

#endif  // MONSTER_ENTITY_VIEW_H