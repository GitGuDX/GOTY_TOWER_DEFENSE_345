#include <SFML/Graphics.hpp>
#include "Entities/Entity.h"
#include "Monster.h"
#include "Tower.h"

class ProjectileManager {
private:
    std::vector<Entity> m_aProjectiles;
    Time m_DeltaTime;
    Texture m_RapidBulletTexture;
    Texture  m_SniperBulletTexture;

    Entity m_RapidBulletTemplate;
    Entity m_SniperBulletTemplate;
public:
    void FireProjectile(Tower tower, float damage, float speed, sf::Vector2f direction, sf::Vector2f position, float angle);
    void UpdateProjectiles(std::vector<Monster>& monstersQueue, 
        std::vector<Monster*>& deadMonsters,
        int& currentWealth,
        const sf::Vector2f& windowSize);
    void InitializeAssets();
    void SetDeltaTime(Time deltaTime);
    void Draw(sf::RenderWindow& window);
};