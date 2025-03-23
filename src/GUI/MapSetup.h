#ifndef MAPSETUP_H
#define MAPSETUP_H

#include "../GameEvents.h"
#include "../Entities/Tile.h"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
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

    const std::vector<sf::Vector2f>& GetPath() const { return m_aPath; }
    std::vector<sf::Vector2f>& GetPath() { return m_aPath; }

    const std::vector<sf::Vector2f>& GetDeletedPath() const { return m_aDeletedPath; }
    const sf::Vector2i& GetGridSize() const { return m_vGridSize; }
    const sf::Vector2f GetEntryTile() const { return m_vEntryTile; }
    const sf::Vector2f GetExitTile() const{ return m_vExitTile; }
    int GetTileSize() const { return m_iTileSize; }

    sf::Vector2i GetMapSize()
    {
        return Vector2i(m_vGridSize.x*m_iTileSize, m_vGridSize.y*m_iTileSize);
    }

    void SetEntryTile(sf::Vector2f entryTile) 
    { 
        m_vEntryTile = entryTile;
        SetTileType(entryTile, Tile::Type::Entry); // Set the tile type to Entry
    }
    
    void SetExitTile(sf::Vector2f exitTile) 
    { 
        m_vExitTile = exitTile;
        SetTileType(exitTile, Tile::Type::Exit); // Set the tile type to Exit
    }

    void PushPathTile(sf::Vector2f pathTile) 
    { 
        m_aPath.push_back(pathTile); 
        notifyObservers();
    }

    void PopPathTile() 
    { 
        m_aPath.pop_back(); 
        notifyObservers();
    }

    void PushDeletedPathTile(sf::Vector2f deletedPathTile) 
    { 
        m_aDeletedPath.push_back(deletedPathTile); 
        notifyObservers();
    }

    void PopDeletedPathTile() 
    { 
        m_aDeletedPath.pop_back(); 
        notifyObservers();
    }

    void ClearDeletedPath() 
    { 
        m_aDeletedPath.clear(); 
        notifyObservers();
    }

    bool isEdgeTile(sf::Vector2f tile);

    void SetupTiles();

    void HighlightEdgeTiles(Tile::Type type);

    bool ValidatePath();

    void SetTileType(sf::Vector2f position, Tile::Type type);

    void debugPrint();
private:
    void notifyObservers() {
        for (auto observer : m_observers) {

            observer->Update(*this);
        }
    }

    Vector2i tileCenterPosToIndex(Vector2f gridPos);

private:
    std::vector<IGameObserver*> m_observers;

    const int m_iTileSize;
    Vector2i m_vGridSize;
    Vector2i m_vMapsize;
    
    std::vector<std::vector<TileData>> m_aTiles;

    std::vector<sf::Vector2f> m_aPath;
    std::vector<sf::Vector2f> m_aDeletedPath;                                                    // Stores the path tiles
    sf::Vector2f m_vEntryTile, m_vExitTile;  
};

#endif // MAPSETUP_H