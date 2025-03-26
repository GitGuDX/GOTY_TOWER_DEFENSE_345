#include "HealthBarView.h"

HealthBarView::HealthBarView(RenderWindow &window)
    : m_Window(window)
    , m_HealthBarPositionOffSet(25)
{
}

void HealthBarView::Update(const IGameSubject &subject)
{
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
            HealthBarData data;

            sf::Vector2f enemyPos = monsterEntityPtr->GetPosition();
            data.shape.setPosition(enemyPos.x, enemyPos.y - m_HealthBarPositionOffSet);
            data.health = monsterEntityPtr->GetHealth();

            data.maxHealth = monsterEntityPtr->GetMaxHealth();

            InitializeShape(data);

            m_MonsterEntitySubjects[monsterEntityPtr] = data;
        }
        else
        {
            // Update the exising monster data if it has changed
            HealthBarData &data = it->second;
            if (data.shape.getPosition() != monsterEntityPtr->GetPosition())
            {
                sf::Vector2f enemyPos = monsterEntityPtr->GetPosition();
                data.shape.setPosition(enemyPos.x, enemyPos.y - m_HealthBarPositionOffSet);
            }
            if (data.health != monsterEntityPtr->GetHealth())
            {
                if (monsterEntityPtr->GetHealth() >= 0)
                {
                    data.health = monsterEntityPtr->GetHealth();
                }
                else
                {
                    data.health = 0.f;
                }
                
                UpdateShape(data);
            }
        }
    }
}

void HealthBarView::Draw()
{
    for (const auto &pair : m_MonsterEntitySubjects)
    {
        const HealthBarData &data = pair.second;

        m_Window.draw(data.shape);
    }
}

void HealthBarView::InitializeShape(HealthBarData &data)
{
    data.shape.setSize(sf::Vector2f(40.0f, 5.0f));
    data.shape.setFillColor(sf::Color::Green);
    data.shape.setOrigin(data.shape.getSize().x / 2, data.shape.getSize().y / 2);
}

void HealthBarView::UpdateShape(HealthBarData &data)
{
    float healthPercentage = data.health / data.maxHealth;
    data.shape.setSize(sf::Vector2f(40.0f * healthPercentage, 5.0f));
    data.shape.setFillColor(healthPercentage > 0.5 ? sf::Color::Green : sf::Color::Red);
    data.shape.setOrigin(data.shape.getSize().x / 2, data.shape.getSize().y / 2);
}

void HealthBarView::RemoveMonster(const MonsterEntity *monsterPtr)
{
    if (monsterPtr)  // Ensure the pointer is valid
    {
        const MonsterEntity* monsterBasePtr = monsterPtr->GetBaseMonsterEntity();
        //std::cout << "subject size before removal: " << m_MonsterEntitySubjects.size() << std::endl;
        m_MonsterEntitySubjects.erase(monsterBasePtr);
        //std::cout << "subject size after removal: " << m_MonsterEntitySubjects.size() << std::endl;
    }
    else
    {
        std::cerr << "MonsterEntityView::RemoveMonster() - Invalid monster pointer\n";
    }
}
