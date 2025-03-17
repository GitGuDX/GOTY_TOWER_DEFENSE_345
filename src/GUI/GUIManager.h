#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "../Platform.h"
#include "GameSetup.h"
#include "../Views/GameSetupView.h"
#include "MapSetup.h"
#include "../Views/MapSetupView.h"
#include "../Entities/Tile.h"
#include "InfoUI.h"
#include "../Views/InfoUIView.h"
#include <SFML/Graphics.hpp>

#include <memory>

class TowerEntity;

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

    Vector2i GetGridSize() const;

    Vector2i GetWindowSize() const;

    Vector2i GetMapSize() const;

    void InitiailizeTowerPrice(std::vector<TowerEntity>& templateTowers);

    bool InitializeEntryTile(const sf::Vector2f& position);

    bool InitializeExitTile(const sf::Vector2f& position);

    bool FinalizeExitTile(const sf::Vector2f& position);

    void UpdateTowerHoverUI(TowerEntity& tower);

    void BlinkTiles(Tile::Type type, sf::Time deltaTime);

    void UpdatePathTiles();

    void SetInstructionAndColor(const std::string& instruction, const Color& color);

    void SetWarningAndColor(const std::string& warning, const Color& color);

private:
    sf::RenderWindow& m_Window;

    float m_fElapsedTimeInSeconds;

    sf::Font m_Font;

    GameSetup m_gameSetup;
    std::unique_ptr<GameSetupView> m_gameSetupView;
    
    std::unique_ptr<MapSetup> m_mapSetup;
    std::unique_ptr<MapSetupView> m_mapSetupView;

    std::unique_ptr<InfoUI> m_infoUI;
    std::unique_ptr<InfoUIView> m_infoUIView;
};



#endif // GUIMANAGER_H