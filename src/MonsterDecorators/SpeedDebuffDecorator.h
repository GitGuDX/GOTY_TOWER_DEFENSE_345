#ifndef SPEED_DEBUFF_DECORATOR_H
#define SPEED_DEBUFF_DECORATOR_H

#include "MonsterDecorator.h"

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
            std::cout << "Elapsed time before the update: " << m_elapsedTime << std::endl;
            m_elapsedTime += deltaTime;
            if (m_elapsedTime >= m_duration) {
                std::cout << "flagged as removal" << std::endl;
                m_markedForRemoval = true;  // Flag for removal
            }
            std::cout << "Elapsed time after the update: " << m_elapsedTime << std::endl;
        }
        //m_decoratedMonster->Update(deltaTime);  // Forward update call
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