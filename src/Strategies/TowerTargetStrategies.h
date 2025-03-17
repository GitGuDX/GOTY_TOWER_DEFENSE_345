// src/Strategies/TowerTargetStrategies.h
#ifndef TOWER_TARGET_STRATEGIES_H
#define TOWER_TARGET_STRATEGIES_H

#include "../TowerTargetStrategy.h"
#include "../Math_Helpers.h"


class ClosestTargetStrategy : public TowerTargetStrategy {
    public:
        Monster* SelectTarget(const TowerEntity& tower, const std::vector<Monster>& enemies) const override {
            std::cout << "ClosestTargetStrategy: Searching for target..." << std::endl;
            Monster* nearestEnemy = nullptr;
            float shortestDistance = std::numeric_limits<float>::max();
    
            for (const auto& enemy : enemies) {
                sf::Vector2f vectorToEnemy = enemy.GetPosition() - tower.GetPosition();
                float distance = MathHelpers::Length(vectorToEnemy);
                
                if (distance < shortestDistance && distance < tower.GetRange()) {
                    shortestDistance = distance;
                    nearestEnemy = const_cast<Monster*>(&enemy);
                }
            }
            
            return nearestEnemy;
        }
    };
    
    // Targets strongest enemy (highest health)
    class StrongestTargetStrategy : public TowerTargetStrategy {
    public:
        Monster* SelectTarget(const TowerEntity& tower, const std::vector<Monster>& enemies) const override {
            std::cout << "StrongeTargetStrategy: Searching for target..." << std::endl;
            Monster* strongestEnemy = nullptr;
            float highestHealth = 0.0f;
    
            for (const auto& enemy : enemies) {
                sf::Vector2f vectorToEnemy = enemy.GetPosition() - tower.GetPosition();
                float distance = MathHelpers::Length(vectorToEnemy);
                
                if (distance < tower.GetRange() && enemy.GetHealth() > highestHealth) {
                    highestHealth = enemy.GetHealth();
                    strongestEnemy = const_cast<Monster*>(&enemy);
                }
            }
    
            return strongestEnemy;
        }
    };
    
   
    class WeakestTargetStrategy : public TowerTargetStrategy {
    public:
        Monster* SelectTarget(const TowerEntity& tower, const std::vector<Monster>& enemies) const override {
            std::cout << "weakestTargetStrategy: Searching for target..." << std::endl;
            Monster* weakestEnemy = nullptr;
            float lowestHealth = std::numeric_limits<float>::max();
    
            for (const auto& enemy : enemies) {
                sf::Vector2f vectorToEnemy = enemy.GetPosition() - tower.GetPosition();
                float distance = MathHelpers::Length(vectorToEnemy);
                
                if (distance < tower.GetRange() && enemy.GetHealth() < lowestHealth) {
                    lowestHealth = enemy.GetHealth();
                    weakestEnemy = const_cast<Monster*>(&enemy);
                }
            }
    
            return weakestEnemy;
        }
    };
    
    #endif