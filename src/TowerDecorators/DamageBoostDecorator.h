#ifndef DAMAGE_BOOST_DECORATOR_H
#define DAMAGE_BOOST_DECORATOR_H

#include "TowerDecorator.h"
#include <memory>

/**
 * @class DamageBoostDecorator
 * @brief A decorator class that modifies the damage behavior of a `TowerEntity`.
 * 
 * The `DamageBoostDecorator` is a concrete decorator that enhances the damage functionality of a `TowerEntity` by multiplying its damage value with a predefined damage multiplier. This allows for increasing the damage output of towers without altering the original class directly.
 * 
 * Public Methods:
 * - `GetDamage()`: Returns the modified damage value for the tower by multiplying the original damage with the `fDamageMultiplier` from `TowerGeneratorData::UpgradeRate`.
 * 
 * Private Attributes:
 * - `m_decoratedTower`: A unique pointer to the decorated `TowerEntity`, which holds the core functionality.
 */
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