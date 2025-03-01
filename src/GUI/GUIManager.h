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

    void InitializeMapSetup(Vector2i gridSize);

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