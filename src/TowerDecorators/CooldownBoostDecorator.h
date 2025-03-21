#ifndef COOLDOWN_BOOST_DECORATOR_H
#define COOLDOWN_BOOST_DECORATOR_H

#include "TowerDecorator.h"
#include <memory>

class CooldownBoostDecorator : public TowerEntityDecorator
{
public:
CooldownBoostDecorator(std::unique_ptr<TowerEntity> tower)
        : TowerEntityDecorator(std::move(tower))
    {}

    float GetMaxCooldown() const override
    {
        return m_decoratedTower->GetMaxCooldown() * TowerGeneratorData::UpgradeRate::fCooldownMultiplier;
    }

};

#endif