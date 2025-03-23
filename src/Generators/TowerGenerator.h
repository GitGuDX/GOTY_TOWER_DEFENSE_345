#ifndef TOWER_GENERATOR_H
#define TOWER_GENERATOR_H

#include "TowerGeneratorData.h"
#include <vector>
#include <SFML/Graphics.hpp>

class TowerEntity;

class TowerGenerator
{
public:
    TowerGenerator() = default;
    ~TowerGenerator() = default;

    TowerEntity GenerateTower(TowerGeneratorData::TowerType type)
    {
        TowerEntity tempTower(type);
        InitializeStat(tempTower);
        return tempTower;
    }

    void InitializeStat(TowerEntity& tower)
    {
        // Access the appropriate struct based on the tower type
        int maxLevel;
        float range;
        float maxCooldown;
        float damage;
        float speed;
        int cost;
        if (tower.GetType() == TowerGeneratorData::TowerType::Basic) 
        {
            maxLevel = TowerGeneratorData::TowerTypeData::Basic::iMaxLevel;
            range = TowerGeneratorData::TowerTypeData::Basic::fRange;
            maxCooldown = TowerGeneratorData::TowerTypeData::Basic::fMaxCooldown;
            damage = TowerGeneratorData::TowerTypeData::Basic::fDamage;
            speed = TowerGeneratorData::TowerTypeData::Basic::fspeed;
            cost = TowerGeneratorData::TowerTypeData::Basic::iCost;
        }
        else if (tower.GetType() == TowerGeneratorData::TowerType::Sniper) 
        {
            maxLevel = TowerGeneratorData::TowerTypeData::Sniper::iMaxLevel;
            range = TowerGeneratorData::TowerTypeData::Sniper::fRange;
            maxCooldown = TowerGeneratorData::TowerTypeData::Sniper::fMaxCooldown;
            damage = TowerGeneratorData::TowerTypeData::Sniper::fDamage;
            speed = TowerGeneratorData::TowerTypeData::Sniper::fspeed;
            cost = TowerGeneratorData::TowerTypeData::Sniper::iCost;
        }
        else if (tower.GetType() == TowerGeneratorData::TowerType::Rapid) 
        {
            maxLevel = TowerGeneratorData::TowerTypeData::Rapid::iMaxLevel;
            range = TowerGeneratorData::TowerTypeData::Rapid::fRange;
            maxCooldown = TowerGeneratorData::TowerTypeData::Rapid::fMaxCooldown;
            damage = TowerGeneratorData::TowerTypeData::Rapid::fDamage;
            speed = TowerGeneratorData::TowerTypeData::Rapid::fspeed;
            cost = TowerGeneratorData::TowerTypeData::Rapid::iCost;
        }
        else if (tower.GetType() == TowerGeneratorData::TowerType::FlameThrower) 
        {
            maxLevel = TowerGeneratorData::TowerTypeData::FlameThrower::iMaxLevel;
            range = TowerGeneratorData::TowerTypeData::FlameThrower::fRange;
            maxCooldown = TowerGeneratorData::TowerTypeData::FlameThrower::fMaxCooldown;
            damage = TowerGeneratorData::TowerTypeData::FlameThrower::fDamage;
            speed = TowerGeneratorData::TowerTypeData::FlameThrower::fspeed;
            cost = TowerGeneratorData::TowerTypeData::FlameThrower::iCost;
        }
        else 
        {
            std::cerr << "Error: Invalid tower type" << std::endl;
        }
        tower.SetMaxLevel(maxLevel);
        tower.SetRange(range);
        tower.SetMaxCooldown(maxCooldown);
        tower.SetDamage(damage);
        tower.SetSpeed(speed);
        tower.SetCost(cost);
    }
};


#endif // !TOWER_GENERATOR_H