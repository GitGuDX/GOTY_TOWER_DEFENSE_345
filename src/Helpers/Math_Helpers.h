/**

@file Math_Helpers.cpp

@brief Implements some useful mathematical functions
*/

#ifndef MATH_HELPERS_H
#define MATH_HELPERS_H

#include <cmath>
#include <SFML/Graphics.hpp>

using namespace sf;

// Wrap it in a namespace so that the codes are not global
namespace MathHelpers
{


    // returns the center of nearest tile when given position
    inline sf::Vector2f getNearestTileCenterPosition(sf::Vector2f& pos, int tileSize) {
        return sf::Vector2f(
            std::floor(pos.x / tileSize) * tileSize + tileSize / 2,
            std::floor(pos.y / tileSize) * tileSize + tileSize / 2
        );
    }

    //Checks if two tiles are adjacent (only horizontal or vertical movement allowed).
    inline bool isAdjacent(sf::Vector2f& a, sf::Vector2f& b, int tileSize) {
        return (std::abs(a.x - b.x) == tileSize && a.y == b.y) ||  (std::abs(a.y - b.y) == tileSize && a.x == b.x);
    }

    // Get Mangnitude of vector
    inline float getMagnitude(const sf::Vector2f& v) {
        // r = sqrt(x^2 + y^2)
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    // Get unit vector
    inline sf::Vector2f getNormalize(const sf::Vector2f& vector) {
        // If vector is (0,0) return vector right away to avoid dividing by 0
        if (vector.x == 0 && vector.y == 0)
        {
            return vector;
        }

        float magnitude = getMagnitude(vector); 

        // Handle case where magnitude is very small, preventing divide-by-zero or precision issues
        const float epsilon = 1e-6f; // A small threshold value
        if (magnitude < epsilon) 
        {
            return sf::Vector2f(0, 0);  // Return a zero vector to avoid invalid directions
        }
        return sf::Vector2f(vector.x / magnitude, vector.y / magnitude);

        //return (magnitude != 0) ? sf::Vector2f(vector.x / magnitude, vector.y / magnitude) : sf::Vector2f(0, 0); 
    }

    inline float Length(const sf::Vector2f& rVector)
    {
        float fLength = sqrt(rVector.x * rVector.x + rVector.y * rVector.y);
        return fLength;
    }

   

}
#endif