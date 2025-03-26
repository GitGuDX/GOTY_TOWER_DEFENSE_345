#ifndef SPEED_BOOST_DECORATOR_H
#define SPEED_BOOST_DECORATOR_H

#include "TowerDecorator.h"
#include <memory>

/**
 * @class SpeedBoostDecorator
 * @brief A decorator class that modifies the speed behavior of a `TowerEntity`.
 * 
 * The `SpeedBoostDecorator` is a concrete decorator that enhances the speed functionality of a `TowerEntity` by multiplying its speed value with a predefined speed multiplier. This allows for increasing the speed of towers without modifying the base tower class directly.
 * 
 * Public Methods:
 * - `GetSpeed()`: Returns the modified speed value for the tower by multiplying the original speed with the `fSpeedMultiplier` from `TowerGeneratorData::UpgradeRate`.
 * 
 * Private Attributes:
 * - `m_decoratedTower`: A unique pointer to the decorated `TowerEntity`, which holds the core functionality.
 */
class SpeedBoostDecorator : public TowerEntityDecorator
{
public:
    SpeedBoostDecorator(std::unique_ptr<TowerEntity> tower)
        : TowerEntityDecorator(std::move(tower))
    {}

    float GetSpeed() const override
    {
        return m_decoratedTower->GetSpeed() * TowerGeneratorData::UpgradeRate::fSpeedMultiplier;
    }
};

#endif