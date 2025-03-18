#include "MapSetupView.h"

#include <iostream>

using namespace sf;


MapSetupView::MapSetupView(RenderWindow &m_Window)
    : m_Window(m_Window)
{
    #ifdef LINUX
    m_GrassTexture.loadFromFile("../src/Images/grass_tile.png");
    m_PathTexture.loadFromFile("../src/Images/path_tile.png");
    m_EntryTileTexture.loadFromFile("../src/Images/entry_Zone_tile.png");
    m_ExitTileTexture.loadFromFile("../src/Images/exit_Zone_tile.png");
    #endif
    #ifdef MAC
    m_GrassTexture.loadFromFile("Images/grass_tile.png");
    m_PathTexture.loadFromFile("Images/path_tile.png");
    m_EntryTileTexture.loadFromFile("Images/entry_tile.png");
    m_ExitTileTexture.loadFromFile("Images/exit_tile.png");
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
        if (data.tiles.empty())
        {
            
            InitializeTiles(data.tiles, tiles); // Call UpdateTiles to update the tile graphics
            //InitializePathLines();
        } 
        else 
        {
            for (size_t i = 0; i < tiles.size(); ++i)
            {
                for (size_t j = 0; j < tiles[i].size(); ++j)
                {
                    UpdateTilesType(data.tiles[i][j], tiles[i][j].type);
                    if (tiles[i][j].type == Tile::Grass)
                    {
                        //std::cout << "Grass tile at: " << tiles[i][j].position.x << ", " << tiles[i][j].position.y << std::endl;
                    }
                    else if (tiles[i][j].type == Tile::Entry)
                    {
                        //std::cout << "Entry tile at: " << tiles[i][j].position.x << ", " << tiles[i][j].position.y << std::endl;
                        data.entryTile = mapSetup->GetEntryTile();
                    }
                    else if (tiles[i][j].type == Tile::Exit)
                    {
                        //std::cout << "Exit tile at: " << tiles[i][j].position.x << ", " << tiles[i][j].position.y << std::endl;
                        data.exitTile = mapSetup->GetExitTile();
                    }
                }
            }
        }

        data.pathPositions = mapSetup->GetPath();
        
        data.exitTile = mapSetup->GetExitTile();
    }

}

void MapSetupView::InitializeTiles(std::vector<std::vector<Tile>>& tiles, const std::vector<std::vector<MapSetup::TileData>>& tilesData)
{
    // Create grass tiles and store them in a 2D array. The position of the item in the array correspond to the position of the tile in the game
    // (e.g. tile at [0][0] is displayed at the top left corner) 
    tiles.clear();
    for (size_t i = 0; i < tilesData.size(); ++i)
    {
        std::vector<Tile> row;
        for (size_t j = 0; j < tilesData[i].size(); ++j)
        {
            Tile tempGrassTile;
            
            tempGrassTile.SetScale(Vector2f(1.f, 1.f));
            tempGrassTile.SetTextureRect(sf::IntRect(0,0,50,50));
            tempGrassTile.SetOrigin(Vector2f(25, 25));
            tempGrassTile.SetPosition(tilesData[i][j].position);
            UpdateTilesType(tempGrassTile, tilesData[i][j].type);

            row.emplace_back(tempGrassTile);


        }
        tiles.emplace_back(row);
    }
}

void MapSetupView::UpdateTilesType(Tile& tile, Tile::Type type)
{
    tile.setType(type);
    switch (type)
    {
        case Tile::Grass:
            tile.SetTexture(m_GrassTexture);
            break;
        case Tile::Path:
            tile.SetTexture(m_PathTexture);
            break;
        case Tile::Entry:
            tile.SetTexture(m_EntryTileTexture);
            break;
        case Tile::Exit:
            tile.SetTexture(m_ExitTileTexture);
            break;
            case Tile::EntryHighlight:
            tile.SetTexture(m_EntryTileTexture);
            break;
        case Tile::ExitHighlight:
            tile.SetTexture(m_ExitTileTexture);
            break;
    }
}

void MapSetupView::Draw()
{

    for (const auto& pair : m_MapSetupSubjects)
    {
        const auto& tiles = pair.second.tiles;
        for (const std::vector<Tile>& row : tiles)
        {
            for (const Tile& tile : row)
            {
                m_Window.draw(tile);
            }
        }
    }

}
