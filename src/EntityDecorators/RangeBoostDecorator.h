#ifndef RANGE_BOOST_DECORATOR_H
#define RANGE_BOOST_DECORATOR_H

#include "TowerDecorator.h"
#include <memory>

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
        return m_decoratedTower->GetRange() * TowerEntity::UpgradeRate::fRangeMultiplier;
    }
};

#endif