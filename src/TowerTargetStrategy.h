#pragma once
#include <vector>
#include "Entities/Entity.h"
#include "Entities/TowerEntity.h"
#include "Entities/MonsterEntity.h"
class TowerEntity;
class MonsterEntity;

class TowerTargetStrategy {
public:
    virtual ~TowerTargetStrategy() = default;
    virtual MonsterEntity* SelectTarget(const TowerEntity& tower, const std::vector<MonsterEntity>& enemies) const = 0;
};
    