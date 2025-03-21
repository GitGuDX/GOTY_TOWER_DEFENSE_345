#ifndef DAMAGE_BOOST_DECORATOR_H
#define DAMAGE_BOOST_DECORATOR_H

#include "TowerDecorator.h"
#include <memory>

class DamageBoostDecorator : public TowerEntityDecorator
{
public:
    DamageBoostDecorator(std::unique_ptr<TowerEntity> tower)
        : TowerEntityDecorator(std::move(tower))
    {}

    float GetDamage() const override
    {
        return m_decoratedTower->GetDamage() * TowerGeneratorData::UpgradeRate::fDamageMultiplier;
    }
};

#endif