#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "../Platform.h"
#include "GameSetup.h"
#include "../Views/GameSetupView.h"
#include "MapSetup.h"
#include "../Views/MapSetupView.h"
#include "Tile.h"
#include "InfoUI.h"
#include "../Views/InfoUIView.h"
#include <SFML/Graphics.hpp>

#include <memory>


class GUIManager
{
public:
    GUIManager(sf::RenderWindow& m_Window);
    ~GUIManager() = default;

    void InitializeGameSetup();

    void InitializeMapSetup();

    void InitializeInfoUI();

    GameSetup* GetGameSetup()
    {
        return &m_gameSetup;
    }

    GameSetupView* GetGameSetupView() const
    {
        return m_gameSetupView.get(); // Return raw pointer to GameSetupView
    }

    MapSetup* GetMapSetup()
    {
        return m_mapSetup.get();
    }

    MapSetupView* GetMapSetupView() const
    {
        return m_mapSetupView.get();
    }

    InfoUI* GetInfoUI()
    {
        return m_infoUI.get();
    }

    InfoUIView* GetInfoUIView() const
    {
        return m_infoUIView.get();
    }

    Vector2i GetWindowSize() const
    {
        if (m_mapSetup != nullptr)
        {
            Vector2i mapSize = m_mapSetup->GetMapSize();
            int InfoUIWidth = m_infoUI->GetInfoUIWidth();
            return Vector2i(mapSize.x + InfoUIWidth, mapSize.y);
        }
        return Vector2i(0, 0);
    }

    Vector2i GetMapSize() const
    {
        if (m_mapSetup != nullptr)
        {
            return m_mapSetup->GetMapSize();
        }
        return Vector2i(0, 0);
    }

private:
    Vector2i GetGridSize() const
    {
        Vector2i gridSize;
        gridSize.x = std::stoi(m_gameSetup.GetUserInputWindowWidth());                // converting sf::String -> std::string -> unsigned int
        gridSize.y = std::stoi(m_gameSetup.GetUserInputWindowHeight());
        return gridSize;
    }

private:
    sf::RenderWindow& m_Window;

    sf::Font m_Font;

    GameSetup m_gameSetup;
    std::unique_ptr<GameSetupView> m_gameSetupView;
    
    std::unique_ptr<MapSetup> m_mapSetup;
    std::unique_ptr<MapSetupView> m_mapSetupView;

    std::unique_ptr<InfoUI> m_infoUI;
    std::unique_ptr<InfoUIView> m_infoUIView;
};



#endif // GUIMANAGER_H