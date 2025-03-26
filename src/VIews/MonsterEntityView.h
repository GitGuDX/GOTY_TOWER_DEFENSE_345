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

/**
 * @class MonsterEntityView
 * @brief Handles the visual representation and updates of monsters in the game.
 * 
 * This class observes the state of `MonsterEntity` objects and updates their corresponding visual representation, including animation frames, health, and effects. It also manages textures for active and dying monsters and displays the monsters on the window.
 * 
 * Key Methods:
 * - `Update()`: Updates the monster view based on changes in the game state.
 * - `Draw()`: Draws the monsters to the window.
 * - `SetTemplateMonsterSprite()`: Sets the sprite for a template monster.
 * - `SetMonsterTexture()`: Sets the texture for a monster based on its type.
 * - `SetMonsterTint()`: Sets the color tint for a monster (e.g., to indicate debuffs).
 * - `RemoveMonster()`: Removes a monster from the view.
 * - `ClearSubjects()`: Clears all monster data from the view.
 * - `GetMonsterEntityData()`: Retrieves the data associated with a specific monster.
 * - `GetMonsterAnimationDelay()`: Gets the clock that tracks the animation delay for monsters.
 * 
 * Private Attributes:
 * - `m_MonsterEntitySubjects`: A map storing the data for each monster.
 * - `m_Window`: The SFML window to render the monsters to.
 * - Texture arrays for different monster types and death animations (e.g., `m_SkeletonTextures`, `m_SkeletonDeathTextures`).
 * - `m_monsterAnimationDelay`: The clock used for handling animation delays.
 * - `m_isHoveringOnTower`: Flag to determine if the mouse is hovering over a tower (to prevent drawing the next monster).
 */
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