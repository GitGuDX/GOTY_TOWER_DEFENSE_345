// src/Strategies/TowerTargetStrategies.h
#ifndef TOWER_TARGET_STRATEGIES_H
#define TOWER_TARGET_STRATEGIES_H

#include "../TowerTargetStrategy.h"
#include "../Math_Helpers.h"


class ClosestTargetStrategy : public TowerTargetStrategy {
    public:
        MonsterEntity* SelectTarget(const TowerEntity& tower, const std::vector<MonsterEntity>& enemies) const override {
            std::cout << "ClosestTargetStrategy: Searching for target..." << std::endl;
            MonsterEntity* nearestEnemy = nullptr;
            float shortestDistance = std::numeric_limits<float>::max();
    
            for (const auto& enemy : enemies) {
                sf::Vector2f vectorToEnemy = enemy.GetPosition() - tower.GetPosition();
                float distance = MathHelpers::Length(vectorToEnemy);
                
                if (distance < shortestDistance && distance < tower.GetRange()) {
                    shortestDistance = distance;
                    nearestEnemy = const_cast<MonsterEntity*>(&enemy);
                }
            }
            
            return nearestEnemy;
        }
    };
    
    class StrongestTargetStrategy : public TowerTargetStrategy {
    public:
        MonsterEntity* SelectTarget(const TowerEntity& tower, const std::vector<MonsterEntity>& enemies) const override {
            std::cout << "StrongestTargetStrategy: Searching for target..." << std::endl;
            MonsterEntity* strongestEnemy = nullptr;
            float highestHealth = 0.0f;
    
            for (const auto& enemy : enemies) {
                sf::Vector2f vectorToEnemy = enemy.GetPosition() - tower.GetPosition();
                float distance = MathHelpers::Length(vectorToEnemy);
                
                if (distance < tower.GetRange() && enemy.GetHealth() > highestHealth) {
                    highestHealth = enemy.GetHealth();
                    strongestEnemy = const_cast<MonsterEntity*>(&enemy);
                }
            }
    
            return strongestEnemy;
        }
    };
    
    class WeakestTargetStrategy : public TowerTargetStrategy {
    public:
        MonsterEntity* SelectTarget(const TowerEntity& tower, const std::vector<MonsterEntity>& enemies) const override {
            std::cout << "WeakestTargetStrategy: Searching for target..." << std::endl;
            MonsterEntity* weakestEnemy = nullptr;
            float lowestHealth = std::numeric_limits<float>::max();
    
            for (const auto& enemy : enemies) {
                sf::Vector2f vectorToEnemy = enemy.GetPosition() - tower.GetPosition();
                float distance = MathHelpers::Length(vectorToEnemy);
                
                if (distance < tower.GetRange() && enemy.GetHealth() < lowestHealth) {
                    lowestHealth = enemy.GetHealth();
                    weakestEnemy = const_cast<MonsterEntity*>(&enemy);
                }
            }
    
            return weakestEnemy;
        }
    };
    
    #endif