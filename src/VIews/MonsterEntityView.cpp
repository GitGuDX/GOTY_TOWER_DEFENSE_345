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
    const MonsterEntity* monsterEntityPtr = dynamic_cast<const MonsterEntity*>(&subject);

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

        }
    }
}

void MonsterEntityView::Draw()
{
    for (const auto &pair : m_MonsterEntitySubjects)
    {
        const MonsterEntityData &data = pair.second;

        m_Window.draw(data.sprite);
    }
}

void MonsterEntityView::SetTemplateMonsterSprite(MonsterEntityData &data, MonsterGenerator::MonsterType type)
{
    switch (type)
    {
        case MonsterGenerator::MonsterType::Skeleton:
            data.sprite.setTexture(m_SkeletonTextures[0]);
            break;
        case MonsterGenerator::MonsterType::Reaper:
            data.sprite.setTexture(m_ReaperTextures[0]);
            break;
        case MonsterGenerator::MonsterType::Golem:
            data.sprite.setTexture(m_GolemTextures[0]);
            break;
        case MonsterGenerator::MonsterType::Minotaur:
            data.sprite.setTexture(m_MinotaurTextures[0]);
            break;
        case MonsterGenerator::MonsterType::Ogre:
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

void MonsterEntityView::SetMonsterTexture(MonsterEntityData &data, MonsterGenerator::MonsterType type)
{
    switch (type)
    {
        case MonsterGenerator::MonsterType::Skeleton:
            if (data.isDying)
            {
                data.sprite.setTexture(m_SkeletonDeathTextures[data.dyingMonsterFrameIndex]);
            }
            else
            {
                data.sprite.setTexture(m_SkeletonTextures[data.activeMonsterFrameIndex]);
            }
            break;
        case MonsterGenerator::MonsterType::Reaper:
            if (data.isDying)
            {
                data.sprite.setTexture(m_ReaperDeathTextures[data.dyingMonsterFrameIndex]);
            }
            else
            {
                data.sprite.setTexture(m_ReaperTextures[data.activeMonsterFrameIndex]);
            }
            break;
        case MonsterGenerator::MonsterType::Golem:
            if (data.isDying)
            {
                data.sprite.setTexture(m_GolemDeathTextures[data.dyingMonsterFrameIndex]);
            }
            else
            {
                data.sprite.setTexture(m_GolemTextures[data.activeMonsterFrameIndex]);
            }
            break;
        case MonsterGenerator::MonsterType::Minotaur:
            if (data.isDying)
            {
                data.sprite.setTexture(m_MinotaurDeathTextures[data.dyingMonsterFrameIndex]);
            }
            else
            {
                data.sprite.setTexture(m_MinotaurTextures[data.activeMonsterFrameIndex]);
            }
            break;
        case MonsterGenerator::MonsterType::Ogre:
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
        m_MonsterEntitySubjects.erase(monsterPtr);
    }
    else
    {
        std::cerr << "MonsterEntityView::RemoveMonster() - Invalid monster pointer\n";
    }
}

MonsterEntityView::MonsterEntityData *MonsterEntityView::GetMonsterEntityData(const MonsterEntity *monster)
{
    auto it = m_MonsterEntitySubjects.find(monster);
    if (it != m_MonsterEntitySubjects.end())
    {
        return &it->second;
    }
    return nullptr;
}

int MonsterEntityView::GetActiveTextureArraySize(MonsterGenerator::MonsterType type)
{
    switch (type)
    {
        case MonsterGenerator::MonsterType::Skeleton:
            return m_SkeletonTextures.size();
        case MonsterGenerator::MonsterType::Reaper:
            return m_ReaperTextures.size();
        case MonsterGenerator::MonsterType::Golem:
            return m_GolemTextures.size();
        case MonsterGenerator::MonsterType::Minotaur:
            return m_MinotaurTextures.size();
        case MonsterGenerator::MonsterType::Ogre:
            return m_OgreTextures.size();
        default:
            std::cerr << "MonsterEntityView::GetTextureArraySize() - Invalid monster type\n";
            return 0;
    }
}


int MonsterEntityView::GetDyingTextureArraySize(MonsterGenerator::MonsterType type)
{
    switch (type)
    {
        case MonsterGenerator::MonsterType::Skeleton:
            return m_SkeletonDeathTextures.size();
        case MonsterGenerator::MonsterType::Reaper:
            return m_ReaperDeathTextures.size();
        case MonsterGenerator::MonsterType::Golem:
            return m_GolemDeathTextures.size();
        case MonsterGenerator::MonsterType::Minotaur:
            return m_MinotaurDeathTextures.size();
        case MonsterGenerator::MonsterType::Ogre:
            return m_OgreDeathTextures.size();
        default:
            std::cerr << "MonsterEntityView::GetDyingTextureArraySize() - Invalid monster type\n";
            return 0;
    }
}
