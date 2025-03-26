#ifndef SPEED_DEBUFF_DECORATOR_H
#define SPEED_DEBUFF_DECORATOR_H

#include "MonsterDecorator.h"

/**
 * @class SpeedDebuffDecorator
 * @brief A decorator class that applies a speed debuff to a `MonsterEntity`.
 * 
 * The `SpeedDebuffDecorator` class is a concrete implementation of the `MonsterEntityDecorator` that reduces the speed of the decorated monster by a fixed percentage (`m_speedDebuff`).
 * The speed debuff lasts for a specified duration (`m_duration`) and removes itself once the duration has expired.
 * 
 * @note The speed debuff is applied by modifying the speed of the decorated monster, and it is removed once the specified duration has ended.
 * 
 * Public Methods:
 * - `Update(float deltaTime)`: Updates the speed debuff's duration and marks it for removal once the duration has elapsed.
 * - `IsMarkedForRemoval()`: Returns whether the speed debuff is marked for removal.
 * - `GetSpeed()`: Returns the modified speed of the decorated monster after applying the debuff.
 * - `ResetElapsedTime()`: Resets the elapsed time for the debuff.
 * 
 * Private Attributes:
 * - `m_duration`: The duration for which the speed debuff lasts (default: 5.0f seconds).
 * - `m_elapsedTime`: Tracks how long the speed debuff has been active.
 * - `m_speedDebuff`: The multiplier by which the monster's speed is reduced (default: 0.5f, 50% speed reduction).
 * - `m_markedForRemoval`: A flag indicating whether the speed debuff has completed and should be removed.
 */
class SpeedDebuffDecorator : public MonsterEntityDecorator
{
public:
    SpeedDebuffDecorator(std::unique_ptr<MonsterEntity> monsterPtr)
        : MonsterEntityDecorator(std::move(monsterPtr))
    {}

    void Update(float deltaTime)
    {
        if (m_markedForRemoval == false)
        {
            //std::cout << "Elapsed time before the update: " << m_elapsedTime << std::endl;
            m_elapsedTime += deltaTime;
            if (m_elapsedTime >= m_duration) {
                //std::cout << "flagged as removal" << std::endl;
                m_markedForRemoval = true;  // Flag for removal
            }
            //std::cout << "Elapsed time after the update: " << m_elapsedTime << std::endl;
        }
    }

    bool IsMarkedForRemoval() { return m_markedForRemoval; }

    float GetSpeed() const override
    { 
        return m_decoratedMonster->GetSpeed() * m_speedDebuff; 
    }

    void ResetElapsedTime()
    {
        m_elapsedTime = 0.0f;
    }

private:
    float m_duration = 5.0f;  // How long the slow effect lasts
    float m_elapsedTime = 0.0f;  // Tracks how long it's been active
    float m_speedDebuff = 0.5f;
    bool m_markedForRemoval = false;
};

#endif