#ifndef TOWER_DECORATOR_H
#define TOWER_DECORATOR_H

#include "../Entities/TowerEntity.h"
#include "../Generators/TowerGeneratorData.h"

/**
 * @class TowerEntityDecorator
 * @brief A decorator class that adds additional functionality to a `TowerEntity`.
 * 
 * The `TowerEntityDecorator` class is a base decorator for the `TowerEntity`, which allows adding extra behavior or functionality without modifying the original `TowerEntity`. It delegates the calls to the decorated `TowerEntity` while allowing the behavior to be extended in subclasses.
 * This class supports various actions like setting target strategies, selecting targets, observing changes, and notifying about changes in stats.
 * 
 * Public Methods:
 * - `SetTargetStrategy(TowerTargetStrategy* strategy)`: Delegates setting the target strategy to the decorated tower.
 * - `SelectTarget(const std::vector<std::unique_ptr<MonsterEntity>>& enemies)`: Delegates the selection of a target to the decorated tower.
 * - `AddObserver(IGameObserver* observer)`: Adds an observer to the decorated tower.
 * - `RemoveObserver(IGameObserver* observer)`: Removes an observer from the decorated tower.
 * - `NotifyStatsChanged()`: Notifies the decorated tower about stats changes.
 * - `GetBaseTowerEntity()`: Recursively unwraps all decorators to return the original base `TowerEntity`.
 * 
 * Private Attributes:
 * - `m_decoratedTower`: A unique pointer to the decorated `TowerEntity`, which holds the core functionality.
 */
class TowerEntityDecorator : public TowerEntity
{
protected:
    std::unique_ptr<TowerEntity> m_decoratedTower;

public:
    TowerEntityDecorator(std::unique_ptr<TowerEntity> tower)
        : TowerEntity(tower->GetType())
        , m_decoratedTower(std::move(tower))
    {}

    virtual ~TowerEntityDecorator() = default;

    void SetTargetStrategy(TowerTargetStrategy* strategy) override
    {
        m_decoratedTower->SetTargetStrategy(strategy);
    }

    MonsterEntity* SelectTarget(const std::vector<std::unique_ptr<MonsterEntity>>& enemies) const override
    {
        return m_decoratedTower->SelectTarget(enemies);
    }

    void AddObserver(IGameObserver* observer) override
    {
        m_decoratedTower->AddObserver(observer);
    }

    void RemoveObserver(IGameObserver* observer) override
    {
        m_decoratedTower->RemoveObserver(observer);
    }

    void NotifyStatsChanged() override
    {
        m_decoratedTower->NotifyStatsChanged();
    }

    const TowerEntity* GetBaseTowerEntity() const override
    {
        // recursively unwrap all decorators until you get the true base instance
        return m_decoratedTower ? m_decoratedTower->GetBaseTowerEntity() : this;
    }

    void SetPosition(const sf::Vector2f& position) override
    {
        m_decoratedTower->SetPosition(position);
    }

    void SetType(TowerGeneratorData::TowerType type) override
    {
        m_decoratedTower->SetType(type);
    }

    void SetMaxLevel(int maxLevel) override
    {
        m_decoratedTower->SetMaxLevel(maxLevel);
    }

    void SetRange(float range) override
    {
        m_decoratedTower->SetRange(range);
    }

    void SetMaxCooldown(float cooldown) override
    {
        m_decoratedTower->SetMaxCooldown(cooldown);
    }

    void SetDamage(float damage) override
    {
        m_decoratedTower->SetDamage(damage);
    }

    void SetSpeed(float speed) override
    {
        m_decoratedTower->SetSpeed(speed);
    }

    void SetCost(int cost) override
    {
        m_decoratedTower->SetCost(cost);
    }

    void SetLevel(int level) override
    {
        m_decoratedTower->SetLevel(level);
    }

    void SetIsTemplate(bool isTemplate) override
    {
        m_decoratedTower->SetIsTemplate(isTemplate);
    }

    TowerGeneratorData::TowerType GetType() const override 
    { 
        return m_decoratedTower->GetType(); 
    }

    Vector2f GetPosition() const override
    {
        return m_decoratedTower->GetPosition();
    }

    float GetRange() const override 
    { 
        return m_decoratedTower->GetRange(); 
    }

    float GetMaxCooldown() const override 
    { 
        return m_decoratedTower->GetMaxCooldown(); 
    }

    float GetShootCooldown() const override
    {
        return m_decoratedTower->GetShootCooldown();
    }

    float GetDamage() const override 
    { 
        return m_decoratedTower->GetDamage(); 
    }

    float GetSpeed() const override 
    { 
        return m_decoratedTower->GetSpeed(); 
    }

    int GetCost() const override 
    { 
        return m_decoratedTower->GetCost(); 
    }

    int GetLevel() const override 
    { 
        return m_decoratedTower->GetLevel(); 
    }

    bool GetIsTemplate() const override 
    { 
        return m_decoratedTower->GetIsTemplate(); 
    }

    bool CanShoot() const override 
    { 
        return m_decoratedTower->CanShoot(); 
    }

    void ResetCooldown() override 
    { 
        m_decoratedTower->ResetCooldown(); 
    }

    void UpdateCooldown(float deltaTime) override
    { 
        m_decoratedTower->UpdateCooldown(deltaTime); 
    }

    bool CanUpgrade() const override 
    { 
        return m_decoratedTower->CanUpgrade(); 
    }

    void IncrementLevel() override
    {
        m_decoratedTower->IncrementLevel();
    }

    int GetUpgradeCost() const override
    {
        return m_decoratedTower->GetUpgradeCost();
    }
};

#endif