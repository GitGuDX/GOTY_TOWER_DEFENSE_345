#include "MonsterEntityView.h"

using namespace sf;

MonsterEntityView::MonsterEntityView(RenderWindow &window)
    : m_Window(window)
{
}

void MonsterEntityView::LoadActiveMonsterTextures()
{
    for (int i = 0; i <= 11; ++i) {
        sf::Texture texture;
        #ifdef LINUX
        //Running Textures Loaded
        if (!texture.loadFromFile("../src/Images/Running_Skeleton/0_Skeleton_Crusader_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Skeleton frame " << i << std::endl;
        }
        m_SkeletonTextures.push_back(texture);

        if (!texture.loadFromFile("../src/Images/Running_Reaper/0_Reaper_Man_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Reaper frame " << i << std::endl;
        }
        m_ReaperTextures.push_back(texture);

        if (!texture.loadFromFile("../src/Images/Running_Golem/0_Golem_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Golem frame " << i << std::endl;
        }
        m_GolemTextures.push_back(texture);

        if (!texture.loadFromFile("../src/Images/Running_Minotaur/0_Minotaur_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Minotaur frame " << i << std::endl;
        }
        m_MinotaurTextures.push_back(texture);

        if (!texture.loadFromFile("../src/Images/Running_Ogre/0_Ogre_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Ogre frame " << i << std::endl;
        }
        m_OgreTextures.push_back(texture);

        //Dying Textures Loaded
        // ...

        #endif
        #ifdef MAC
        //Running Textures Loaded
        if (!texture.loadFromFile("Images/Running_Skeleton/0_Skeleton_Crusader_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Skeleton frame " << i << std::endl;
        }
        m_SkeletonTextures.push_back(texture);

        if (!texture.loadFromFile("Images/Running_Reaper/0_Reaper_Man_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Reaper frame " << i << std::endl;
        }
        m_ReaperTextures.push_back(texture);

        if (!texture.loadFromFile("Images/Running_Golem/0_Golem_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Golem frame " << i << std::endl;
        }
        m_GolemTextures.push_back(texture);

        if (!texture.loadFromFile("Images/Running_Minotaur/0_Minotaur_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Minotaur frame " << i << std::endl;
        }
        m_MinotaurTextures.push_back(texture);

        if (!texture.loadFromFile("Images/Running_Ogre/0_Ogre_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Ogre frame " << i << std::endl;
        }
        m_OgreTextures.push_back(texture);
        #endif
        #ifdef WINDOW
        // add for window
        #endif
    }
}

void MonsterEntityView::LoadDyingMonsterTextures()
{
    //DYING TEXTURES
    for(int j = 0; j <= 14; ++j){
        sf::Texture texture;
        //Dying Textures Loaded
        #ifdef LINUX
        if (!texture.loadFromFile("../src/Images/Skeleton_Dying/_Skeleton_Crusader_Dying_" + std::to_string(j) + ".png")) {
            std::cerr << "Failed to load Skeleton death frame " << j << std::endl;
        }
        m_SkeletonDeathTextures.push_back(texture);

        if (!texture.loadFromFile("../src/Images/Reaper_Dying/_Reaper_Man_Dying_" + std::to_string(j) + ".png")) {
            std::cerr << "Failed to load Reaper death frame " << j << std::endl;
        }
        m_ReaperDeathTextures.push_back(texture);

        if (!texture.loadFromFile("../src/Images/Golem_Dying/_Golem_Dying_" + std::to_string(j) + ".png")) {
            std::cerr << "Failed to load Golem death frame " << j << std::endl;
        }
        m_GolemDeathTextures.push_back(texture);

        if (!texture.loadFromFile("../src/Images/Minotaur_Dying/_Minotaur_Dying_" + std::to_string(j) + ".png")) {
            std::cerr << "Failed to load Minotaur death frame " << j << std::endl;
        }
        m_MinotaurDeathTextures.push_back(texture);

        if (!texture.loadFromFile("../src/Images/Ogre_Dying/_Ogre_Dying_" + std::to_string(j) + ".png")) {
            std::cerr << "Failed to load Ogre death frame " << j << std::endl;
        }
        m_OgreDeathTextures.push_back(texture);
        #endif

        #ifdef MAC
        if (!texture.loadFromFile("Images/Skeleton_Dying/_Skeleton_Crusader_Dying_" + std::to_string(j) + ".png")) {
            std::cerr << "Failed to load Skeleton death frame " << j << std::endl;
        }
        m_SkeletonDeathTextures.push_back(texture);

        if (!texture.loadFromFile("Images/Reaper_Dying/_Reaper_Man_Dying_" + std::to_string(j) + ".png")) {
            std::cerr << "Failed to load Reaper death frame " << j << std::endl;
        }
        m_ReaperDeathTextures.push_back(texture);

        if (!texture.loadFromFile("Images/Golem_Dying/_Golem_Dying_" + std::to_string(j) + ".png")) {
            std::cerr << "Failed to load Golem death frame " << j << std::endl;
        }
        m_GolemDeathTextures.push_back(texture);

        if (!texture.loadFromFile("Images/Minotaur_Dying/_Minotaur_Dying_" + std::to_string(j) + ".png")) {
            std::cerr << "Failed to load Minotaur death frame " << j << std::endl;
        }
        m_MinotaurDeathTextures.push_back(texture);

        if (!texture.loadFromFile("Images/Ogre_Dying/_Ogre_Dying_" + std::to_string(j) + ".png")) {
            std::cerr << "Failed to load Ogre death frame " << j << std::endl;
        }
        m_OgreDeathTextures.push_back(texture);
        #endif
    }
}

void MonsterEntityView::Update(const IGameSubject &subject)
{
    // Cast the subject (which is of type IGameSubject) to a const MonsterEntity*.
    // This assumes that subject is a type of MonsterEntity or a derived class (e.g., MonsterEntityDecorator).
    // Then, call GetBaseMonsterEntity() to retrieve the base MonsterEntity pointer that the decorator wraps.
    // The final result is the actual base MonsterEntity pointer, not the decorator object itself.
    const MonsterEntity *monsterEntityPtr = (dynamic_cast<const MonsterEntity *>(&subject))->GetBaseMonsterEntity();

    if (!monsterEntityPtr)
    {
        //std::cout << "MonsterEntityView::Update() - Not a MonsterEntity\n";
        return;
    }

    // Remove dead monsters
    auto it = m_MonsterEntitySubjects.begin();
    while (it != m_MonsterEntitySubjects.end())
    {
        if (it->first == nullptr)  // If the pointer is invalid
        {
            it = m_MonsterEntitySubjects.erase(it);
        }
        else
        {
            ++it;
        }
    }

    if (monsterEntityPtr)
    {
        // Check if monster already exists in the subject data
        // If not, create a new data, give it a texture based on its type
        // If it does, update the existing data
        auto it = m_MonsterEntitySubjects.find(monsterEntityPtr);
        
        if (it == m_MonsterEntitySubjects.end())
        {
            MonsterEntityData data;
            SetTemplateMonsterSprite(data, monsterEntityPtr->GetType());
            data.sprite.setPosition(monsterEntityPtr->GetPosition());
            data.type = monsterEntityPtr->GetType();
            data.health = monsterEntityPtr->GetHealth();
            data.maxHealth = monsterEntityPtr->GetMaxHealth();
            data.speed = monsterEntityPtr->GetSpeed();
            data.level = monsterEntityPtr->GetLevel();
            data.strength = monsterEntityPtr->GetStrength();
            data.reward = monsterEntityPtr->GetReward();
            data.activeMonsterFrameIndex = monsterEntityPtr->GetActiveFrameIndex();
            data.dyingMonsterFrameIndex = monsterEntityPtr->GetDyingFrameIndex();
            data.isDying = monsterEntityPtr->GetIsDying();
            data.isDead = monsterEntityPtr->GetIsDead();
            data.isTemplate = monsterEntityPtr->GetIsTemplate();
            m_MonsterEntitySubjects[monsterEntityPtr] = data;
        }
        else
        {
            // Update the exising monster data if it has changed
            MonsterEntityData &data = it->second;
            if (data.sprite.getPosition() != monsterEntityPtr->GetPosition())
            {
                data.sprite.setPosition(monsterEntityPtr->GetPosition());
            }
            if (data.health != monsterEntityPtr->GetHealth())
            {
                data.health = monsterEntityPtr->GetHealth();
            }
            if (data.activeMonsterFrameIndex != monsterEntityPtr->GetActiveFrameIndex())
            {
                data.activeMonsterFrameIndex = monsterEntityPtr->GetActiveFrameIndex();
            }
            if (data.dyingMonsterFrameIndex != monsterEntityPtr->GetDyingFrameIndex())
            {
                data.dyingMonsterFrameIndex = monsterEntityPtr->GetDyingFrameIndex();
            }
            if (data.isDying != monsterEntityPtr->GetIsDying())
            {
                data.isDying = monsterEntityPtr->GetIsDying();
            }
            if (data.isDead != monsterEntityPtr->GetIsDead())
            {
                data.isDead = monsterEntityPtr->GetIsDead();
            }
            if (data.isTemplate != monsterEntityPtr->GetIsTemplate())
            {
                data.isTemplate = monsterEntityPtr->GetIsTemplate();
            }

        }
    }
}

void MonsterEntityView::Draw()
{
    for (const auto &pair : m_MonsterEntitySubjects)
    {
        const MonsterEntityData &data = pair.second;

        if (!m_isHoveringOnTower || !data.isTemplate)
        {
            m_Window.draw(data.sprite);
        }
    }
}

void MonsterEntityView::SetTemplateMonsterSprite(MonsterEntityData &data, MonsterGeneratorData::MonsterType type)
{
    switch (type)
    {
        case MonsterGeneratorData::MonsterType::Skeleton:
            data.sprite.setTexture(m_SkeletonTextures[0]);
            break;
        case MonsterGeneratorData::MonsterType::Reaper:
            data.sprite.setTexture(m_ReaperTextures[0]);
            break;
        case MonsterGeneratorData::MonsterType::Golem:
            data.sprite.setTexture(m_GolemTextures[0]);
            break;
        case MonsterGeneratorData::MonsterType::Minotaur:
            data.sprite.setTexture(m_MinotaurTextures[0]);
            break;
        case MonsterGeneratorData::MonsterType::Ogre:
            data.sprite.setTexture(m_OgreTextures[0]);
            break;
        default:
            std::cerr << "MonsterEntityView::SetTemplateMonsterSprite() - Invalid monster type\n";
            break;
    }
    // Set common properties
    data.sprite.setScale(Vector2f(0.08f, 0.08f));
    data.sprite.setOrigin(data.sprite.getLocalBounds().width / 2, data.sprite.getLocalBounds().height / 2);
}

void MonsterEntityView::SetMonsterTexture(MonsterEntityData &data, MonsterGeneratorData::MonsterType type)
{
    switch (type)
    {
        case MonsterGeneratorData::MonsterType::Skeleton:
            if (data.isDying)
            {
                data.sprite.setTexture(m_SkeletonDeathTextures[data.dyingMonsterFrameIndex]);
            }
            else
            {
                data.sprite.setTexture(m_SkeletonTextures[data.activeMonsterFrameIndex]);
            }
            break;
        case MonsterGeneratorData::MonsterType::Reaper:
            if (data.isDying)
            {
                data.sprite.setTexture(m_ReaperDeathTextures[data.dyingMonsterFrameIndex]);
            }
            else
            {
                data.sprite.setTexture(m_ReaperTextures[data.activeMonsterFrameIndex]);
            }
            break;
        case MonsterGeneratorData::MonsterType::Golem:
            if (data.isDying)
            {
                data.sprite.setTexture(m_GolemDeathTextures[data.dyingMonsterFrameIndex]);
            }
            else
            {
                data.sprite.setTexture(m_GolemTextures[data.activeMonsterFrameIndex]);
            }
            break;
        case MonsterGeneratorData::MonsterType::Minotaur:
            if (data.isDying)
            {
                data.sprite.setTexture(m_MinotaurDeathTextures[data.dyingMonsterFrameIndex]);
            }
            else
            {
                data.sprite.setTexture(m_MinotaurTextures[data.activeMonsterFrameIndex]);
            }
            break;
        case MonsterGeneratorData::MonsterType::Ogre:
            if (data.isDying)
            {
                data.sprite.setTexture(m_OgreDeathTextures[data.dyingMonsterFrameIndex]);
            }
            else
            {
                data.sprite.setTexture(m_OgreTextures[data.activeMonsterFrameIndex]);
            }
            break;
        default:
            std::cerr << "MonsterEntityView::SetMonsterTexture() - Invalid monster type\n";
            break;
    }
}

void MonsterEntityView::RemoveMonster(const MonsterEntity* monsterPtr)
{
    if (monsterPtr)  // Ensure the pointer is valid
    {
        const MonsterEntity* monsterBasePtr = monsterPtr->GetBaseMonsterEntity();
        m_MonsterEntitySubjects.erase(monsterBasePtr);
    }
    else
    {
        //std::cerr << "MonsterEntityView::RemoveMonster() - Invalid monster pointer\n";
    }
}

MonsterEntityView::MonsterEntityData *MonsterEntityView::GetMonsterEntityData(const MonsterEntity *monsterPtr)
{
    const MonsterEntity* monsterBasePtr = monsterPtr->GetBaseMonsterEntity();
    auto it = m_MonsterEntitySubjects.find(monsterBasePtr);
    if (it != m_MonsterEntitySubjects.end())
    {
        return &it->second;
    }
    return nullptr;
}

int MonsterEntityView::GetActiveTextureArraySize(MonsterGeneratorData::MonsterType type)
{
    switch (type)
    {
        case MonsterGeneratorData::MonsterType::Skeleton:
            return m_SkeletonTextures.size();
        case MonsterGeneratorData::MonsterType::Reaper:
            return m_ReaperTextures.size();
        case MonsterGeneratorData::MonsterType::Golem:
            return m_GolemTextures.size();
        case MonsterGeneratorData::MonsterType::Minotaur:
            return m_MinotaurTextures.size();
        case MonsterGeneratorData::MonsterType::Ogre:
            return m_OgreTextures.size();
        default:
            std::cerr << "MonsterEntityView::GetTextureArraySize() - Invalid monster type\n";
            return 0;
    }
}


int MonsterEntityView::GetDyingTextureArraySize(MonsterGeneratorData::MonsterType type)
{
    switch (type)
    {
        case MonsterGeneratorData::MonsterType::Skeleton:
            return m_SkeletonDeathTextures.size();
        case MonsterGeneratorData::MonsterType::Reaper:
            return m_ReaperDeathTextures.size();
        case MonsterGeneratorData::MonsterType::Golem:
            return m_GolemDeathTextures.size();
        case MonsterGeneratorData::MonsterType::Minotaur:
            return m_MinotaurDeathTextures.size();
        case MonsterGeneratorData::MonsterType::Ogre:
            return m_OgreDeathTextures.size();
        default:
            std::cerr << "MonsterEntityView::GetDyingTextureArraySize() - Invalid monster type\n";
            return 0;
    }
}
