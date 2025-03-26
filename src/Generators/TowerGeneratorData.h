#ifndef TOWER_GENERATOR_DATA_H
#define TOWER_GENERATOR_DATA_H

/**
 * @namespace TowerGeneratorData
 * @brief Contains data structures and constants for tower types and their attributes.
 * 
 * The `TowerGeneratorData` namespace includes definitions for various tower types, their stats, and upgrade rates.
 * 
 * It consists of:
 * - `TowerType`: An enumeration listing all available tower types (Basic, Sniper, Rapid, and FlameThrower).
 * - `TowerTypeData`: A struct containing nested structs for each tower type, with static constants defining attributes like:
 *   - `iMaxLevel`: The maximum level for the tower.
 *   - `fRange`: The range of the tower's attack.
 *   - `fMaxCooldown`: The cooldown time between attacks.
 *   - `fDamage`: The damage dealt by the tower.
 *   - `fspeed`: The speed of the tower's attack.
 *   - `iCost`: The cost of the tower.
 * - `UpgradeRate`: A struct with static constants that define the multipliers used to upgrade tower attributes (damage, range, cooldown, and speed).
 */
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