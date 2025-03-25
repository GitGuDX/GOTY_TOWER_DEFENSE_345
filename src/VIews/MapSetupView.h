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
        std::vector<sf::Vector2f> deletedPathPositions;     // Stores the path tiles
        sf::VertexArray pathLines;                      // Draws path line 
        sf::Vector2f entryTile = sf::Vector2f(-1, -1); // Default value indicating uninitialized state
        sf::Vector2f exitTile = sf::Vector2f(-1, -1);  // Default value indicating uninitialized state
    };

public:
    MapSetupView(sf::RenderWindow& m_Window);
    ~MapSetupView() = default;

    void Update(const IGameSubject& subject);

    void Draw(const MapSetup* mapSetup);

    void DrawPathLine(const MapSetup* mapSetup);

    void ClearSubjects() { m_MapSetupSubjects.clear(); }

private:
    void LoadTileTextures();
    void InitializeTiles(MapSetupData& data, const std::vector<std::vector<MapSetup::TileData>>& tiles);
    void UpdatePath(MapSetupData& data);
    void UpdateTilesType(Tile& tile, Tile::Type type);


private:
    std::unordered_map<const MapSetup*, MapSetupData> m_MapSetupSubjects;

    sf::RenderWindow& m_Window;

    Texture m_GrassTexture;
    Texture m_PathTexture;
};

#endif      // MAPSETUPVIEW_H