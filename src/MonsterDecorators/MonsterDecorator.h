#ifndef MONSTER_DECORATOR_H
#define MONSTER_DECORATOR_H

#include "../Entities/MonsterEntity.h"
#include <memory>

/**
 * @class MonsterEntityDecorator
 * @brief A decorator class that extends the functionality of a `MonsterEntity` object.
 * 
 * The `MonsterEntityDecorator` class is used to modify or add additional behaviors to a `MonsterEntity` object while maintaining the original interface. 
 * It follows the Decorator design pattern to dynamically add features to the `MonsterEntity` without modifying its base class.
 * 
 * In addition to the attributes and methods of `MonsterEntity`, this decorator forwards observer management operations to the decorated monster:
 * - `AddObserver()`: Adds an observer to the decorated monster.
 * - `RemoveObserver()`: Removes a specific observer from the decorated monster.
 * - `RemoveAllObservers()`: Removes all observers from the decorated monster.
 * 
 * @note The class uses a `std::unique_ptr` to manage the lifecycle of the decorated monster object.
 */
class SpeedDebuffDecorator;

class MonsterEntityDecorator : public MonsterEntity
{
protected:
    std::unique_ptr<MonsterEntity> m_decoratedMonster;

public:
    MonsterEntityDecorator(std::unique_ptr<MonsterEntity> monsterPtr)
        : MonsterEntity(monsterPtr->GetType(), monsterPtr->GetLevel())
        , m_decoratedMonster(std::move(monsterPtr))
    {}

    virtual ~MonsterEntityDecorator() = default;

    void AddObserver(IGameObserver* observer) override 
    {
        m_decoratedMonster->AddObserver(observer);
    }

    void RemoveObserver(IGameObserver* observer) override 
    {
        m_decoratedMonster->RemoveObserver(observer);
    }

    void RemoveAllObservers() override
    {
        m_decoratedMonster->RemoveAllObservers();
    }

    void NotifyStatsChanged() override
    {
        m_decoratedMonster->NotifyStatsChanged();
    }    

    std::unique_ptr<MonsterEntity> GetDecoratedMonster()
    {
        return std::move(m_decoratedMonster);
    }

    MonsterEntity* GetDecoratedMonsterRef() const
    {
        return m_decoratedMonster.get();
    }

    void SetDecoratedMonster(std::unique_ptr<MonsterEntity> monsterPtr)
    {
        m_decoratedMonster = std::move(monsterPtr);
    }

    const MonsterEntity* GetBaseMonsterEntity() const override
    {
        // recursively unwrap all decorators until you get the true base instance
        return m_decoratedMonster ? m_decoratedMonster->GetBaseMonsterEntity() : this;
    }

    std::unique_ptr<MonsterEntity> ExtractBaseMonsterUniquePointer()
    {
        return std::move(m_decoratedMonster); // Transfers ownership
    }

    void SetPosition(const sf::Vector2f& position) override
    {
        m_decoratedMonster->SetPosition(position);
    }

    void Move(const sf::Vector2f& offset) override
    {
        m_decoratedMonster->Move(offset);
    }

    void SetType(MonsterGeneratorData::MonsterType type) override
    { 
        m_decoratedMonster->SetType(type);
    }

    void SetHealth(float health) override
    { 
        m_decoratedMonster->SetHealth(health);
    }

    void SetMaxHealth(float maxHealth) override
    { 
        m_decoratedMonster->SetMaxHealth(maxHealth);
    }

    void SetSpeed(float speed) override
    { 
        m_decoratedMonster->SetSpeed(speed);
    }

    void SetLevel(int level) override
    { 
        m_decoratedMonster->SetLevel(level);
    }

    void SetStrength(int strength) override
    { 
        m_decoratedMonster->SetStrength(strength);
    }

    void SetReward(int reward) override
    { 
        m_decoratedMonster->SetReward(reward);
    }

    void SetCurrentPathIndex(size_t index) override
    { 
        m_decoratedMonster->SetCurrentPathIndex(index);
    }

    void SetIsDying(bool isDying) override
    { 
        m_decoratedMonster->SetIsDying(isDying);
    }

    void SetIsDead(bool isDead) override
    { 
        m_decoratedMonster->SetIsDead(isDead);
    }

    void SetIsTemplate(bool isTemplate) override
    { 
        m_decoratedMonster->SetIsTemplate(isTemplate);
    }

    void SetIsOnSlowDebuff(bool isOnSlowDebuff) override
    { 
        m_decoratedMonster->SetIsOnSlowDebuff(isOnSlowDebuff);
    }

    void SetIsOnBurnEffect(bool isOnBurnEffect) override
    { 
        m_decoratedMonster->SetIsOnBurnEffect(isOnBurnEffect);
    }

    void IncrementActiveFrameIndex(int indexLimit) override
    {
        m_decoratedMonster->IncrementActiveFrameIndex(indexLimit);
    }

    void IncrementDyingFrameIndex(int indexLimit) override
    {
        m_decoratedMonster->IncrementDyingFrameIndex(indexLimit);
    }

    MonsterGeneratorData::MonsterType GetType() const override
    { 
        return m_decoratedMonster->GetType(); 
    }

    Vector2f GetPosition() const override
    {
        return m_decoratedMonster->GetPosition();
    }

    float GetHealth() const override
    {
        return m_decoratedMonster->GetHealth(); 
    }

    float GetMaxHealth() const override
    { 
        return m_decoratedMonster->GetMaxHealth(); 
    }

    float GetSpeed() const override
    { 
        return m_decoratedMonster->GetSpeed(); 
    }

    int GetLevel() const override
    { 
        return m_decoratedMonster->GetLevel(); 
    }

    int GetStrength() const override
    { 
        return m_decoratedMonster->GetStrength(); 
    }

    int GetReward() const override
    { 
        return m_decoratedMonster->GetReward(); 
    }

    size_t GetCurrentPathIndex() const override
    { 
        return m_decoratedMonster->GetCurrentPathIndex(); 
    }

    int GetActiveFrameIndex() const override
    { 
        return m_decoratedMonster->GetActiveFrameIndex(); 
    }

    int GetDyingFrameIndex() const override
    { 
        return m_decoratedMonster->GetDyingFrameIndex(); 
    }

    bool GetIsDying() const override
    { 
        return m_decoratedMonster->GetIsDying(); 
    }

    bool GetIsFinishedDying() const override
    { 
        return m_decoratedMonster->GetIsFinishedDying(); 
    }

    bool GetIsDead() const override
    {
        return m_decoratedMonster->GetIsDead(); 
    }

    bool GetIsTemplate() const  override
    { 
        return m_decoratedMonster->GetIsTemplate(); 
    }

    bool GetIsOnSlowDebuff() const override
    { 
        return m_decoratedMonster->GetIsOnSlowDebuff(); 
    }

    bool GetIsOnBurnEffect() const override
    { 
        return m_decoratedMonster->GetIsOnBurnEffect(); 
    }
};

#endif