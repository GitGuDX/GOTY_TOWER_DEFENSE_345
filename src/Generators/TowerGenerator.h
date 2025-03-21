#ifndef TOWER_GENERATOR_H
#define TOWER_GENERATOR_H

#include "TowerGeneratorData.h"
#include <vector>
#include <SFML/Graphics.hpp>

class TowerEntity;

class TowerGenerator
{
public:

    TowerGenerator();
    ~TowerGenerator() = default;

    // enum class TowerType {
    //     Basic,
    //     Sniper,
    //     Rapid
    // };

    // struct TowerTypeData
    // {
    //     struct Basic
    //     {
    //         static constexpr float fRange = 300.0f;
    //         static constexpr float fMaxCooldown = 1.0f;
    //         static constexpr float fDamage = 10.0f;
    //         static constexpr float fspeed = 300.f;
    //         static constexpr int iCost = 100;
    //     };

    //     struct Sniper
    //     {
    //         static constexpr float fRange = 600.0f;
    //         static constexpr float fMaxCooldown = 3.0f;
    //         static constexpr float fDamage = 50.0f;
    //         static constexpr float fspeed = 800.f;
    //         static constexpr int iCost = 300;
    //     };

    //     struct Rapid
    //     {
    //         static constexpr float fRange = 170.0f;
    //         static constexpr float fMaxCooldown = 0.14f;
    //         static constexpr float fDamage = 5.0f;
    //         static constexpr float fspeed = 400.f;
    //         static constexpr int iCost = 200;
    //     };
    // };


    TowerEntity GenerateRapidTowerTemplate();

    TowerEntity GenerateSniperTowerTemplate();

    TowerEntity GenerateTower(TowerGeneratorData::TowerType type);


};


#endif // !TOWER_GENERATOR_H