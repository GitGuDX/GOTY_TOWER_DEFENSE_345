#ifndef MAPSETUP_H
#define MAPSETUP_H

#include "../GameEvents.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace sf;

class MapSetup : public IGameSubject
{
public:
    struct TileData
    {
        Vector2f position;
        Tile::Type type;
    };

    MapSetup(Vector2i gridSize);
    ~MapSetup() = default;

    void AddObserver(IGameObserver* observer) override {
        m_observers.push_back(observer);
    }

    void RemoveObserver(IGameObserver* observer) override {
        m_observers.erase(
            std::remove(m_observers.begin(), m_observers.end(), observer),
            m_observers.end()
        );
    }

    std::vector<std::vector<TileData>>& GetTiles() { return m_aTiles; }
    const std::vector<std::vector<TileData>>& GetTiles() const { return m_aTiles; }
    std::vector<sf::Vector2f>& GetPath() { return m_aPath; }
    std::vector<sf::Vector2f>& GetDeletedPath() { return m_aDeletedPath; }
    sf::Vector2f GetEntryTile() { return m_vEntryTile; }
    sf::Vector2f GetExitTile() { return m_vExitTile; }
    sf::Vector2i GetMapSize()
    {
        return Vector2i(m_vGridSize.x*m_iTileSize, m_vGridSize.y*m_iTileSize);
    }

private:
    bool isEdgeTile(sf::Vector2f tile);

    void notifyObservers() {
        for (auto observer : m_observers) {

            observer->Update(*this);
        }
    }

    void SetupTiles()
    {
        m_aTiles.clear();
        for (int i = 0; i < m_vGridSize.y; ++i)
        {
            std::vector<TileData> row;
            for (int j = 0; j < m_vGridSize.x; ++j)
            {
                TileData tempGrassTile;
                tempGrassTile.position = Vector2f(j * m_iTileSize + m_iTileSize / 2, i * m_iTileSize + m_iTileSize / 2);
                tempGrassTile.type = Tile::Type::Grass;
                // tempGrassTile.SetTexture(m_GrassTexture);
                // tempGrassTile.SetScale(Vector2f(1.f, 1.f));
                // tempGrassTile.SetTextureRect(sf::IntRect(0,0,50,50));
                // tempGrassTile.SetOrigin(Vector2f(25, 25));
                // tempGrassTile.SetPosition(Vector2f(j * m_iTileSize + m_iTileSize / 2, i * m_iTileSize + m_iTileSize / 2));
                // tempGrassTile.setType(Tile::Type::Grass);                               // Define its tile type
                row.emplace_back(tempGrassTile);
            }
            m_aTiles.emplace_back(row);
        }
        notifyObservers();
    }

private:
    std::vector<IGameObserver*> m_observers;

    const int m_iTileSize;
    Vector2i m_vGridSize;
    Vector2i m_vMapsize;
    
    std::vector<std::vector<TileData>> m_aTiles;

    std::array<RectangleShape, 8> m_ahighlights;
    std::vector<sf::Vector2f> m_aPath;
    std::vector<sf::Vector2f> m_aDeletedPath;                                                    // Stores the path tiles
    sf::Vector2f m_vEntryTile, m_vExitTile;  
};

#endif // MAPSETUP_H