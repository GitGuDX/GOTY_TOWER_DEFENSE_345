#ifndef MAPSETUPVIEW_H
#define MAPSETUPVIEW_H

#include "../Platform.h"
#include "../GameEvents.h"
#include "../GUI/MapSetup.h"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <unordered_map> 
#include <vector>

using namespace sf;

class MapSetupView : public IGameObserver
{
private:
    struct MapSetupData
    {
        std::vector<std::vector<Tile>> tiles;
        std::vector<sf::Vector2f> pathPositions;
        std::vector<sf::Vector2f> deletedPathPositions;                                                    // Stores the path tiles
        sf::Vector2f entryTile = sf::Vector2f(-1, -1); // Default value indicating uninitialized state
        sf::Vector2f exitTile = sf::Vector2f(-1, -1);  // Default value indicating uninitialized state
    };

public:
    MapSetupView(sf::RenderWindow& m_Window);
    ~MapSetupView() = default;

    void Update(const IGameSubject& subject);

    void Draw(const MapSetup* subject);

    void ClearSubjects() { m_MapSetupSubjects.clear(); }

private:
    void LoadTileTextures();
    void InitializeTiles(std::vector<std::vector<Tile>>& tilePositions, const std::vector<std::vector<MapSetup::TileData>>& tiles);
    void UpdateTilesType(Tile& tile, Tile::Type type);


private:
    std::unordered_map<const MapSetup*, MapSetupData> m_MapSetupSubjects;

    sf::RenderWindow& m_Window;

    Texture m_GrassTexture;
    Texture m_PathTexture;
    Texture m_EntryTileTexture;
    Texture m_ExitTileTexture;

};

#endif      // MAPSETUPVIEW_H