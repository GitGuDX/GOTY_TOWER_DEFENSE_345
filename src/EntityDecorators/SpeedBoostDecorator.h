#ifndef SPEED_BOOST_DECORATOR_H
#define SPEED_BOOST_DECORATOR_H

#include "TowerDecorator.h"
#include <memory>

class SpeedBoostDecorator : public TowerEntityDecorator
{
public:
    SpeedBoostDecorator(std::unique_ptr<TowerEntity> tower)
        : TowerEntityDecorator(std::move(tower))
    {}

    float GetSpeed() const override
    {
        return m_decoratedTower->GetSpeed() * UpgradeRate::fSpeedMultiplier;
    }
};

#endif