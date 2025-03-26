#ifndef RANGE_BOOST_DECORATOR_H
#define RANGE_BOOST_DECORATOR_H

#include "TowerDecorator.h"
#include <memory>

/**
 * @class RangeBoostDecorator
 * @brief A decorator class that modifies the range behavior of a `TowerEntity`.
 * 
 * The `RangeBoostDecorator` is a concrete decorator that enhances the range functionality of a `TowerEntity` by multiplying its range value with a predefined range multiplier. This allows for increasing the range of towers without modifying the base tower class directly.
 * 
 * Public Methods:
 * - `GetRange()`: Returns the modified range value for the tower by multiplying the original range with the `fRangeMultiplier` from `TowerGeneratorData::UpgradeRate`.
 * 
 * Private Attributes:
 * - `m_decoratedTower`: A unique pointer to the decorated `TowerEntity`, which holds the core functionality.
 */
class RangeBoostDecorator : public TowerEntityDecorator
{
public:
    RangeBoostDecorator(std::unique_ptr<TowerEntity> tower)
        : TowerEntityDecorator(std::move(tower))
    {}

    float GetRange() const override
    {
        //std::cout << "range multipler is: " << TowerEntity::UpgradeRate::fRangeMultiplier << std::endl;
        //std::cout << "decorator base range is: " << m_decoratedTower->GetRange() << std::endl;
        return m_decoratedTower->GetRange() * TowerGeneratorData::UpgradeRate::fRangeMultiplier;
    }
};

#endif