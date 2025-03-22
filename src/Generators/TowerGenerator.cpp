#include "TowerGenerator.h"
#include "../Entities/TowerEntity.h"

TowerGenerator::TowerGenerator()
{
}

TowerEntity TowerGenerator::GenerateRapidTowerTemplate()
{
    return TowerEntity(TowerGeneratorData::TowerType::Rapid);  
}

TowerEntity TowerGenerator::GenerateSniperTowerTemplate()
{
    return TowerEntity(TowerGeneratorData::TowerType::Sniper);
}

TowerEntity TowerGenerator::GenerateFlameThrowerTowerTemplate()
{
    return TowerEntity(TowerGeneratorData::TowerType::FlameThrower);
}

TowerEntity TowerGenerator::GenerateTower(TowerGeneratorData::TowerType type)
{
    return TowerEntity(type);
}
