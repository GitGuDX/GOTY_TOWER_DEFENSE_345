#include "MapSetupView.h"

#include <iostream>

using namespace sf;


MapSetupView::MapSetupView(RenderWindow &m_Window)
    : m_Window(m_Window)
{
    #ifdef LINUX
    m_GrassTexture.loadFromFile("../src/Images/grass_tile.png");
    m_PathTexture.loadFromFile("../src/Images/path_tile.png");
    m_EntryTileTexture.loadFromFile("../src/Images/entry_tile.png");
    m_ExitTileTexture.loadFromFile("../src/Images/exit_tile.png");
    #endif
    #ifdef MAC
    m_GrassTexture.loadFromFile("Images/grass_tile.png");
    m_PathTexture.loadFromFile("Images/path_tile.png");
    m_EntryTexture.loadFromFile("Images/entry_tile.png");
    m_ExitTexture.loadFromFile("Images/exit_tile.png");
    #endif

    //m_sfPathLines.setPrimitiveType(sf::LineStrip); // Set the drawing type to a continuous line
}

void MapSetupView::Update(const IGameSubject &subject)
{
    const MapSetup *mapSetup = dynamic_cast<const MapSetup *>(&subject);
    if (mapSetup)
    {
        auto &data = m_MapSetupSubjects[mapSetup];
        const std::vector<std::vector<MapSetup::TileData>>& tiles = mapSetup->GetTiles();
        if (m_aTiles.empty())
        {
            InitializeTiles(tiles); // Call UpdateTiles to update the tile graphics
            InitializePathLines();
        } 
        else 
        {
            for (int i = 0; i < tiles.size(); ++i)
            {
                for (int j = 0; j < tiles[i].size(); ++j)
                {
                    UpdateTilesType(m_aTiles[i][j], tiles[i][j].type);
                }
            }
        }

        
        data.m_aPath = mapSetup->GetPath();
        data.m_vEntryTile = mapSetup->GetEntryTile();
        data.m_vExitTile = mapSetup->GetExitTile();
    }

}

void MapSetupView::InitializeTiles(std::vector<std::vector<MapSetup::TileData>>& tiles)
{
    // Create grass tiles and store them in a 2D array. The position of the item in the array correspond to the position of the tile in the game
    // (e.g. tile at [0][0] is displayed at the top left corner) 
    m_aTiles.clear();
    for (int i = 0; i < tiles.size(); ++i)
    {
        std::vector<Tile> row;
        for (int j = 0; j < tiles[i].size(); ++j)
        {
            Tile tempGrassTile;
            
            tempGrassTile.SetScale(Vector2f(1.f, 1.f));
            tempGrassTile.SetTextureRect(sf::IntRect(0,0,50,50));
            tempGrassTile.SetOrigin(Vector2f(25, 25));
            tempGrassTile.SetPosition(tiles[i][j].position);
            UpdateTilesType(tempGrassTile, tiles[i][j].type);

            row.emplace_back(tempGrassTile);


        }
        m_aTiles.emplace_back(row);
    }
}

void MapSetupView::UpdateTilesType(Tile& tile, Tile::Type type)
{
    tile.setType(type);
    switch (type)
    {
        case MapSetup::TileData::Type::Grass:
            tile.SetTexture(m_GrassTexture);
            break;
        case MapSetup::TileData::Type::Path:
            tile.SetTexture(m_PathTexture);
            break;
        case MapSetup::TileData::Type::Entry:
            tile.SetTexture(m_EntryTexture);
            break;
        case MapSetup::TileData::Type::Exit:
            tile.SetTexture(m_ExitTexture);
            break;
    }
}

void MapSetupView::Draw()
{

    for (std::vector<Tile>& row : m_aTiles)
    {
        for (Tile& tile : row)
        {
            m_Window.draw(tile);
        }
    }

}
