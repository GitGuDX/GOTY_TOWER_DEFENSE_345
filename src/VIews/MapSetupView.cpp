#include "MapSetupView.h"

using namespace sf;


/**
 * @class MapSetupView
 * @brief Handles the visual representation of the map setup in the game.
 * 
 * This class is responsible for rendering the map tiles, including the grass, path, entry, and exit tiles, as well as drawing the path lines. It listens for changes from the `MapSetup` and updates the view accordingly.
 * 
 * Key Methods:
 * - `Update()`: Updates the view with new tile data from the `MapSetup` subject. It initializes or updates tiles and path lines.
 * - `LoadTileTextures()`: Loads textures for tiles (grass and path).
 * - `InitializeTiles()`: Sets up the tiles based on the data received, including their textures and types.
 * - `UpdatePath()`: Updates the path lines based on the current path positions.
 * - `UpdateTilesType()`: Modifies the tile's texture and color depending on its type.
 * - `Draw()`: Draws the tiles of the map to the window.
 * - `DrawPathLine()`: Draws the path lines to the window.
 */
MapSetupView::MapSetupView(RenderWindow &m_Window)
    : m_Window(m_Window)
{
    LoadTileTextures();
}

void MapSetupView::Update(const IGameSubject &subject)
{
    const MapSetup *mapSetup = dynamic_cast<const MapSetup *>(&subject);
    //std::cout << "Getting data for address: " << mapSetup << std::endl;
    if (mapSetup)
    {
        auto &data = m_MapSetupSubjects[mapSetup];
        const std::vector<std::vector<MapSetup::TileData>>& tiles = mapSetup->GetTiles();
        if (data.tiles.empty())
        {
            InitializeTiles(data, tiles); // Call UpdateTiles to update the tile graphics
            data.pathLines.setPrimitiveType(sf::LineStrip); // Set the drawing type to a continuous line
        } 
        else 
        {
            for (size_t i = 0; i < tiles.size(); ++i)
            {
                for (size_t j = 0; j < tiles[i].size(); ++j)
                {
                    UpdateTilesType(data.tiles[i][j], tiles[i][j].type);
                    if (tiles[i][j].type == Tile::Entry)
                    {
                        //std::cout << "Entry tile at: " << tiles[i][j].position.x << ", " << tiles[i][j].position.y << std::endl;
                        data.entryTile = tiles[i][j].position;
                    }
                    else if (tiles[i][j].type == Tile::Exit)
                    {
                        //std::cout << "Exit tile at: " << tiles[i][j].position.x << ", " << tiles[i][j].position.y << std::endl;
                        data.exitTile = tiles[i][j].position;
                        //data.pathLines.append(sf::Vertex(tiles[i][j].position, sf::Color::Red));
                    }
                }
            }
            
        }
        data.pathPositions = mapSetup->GetPath();
        data.exitTile = mapSetup->GetExitTile();
        UpdatePath(data);
    }

}

void MapSetupView::LoadTileTextures()
{
    m_GrassTexture.loadFromFile("../src/Images/Tiles/grass_tile.png");
    m_PathTexture.loadFromFile("../src/Images/Tiles/path_tile.png");
}

void MapSetupView::InitializeTiles(MapSetupData& data, const std::vector<std::vector<MapSetup::TileData>> &tilesData)
{
    // Create grass tiles and store them in a 2D array. The position of the item in the array correspond to the position of the tile in the game
    // (e.g. tile at [0][0] is displayed at the top left corner) 
    data.tiles.clear();
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
        data.tiles.emplace_back(row);
    }
}

void MapSetupView::UpdatePath(MapSetupData& data)
{
    data.pathLines.clear();
    data.pathLines.resize(data.pathPositions.size());
    for (size_t i = 0; i < data.pathPositions.size(); ++i)
    {
        if (i == 0)
        {
            data.pathLines[i] = (sf::Vertex(data.pathPositions[i], sf::Color::Green));
        }
        else if (i == data.pathPositions.size() - 1)
        {
            data.pathLines[i] = (sf::Vertex(data.pathPositions[i], sf::Color::Red));
        }
        else
        {
            data.pathLines[i] = (sf::Vertex(data.pathPositions[i], sf::Color(128, 128, 128)));
        }
    }
}

void MapSetupView::UpdateTilesType(Tile& tile, Tile::Type type)
{
    tile.setType(type);
    switch (type)
    {
        case Tile::Grass:
            tile.SetTexture(m_GrassTexture);
            tile.SetColor(sf::Color::White);
            break;
        case Tile::Path:
            tile.SetTexture(m_PathTexture);
            break;
        case Tile::Entry:
            tile.SetTexture(m_PathTexture);
            tile.SetColor(sf::Color(0, 255, 0, 255));
            break;
        case Tile::Exit:
            tile.SetTexture(m_PathTexture);
            tile.SetColor(sf::Color(255, 0, 0, 255));
            break;
        case Tile::EntryHighlight:
            tile.SetTexture(m_PathTexture);
            tile.SetColor(sf::Color(0, 255, 0, 255));
            break;
        case Tile::ExitHighlight:
            tile.SetTexture(m_PathTexture);
            tile.SetColor(sf::Color(255, 0, 0, 255));
            break;
    }
}

void MapSetupView::Draw(const MapSetup* mapSetup)
{
    if (m_MapSetupSubjects.find(mapSetup) != m_MapSetupSubjects.end()) {
        const auto& tiles = m_MapSetupSubjects[mapSetup].tiles;
        for (const std::vector<Tile>& row : tiles)
        {
            for (const Tile& tile : row)
            {
                m_Window.draw(tile);
            }
        }
    } else {
        std::cout << "Map does not exist" << std::endl;
    }
}

void MapSetupView::DrawPathLine(const MapSetup* mapSetup)
{
    if (m_MapSetupSubjects.find(mapSetup) != m_MapSetupSubjects.end()) {
        const auto& pathLines = m_MapSetupSubjects[mapSetup].pathLines;
        m_Window.draw(pathLines);
    } else {
        std::cout << "Map does not exist" << std::endl;
    }
}