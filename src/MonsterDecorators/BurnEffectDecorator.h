#ifndef BURN_EFFECT_DECORATOR_H
#define BURN_EFFECT_DECORATOR_H

#include "MonsterDecorator.h"

/**
 * @class BurnEffectDecorator
 * @brief A decorator class that adds a burn effect to a `MonsterEntity`.
 * 
 * The `BurnEffectDecorator` class is a concrete implementation of the `MonsterEntityDecorator` that adds burn damage over time to the decorated monster.
 * It periodically applies damage to the monster based on the `m_burnDamagePerSecond` value, and continues to apply the effect for a specified duration (`m_duration`).
 * After the duration is complete, the decorator flags itself for removal.
 * 
 * @note The burn effect updates at regular intervals and removes itself once its duration has ended.
 * 
 * Public Methods:
 * - `Update(float deltaTime)`: Updates the burn effect based on elapsed time and applies burn damage every second.
 * - `IsMarkedForRemoval()`: Returns whether the burn effect is marked for removal.
 * - `ResetElapsedTime()`: Resets the elapsed time for the burn effect.
 * 
 * Private Methods:
 * - `ApplyBurnDamage()`: Applies burn damage to the decorated monster.
 * 
 * Attributes:
 * - `m_duration`: The duration for which the burn effect lasts (default: 5.0f seconds).
 * - `m_elapsedTime`: Tracks how long the burn effect has been active.
 * - `m_elapsedTimeSinceLastBurn`: Tracks time since the last burn damage was applied.
 * - `m_burnDamagePerSecond`: The amount of damage dealt to the monster per second (default: 25).
 * - `m_markedForRemoval`: A flag indicating whether the burn effect has completed and should be removed.
 */
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
            //m_decoratedMonster->SetIsOnBurnEffect(false);
            if (m_elapsedTimeSinceLastBurn >= 1.0f)
            {
                ApplyBurnDamage();
                //m_decoratedMonster->SetIsOnBurnEffect(true);
                m_elapsedTimeSinceLastBurn = 0.0f;
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