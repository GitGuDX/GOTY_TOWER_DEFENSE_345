#include "TowerGenerator.h"
#include "../Entities/TowerEntity.h"

TowerGenerator::TowerGenerator()
{
}

TowerEntity TowerGenerator::GenerateRapidTowerTemplate()
{
    return TowerEntity(TowerGenerator::TowerType::Rapid);
}

TowerEntity TowerGenerator::GenerateSniperTowerTemplate()
{
    return TowerEntity(TowerGenerator::TowerType::Sniper);
}

TowerEntity TowerGenerator::GenerateFlameThrowerTowerTemplate()
{
    return TowerEntity(TowerGenerator::TowerType::FlameThrower);
}

TowerEntity TowerGenerator::GenerateTower(TowerType type)
{
    return TowerEntity(type);
}
