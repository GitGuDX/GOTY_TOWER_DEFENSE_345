#include <cmath>
#include <SFML/Graphics.hpp>

using namespace sf;

// Wrap it in a namespace so that the codes are not global
namespace MathHelpers
{

    // returns the center of nearest tile when given position
    sf::Vector2f snapToGrid(sf::Vector2f pos, int tileSize) {
        return sf::Vector2f(
            std::floor(pos.x / tileSize) * tileSize + tileSize / 2,
            std::floor(pos.y / tileSize) * tileSize + tileSize / 2
        );
    }

    //Checks if two tiles are adjacent (only horizontal or vertical movement allowed).
    bool isAdjacent(sf::Vector2f a, sf::Vector2f b, int tileSize) {
        return (std::abs(a.x - b.x) == tileSize && a.y == b.y) ||  (std::abs(a.y - b.y) == tileSize && a.x == b.x);
    }

    // Get Mangnitude of vector
    float getMagnitude(const sf::Vector2f& v) {
        // r = sqrt(x^2 + y^2)
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    // Get unit vector
    sf::Vector2f getNormalize(const sf::Vector2f& vector) {
        float magnitude = getMagnitude(vector);                                             
        return (magnitude != 0) ? sf::Vector2f(vector.x / magnitude, vector.y / magnitude) : sf::Vector2f(0, 0); 
    }

}
