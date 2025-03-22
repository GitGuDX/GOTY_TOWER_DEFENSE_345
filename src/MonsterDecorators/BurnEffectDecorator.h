#ifndef BURN_EFFECT_DECORATOR_H
#define BURN_EFFECT_DECORATOR_H

#include "MonsterDecorator.h"

class BurnEffectDecorator : public MonsterEntityDecorator
{
public:
    BurnEffectDecorator(std::unique_ptr<MonsterEntity> monsterPtr)
        : MonsterEntityDecorator(std::move(monsterPtr))
    {}

    void Update(float deltaTime)
    {
        if (m_markedForRemoval == false)
        {
            //std::cout << "Elapsed time before the update: " << m_elapsedTime << std::endl;
            m_elapsedTime += deltaTime;
            m_elapsedTimeSinceLastBurn += deltaTime;

            if (m_elapsedTimeSinceLastBurn >= 1.0f)
            {
                ApplyBurnDamage();
                m_elapsedTimeSinceLastBurn -= 1.0f;
            }

            if (m_elapsedTime >= m_duration) {
                //std::cout << "flagged as removal" << std::endl;
                m_markedForRemoval = true;  // Flag for removal
            }
            //std::cout << "Elapsed time after the update: " << m_elapsedTime << std::endl;
        }
    }

    bool IsMarkedForRemoval() { return m_markedForRemoval; }

    void ResetElapsedTime()
    {
        m_elapsedTime = 0.0f;
    }

private:
    void ApplyBurnDamage()
    {
        m_decoratedMonster->SetHealth(m_decoratedMonster->GetHealth() - m_burnDamagePerSecond);
    }

private:
    float m_duration = 5.0f;  // How long the slow effect lasts
    float m_elapsedTime = 0.0f;  // Tracks how long it's been active
    float m_elapsedTimeSinceLastBurn = 0.0f;
    int m_burnDamagePerSecond = 25;
    bool m_markedForRemoval = false;
};


#endif