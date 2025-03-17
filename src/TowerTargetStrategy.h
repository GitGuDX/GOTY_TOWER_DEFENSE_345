#pragma once
#include <vector>
#include "Entities/Entity.h"
#include "Entities/TowerEntity.h"
#include "Monster.h"
class TowerEntity;  // Forward declaration
class Monster;


class TowerTargetStrategy {
    public:
        virtual ~TowerTargetStrategy() = default;
        // Change return type to Monster* to match derived classes
        virtual Monster* SelectTarget(const TowerEntity& tower, const std::vector<Monster>& monsters) const = 0;
};
    