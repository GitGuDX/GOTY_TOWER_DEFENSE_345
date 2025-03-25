#include "MapSetup.h"
#include "../Helpers/Math_Helpers.h"

MapSetup::MapSetup(Vector2i gridSize)
    : m_iTileSize(50)
    , m_vGridSize(gridSize)    
{
}

void MapSetup::SetupDefaultTiles()
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
            row.emplace_back(tempGrassTile);
        }
        m_aTiles.emplace_back(row);
    }
    notifyObservers();
}

void MapSetup::EditTilesFromPath()
{
    for (size_t i = 0; i < m_aPath.size(); ++i)
    {
        Tile::Type type = Tile::Type::Path;
        if (i == 0)
        {
            type = Tile::Type::Entry;
            m_vEntryTile = m_aPath[i];
        }
        else if (i == m_aPath.size() - 1)
        {
            type = Tile::Type::Exit;
            m_vExitTile = m_aPath[i];
        }
        SetTileType(m_aPath[i], type);
    }
}

void MapSetup::HighlightEdgeTiles(Tile::Type type)
{
    for (size_t i = 0; i < m_aTiles.size(); ++i)
    {
        for (size_t j = 0; j < m_aTiles[i].size(); ++j)
        {
            if ((m_aTiles[i][j].position != m_vEntryTile && m_aTiles[i][j].position != m_vExitTile) && isEdgeTile(m_aTiles[i][j].position))
            {
                m_aTiles[i][j].type = type;
            }
        }
    }
    notifyObservers();
}

void MapSetup::debugPrint()
{   
    for (size_t i = 0; i < m_aTiles.size(); ++i)
    {
        for (size_t j = 0; j < m_aTiles[i].size(); ++j)
        {
            if (m_aTiles[i][j].position == m_vEntryTile)
            {
                std::cout << "Entry tile at: " << m_aTiles[i][j].position.x<<" "<<m_aTiles[i][j].position.y<<std::endl;
                std::cout << "Type: " << m_aTiles[i][j].type << std::endl;
            }
            else if (m_aTiles[i][j].position == m_vExitTile)
            {
                std::cout << "Exit tile at: " << m_aTiles[i][j].position.x<<" "<<m_aTiles[i][j].position.y<<std::endl;
                std::cout << "Type: " << m_aTiles[i][j].type << std::endl;
            }
            
        }
    }
}

void MapSetup::SetTileType(sf::Vector2f position, Tile::Type type)
{
    sf::Vector2i TileIndex = tileCenterPosToIndex(position);
    m_aTiles[TileIndex.y][TileIndex.x].type = type;
    notifyObservers();
}

Vector2i MapSetup::tileCenterPosToIndex(Vector2f gridPos)
{
    return Vector2i(static_cast<int>(gridPos.x/m_iTileSize), static_cast<int>(gridPos.y/m_iTileSize));
}

bool MapSetup::isEdgeTile(sf::Vector2f tile)
{
    // Check if the tile is on the left or right edge
    bool isOnHorizontalEdge = (tile.x <= m_iTileSize / 2) || (tile.x >= (m_vGridSize.x - 1) * m_iTileSize + m_iTileSize / 2);
    // Check if the tile is on the top or bottom edge
    bool isOnVerticalEdge = (tile.y <= m_iTileSize / 2) || (tile.y >= (m_vGridSize.y - 1) * m_iTileSize + m_iTileSize / 2);

    return isOnHorizontalEdge || isOnVerticalEdge;
}

bool MapSetup::ValidatePath()
{
    if (!m_aPath.empty())
    {
        // Check if the path is connected
        for (size_t i = 0; i < m_aPath.size() - 1; ++i)
        {
            Vector2f currentTile = m_aPath[i];
            Vector2f nextTile = m_aPath[i + 1];
            Vector2f tileToTile = nextTile - currentTile;
            float distance = MathHelpers::Length(tileToTile);
            if (distance > m_iTileSize)
            {
                return false;
            }
        }

        // Check if the path is connected to the entry and exit
        if (m_aPath[0] != m_vEntryTile || m_aPath[m_aPath.size() - 1] != m_vExitTile)
        {
            return false;
        }

        return true;
    }
    return false;
}
