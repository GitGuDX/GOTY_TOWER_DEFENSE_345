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

TowerEntity TowerGenerator::GenerateTower(TowerType type)
{
    return TowerEntity(type);
}
