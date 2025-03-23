#ifndef TOWER_GENERATOR_DATA_H
#define TOWER_GENERATOR_DATA_H

namespace TowerGeneratorData {  // Renamed namespace to TowerGeneratorData
    enum class TowerType {
        Basic,
        Sniper,
        Rapid,
        FlameThrower,
    };

    struct TowerTypeData
    {
        struct Basic
        {
            static constexpr int iMaxLevel = 3;
            static constexpr float fRange = 300.0f;
            static constexpr float fMaxCooldown = 1.0f;
            static constexpr float fDamage = 10.0f;
            static constexpr float fspeed = 300.f;
            static constexpr int iCost = 100;
        };

        struct Sniper
        {
            static constexpr int iMaxLevel = 3;
            static constexpr float fRange = 600.0f;
            static constexpr float fMaxCooldown = 3.0f;
            static constexpr float fDamage = 50.0f;
            static constexpr float fspeed = 800.f;
            static constexpr int iCost = 300;
        };

        struct Rapid
        {
            static constexpr int iMaxLevel = 3;
            static constexpr float fRange = 170.0f;
            static constexpr float fMaxCooldown = 0.14f;
            static constexpr float fDamage = 5.0f;
            static constexpr float fspeed = 400.f;
            static constexpr int iCost = 200;
        };

        struct FlameThrower
        {
            static constexpr int iMaxLevel = 3;
            static constexpr float fRange = 140.0f;
            static constexpr float fMaxCooldown = 0.0f;
            static constexpr float fDamage = 0.025f;
            static constexpr float fspeed = 5000.f;
            static constexpr int iCost = 400;
            static constexpr bool bIsFlameThrowerActive = false;
            static constexpr int iFlameFrame = 0;
        };
    };

    struct UpgradeRate
    {
        static constexpr float fDamageMultiplier = 1.70f;
        static constexpr float fRangeMultiplier = 1.55f;
        static constexpr float fCooldownMultiplier = 1.4f;
        static constexpr float fSpeedMultiplier = 1.60f;
    };
}

#endif // TOWER_GENERATOR_DATA_H