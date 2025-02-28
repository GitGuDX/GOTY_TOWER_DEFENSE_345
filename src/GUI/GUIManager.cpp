#include "GUIManager.h"

#include <iostream>

using namespace sf;

GUIManager::GUIManager(RenderWindow& m_Window)
    : m_Window(m_Window)
{
    #ifdef LINUX
    if (!m_Font.loadFromFile("../src/Fonts/Kreon-Medium.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    #endif
    #ifdef MAC
    if (!m_Font.loadFromFile("Fonts/Kreon-Medium.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    #endif

    // Initialize GameSetupView dynamically
    m_gameSetupView = std::make_unique<GameSetupView>(m_Window, m_Font);

    // PLACEHOLDER. Will be replaced with actual game setup initialization which will initialize 
    // appropriate GUI depending on the game mode
    InitializeGameSetup();
}

void GUIManager::InitializeGameSetup()
{
    // Pass the raw pointer of the unique_ptr to AddObserver
    m_gameSetup.AddObserver(m_gameSetupView.get());                          // Must be done before setting up the view
    m_gameSetup.SetIntroTitle("Welcome to Tower Defense!");
    m_gameSetup.SetEnterSizeSign("Enter the size of the grid:");
    m_gameSetup.SetUserInputWindowHeight("10");
    m_gameSetup.SetUserInputWindowWidth("10");
    m_gameSetup.SetSizeLimitWarning("Size must be between 10 and 20.");
}

void GUIManager::InitializeMapSetup(Vector2i gridSize)
{
    m_mapSetup = std::make_unique<MapSetup>(gridSize);
    m_mapSetupView = std::make_unique<MapSetupView>(m_Window);
    m_mapSetup->AddObserver(m_mapSetupView.get());
    m_mapSetup->SetupTiles();
}
