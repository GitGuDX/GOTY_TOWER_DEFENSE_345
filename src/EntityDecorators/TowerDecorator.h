#ifndef TOWER_DECORATOR_H
#define TOWER_DECORATOR_H

#include "../Entities/TowerEntity.h"
#include "../Generators/TowerGeneratorData.h"
#include <memory>

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

    virtual void SetTargetStrategy(TowerTargetStrategy* strategy) override
    {
        m_decoratedTower->SetTargetStrategy(strategy);
    }

    virtual MonsterEntity* SelectTarget(const std::vector<std::unique_ptr<MonsterEntity>>& enemies) const override
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
        
    void InitializeStat() override
    {
        m_decoratedTower->InitializeStat();
    }

    void SetPosition(const sf::Vector2f& position) override
    {
        m_decoratedTower->SetPosition(position);
    }

    void SetType(TowerGeneratorData::TowerType type) override
    {
        m_decoratedTower->SetType(type);
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