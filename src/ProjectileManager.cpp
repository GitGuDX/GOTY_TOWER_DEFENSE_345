#include <SFML/Graphics.hpp>
#include "ProjectileManager.h"
#include "Math_Helpers.h"
#include "Monster.h"
#include <iostream>
#include "filesystem"

using namespace sf;

void ProjectileManager::Draw(sf::RenderWindow& window)
{
    try {
      //  std::cout << "Drawing " << m_aProjectiles.size() << " projectiles" << std::endl;
        for (const auto& projectile : m_aProjectiles)
        {
            window.draw(projectile.m_Sprite);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error in Draw: " << e.what() << std::endl;
    }
}

void ProjectileManager::FireProjectile(Tower tower, float damage, float speed, sf::Vector2f direction, sf::Vector2f position, float angle)
{
    try {
        // Debug print to verify function is being called
        std::cout << "Attempting to fire projectile from position: " 
                  << position.x << "," << position.y << std::endl;

        if (tower.GetType() == TowerType::Rapid) {
            std::cout << "Firing Rapid projectile" << std::endl;
            m_aProjectiles.push_back(m_RapidBulletTemplate);
        } else if (tower.GetType() == TowerType::Sniper) {
            std::cout << "Firing Sniper projectile" << std::endl;
            m_aProjectiles.push_back(m_SniperBulletTemplate);
        }

        Entity& newProjectile = m_aProjectiles.back();
        std::cout << "Projectile added to array, setting properties..." << std::endl;

        newProjectile.SetRotation(angle);
        newProjectile.m_speed = speed;
        newProjectile.m_fDamage = damage;
        newProjectile.SetDirection(direction);
        newProjectile.SetPosition(position);
        
        std::cout << "Projectile initialized at position: " 
                  << position.x << "," << position.y << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error in FireProjectile: " << e.what() << std::endl;
        std::cerr << "Tower type: " << static_cast<int>(tower.GetType()) << std::endl;
        std::cerr << "Position: " << position.x << "," << position.y << std::endl;
    }
}


void ProjectileManager::UpdateProjectiles(std::vector<Monster>& monstersQueue, 
    std::vector<Monster*>& deadMonsters,
    int& currentWealth,
    const sf::Vector2f& windowSize)
{
    const float COLLISION_DISTANCE = 25.0f;

    std::cout << "\n=== UpdateProjectiles Start ===\n";
    std::cout << "Active projectiles: " << m_aProjectiles.size() << std::endl;
    std::cout << "Active monsters: " << monstersQueue.size() << std::endl;
    std::cout << "Delta time: " << m_DeltaTime.asSeconds() << std::endl;

    for (auto it = m_aProjectiles.begin(); it != m_aProjectiles.end();)
    {
        bool hitMonster = false;
        
        // Debug movement
        Vector2f oldPos = it->GetPosition();
        Vector2f moveVector = it->GetDirection() * it->GetSpeed() * m_DeltaTime.asSeconds();
        
        std::cout << "\nProjectile Update:"
                  << "\n- Current Position: (" << oldPos.x << ", " << oldPos.y << ")"
                  << "\n- Direction: (" << it->GetDirection().x << ", " << it->GetDirection().y << ")"
                  << "\n- Speed: " << it->GetSpeed()
                  << "\n- Movement Vector: (" << moveVector.x << ", " << moveVector.y << ")\n";
        
        // Move projectile
        it->Move(moveVector);
        
        std::cout << "- New Position: (" << it->GetPosition().x << ", " << it->GetPosition().y << ")\n";
        
        // Debug collision checks
        for (auto& monster : monstersQueue)
        {
            Vector2f diff = monster.GetPosition() - it->GetPosition();
            float distance = MathHelpers::Length(diff);
            
            std::cout << "Checking collision with monster:"
                      << "\n- Monster Position: (" << monster.GetPosition().x << ", " << monster.GetPosition().y << ")"
                      << "\n- Distance: " << distance 
                      << "\n- Collision Threshold: " << COLLISION_DISTANCE << std::endl;
            
            if (distance < COLLISION_DISTANCE)
            {
                std::cout << "*** Collision detected! ***" << std::endl;
                std::string hitMonsterName;
                if(static_cast<int>(monster.GetMonsterType()) == 0){
                    hitMonsterName = "Skeleton";
                } else if (static_cast<int>(monster.GetMonsterType()) == 1){
                    hitMonsterName = "Reaper";
                }else if (static_cast<int>(monster.GetMonsterType()) == 2){
                    hitMonsterName = "Golem";
                }else if (static_cast<int>(monster.GetMonsterType()) == 3){
                    hitMonsterName = "Ogre";
                }else if (static_cast<int>(monster.GetMonsterType()) == 4){
                    hitMonsterName = "Minotaur";
                }
                std::cout << "Debug: Axe hit " << hitMonster << " at position ("
                          << monster.GetPosition().x << ", "
                          << monster.GetPosition().y << ")" << std::endl;
                hitMonster = true;
                monster.SetHealth(monster.GetHealth()-it->GetDamage());
                std::cout << "\n"<<monster.GetHealth()<<"\n";
                if (monster.GetHealth() <= 0){
                    // Handle the monster's death (e.g., remove it from the queue)
                    std::cout << "Monster destroyed!" << std::endl;
                    // Remove the monster from the queue (if applicable)
                    auto monsterIt = std::find(monstersQueue.begin(), monstersQueue.end(), monster);
                    if (monsterIt != monstersQueue.end()) {
                        deadMonsters.push_back(&(*monsterIt));
                        monstersQueue.erase(monsterIt);    //STYLE
                        currentWealth += monster.GetReward();
                    }
                }
                break;
            }
        }

        // Debug removal check
        bool outOfBounds = (it->GetPosition().x < 0 || 
                           it->GetPosition().x > windowSize.x ||
                           it->GetPosition().y < 0 || 
                           it->GetPosition().y > windowSize.y);
        
        std::cout << "Removal check:"
                  << "\n- Hit Monster: " << hitMonster
                  << "\n- Out of Bounds: " << outOfBounds
                  << "\n- Window Size: (" << windowSize.x << ", " << windowSize.y << ")\n";

        if (hitMonster || outOfBounds)
        {
            std::cout << "Removing projectile due to: " 
                      << (hitMonster ? "monster hit" : "out of bounds") << std::endl;
            it = m_aProjectiles.erase(it);
        }
        else
        {
            ++it;
        }
    }
    
    std::cout << "=== UpdateProjectiles End ===\n\n";
}

void ProjectileManager::InitializeAssets()
{
    
        // Load bullet texture
        #ifdef MAC
        std::cout << "Attempting to load Rapid Bullet texture..." << std::endl;
        if (!m_RapidBulletTexture.loadFromFile("Images/Rapid_Bullet.png")) {
            throw std::runtime_error("Failed to load Rapid_Bullet.png");
        }
        std::cout << "Rapid Bullet texture loaded successfully. Size: " 
                  << m_RapidBulletTexture.getSize().x << "x" 
                  << m_RapidBulletTexture.getSize().y << std::endl;

        std::cout << "Attempting to load Sniper Bullet texture..." << std::endl;
        if (!m_SniperBulletTexture.loadFromFile("Images/Sniper_Bullet.png")) {
            throw std::runtime_error("Failed to load Sniper_Bullet.png");
        }
        std::cout << "Sniper Bullet texture loaded successfully. Size: " 
                  << m_SniperBulletTexture.getSize().x << "x" 
                  << m_SniperBulletTexture.getSize().y << std::endl;
        #endif
        m_RapidBulletTemplate.SetTexture(m_RapidBulletTexture);
        m_RapidBulletTemplate.SetOrigin(Vector2f(8, 8));  // Use fixed values like in Game.cpp
        m_RapidBulletTemplate.SetScale(Vector2f(0.3, 0.3));

        // Set up Sniper Bullet
        m_SniperBulletTemplate.SetTexture(m_SniperBulletTexture);
        m_SniperBulletTemplate.SetOrigin(Vector2f(8, 8));  // Use fixed values like in Game.cpp
        m_SniperBulletTemplate.SetScale(Vector2f(0.5, 0.5));
        
}

void ProjectileManager::SetDeltaTime(Time deltaTime)
{
    m_DeltaTime = deltaTime;
    std::cout << "Setting delta time: " << m_DeltaTime.asSeconds() << std::endl;
}

