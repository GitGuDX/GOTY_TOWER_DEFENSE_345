#ifndef COOLDOWN_BOOST_DECORATOR_H
#define COOLDOWN_BOOST_DECORATOR_H

#include "TowerDecorator.h"
#include <memory>

/**
 * @class CooldownBoostDecorator
 * @brief A decorator class that modifies the cooldown behavior of a `TowerEntity`.
 * 
 * The `CooldownBoostDecorator` is a concrete decorator that enhances the cooldown functionality of a `TowerEntity` by modifying its maximum cooldown using a predefined multiplier. It is intended to be used on a `TowerEntity` to improve or alter the cooldown mechanic without modifying the original class directly.
 * 
 * Public Methods:
 * - `GetMaxCooldown()`: Returns the modified maximum cooldown for the tower by multiplying the original cooldown with the `fCooldownMultiplier` from `TowerGeneratorData::UpgradeRate`.
 * 
 * Private Attributes:
 * - `m_decoratedTower`: A unique pointer to the decorated `TowerEntity`, which holds the core functionality.
 */
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