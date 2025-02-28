#include "MapSetup.h"
#include "../Math_Helpers.h"

MapSetup::MapSetup(Vector2i gridSize)
    : m_iTileSize(50)
    , m_vGridSize(gridSize)    
{

}

void MapSetup::SetupTiles()
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
    for (auto& row : m_aTiles)
    {
        for (auto& tile : row)
        {
            if (tile.position == position)
            {
                tile.type = type;
                return;
            }
        }
    }
    notifyObservers();
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
