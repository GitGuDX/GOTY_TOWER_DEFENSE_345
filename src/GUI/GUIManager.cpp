#include "GUIManager.h"
#include "../Entities/TowerEntity.h"
//#include "../Generators/TowerGenerator.h"

#include <iostream>
#include <cmath>

using namespace sf;

GUIManager::GUIManager(RenderWindow& m_Window)
    : m_Window(m_Window)
    , m_fElapsedTimeInSeconds(0.0f)
{

    // ** Load class
    LoadFonts();

    m_gameSetup = std::make_unique<GameSetup>();
    // Initialize GameSetupView dynamically
    m_gameSetupView = std::make_unique<GameSetupView>(m_Window, m_Font);

    // PLACEHOLDER. Will be replaced with actual game setup initialization which will initialize 
    // appropriate GUI depending on the game mode
    InitializeGameSetup();
}

// ** Load class
void GUIManager::LoadFonts()
{
    if (!m_Font.loadFromFile("../src/Fonts/Kreon-Medium.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
}

void GUIManager::InitializeMainMenu()
{
    m_mainMenu = std::make_unique<MainMenuDriver>(m_Window);
    m_mainMenu->LoadTextures();
    m_mainMenu->InitializeTitleLogo();
    m_mainMenu->InitializeButtons();
}

void GUIManager::InitializeMapSelectionMenu()
{
    m_mapSelectionMenu = std::make_unique<MapSelectionDriver>(m_Window, m_Font);
    m_mapSelectionMenu->LoadMapSelectionMenuTextures();
    m_mapSelectionMenu->InitializeMapSelectionAssets();
}

void GUIManager::InitializeGameSetup()
{
    // If the game setup view is not nullptr, remove the observer before setting up the view
    if (m_gameSetupView != nullptr)
    {
    m_gameSetup->RemoveObserver(m_gameSetupView.get());                       // Remove the observer before setting up the view
    m_gameSetupView->ClearSubjects();                                        // Clear the subjects before setting up the view
    }

    // Pass the raw pointer of the unique_ptr to AddObserver
    m_gameSetup->AddObserver(m_gameSetupView.get());                          // Must be done before setting up the view
    m_gameSetup->SetIntroTitle("Create your own map!");
    m_gameSetup->SetEnterSizeSign("Enter the size of the grid:");
    m_gameSetup->SetUserInputWindowHeight("10");
    m_gameSetup->SetUserInputWindowWidth("10");
    m_gameSetup->SetSizeLimitWarning("Size must be between 10 and 20.");
}

void GUIManager::InitializeLoadedMapSetup(sf::Vector2i gridSize)
{
    // If the map setup view is not nullptr, remove the observer before setting up the view
    if (m_mapSetup != nullptr && m_mapSetupView != nullptr)
    {
        m_mapSetup->RemoveObserver(m_mapSetupView.get());
        m_mapSetupView->ClearSubjects();
    }
    m_mapSetup = std::make_unique<MapSetup>(gridSize);
    m_mapSetupView = std::make_unique<MapSetupView>(m_Window);
    m_mapSetup->AddObserver(m_mapSetupView.get());
    std::cout << "Map setup address: " << m_mapSetup.get() << std::endl;
}

void GUIManager::InitializeMapSetup()
{
    // If the map setup view is not nullptr, remove the observer before setting up the view
    if (m_mapSetup != nullptr && m_mapSetupView != nullptr)
    {
        m_mapSetup->RemoveObserver(m_mapSetupView.get());
        m_mapSetupView->ClearSubjects();
    }

    Vector2i gridSize = GetGridSize();
    m_mapSetup = std::make_unique<MapSetup>(gridSize);
    m_mapSetupView = std::make_unique<MapSetupView>(m_Window);
    m_mapSetup->AddObserver(m_mapSetupView.get());
    //m_mapSetup->SetupDefaultTiles();
}

void GUIManager::InitializeInfoUI()
{

    if (m_infoUI != nullptr && m_infoUIView != nullptr)
    {
        m_infoUI->RemoveObserver(m_infoUIView.get());
        m_infoUIView->ClearSubjects();
    }

    m_infoUI = std::make_unique<InfoUI>();

    Vector2i mapSize = GetMapSetup()->GetMapSize();
    int infoUIWidth = m_infoUI->GetInfoUIWidth();

    m_infoUIView = std::make_unique<InfoUIView>(m_Window, mapSize, infoUIWidth, m_Font);
    m_infoUI->AddObserver(m_infoUIView.get());
    m_infoUI->InitializeInfoUI();
}

void GUIManager::ResetGameSetup()
{
    m_gameSetup->SetUserInputWindowHeight("10");
    m_gameSetup->SetUserInputWindowWidth("10");
    m_gameSetupView->SetIsSizeLimitTextShown(false);
}

Vector2i GUIManager::GetWindowSize() const
{
    if (m_mapSetup != nullptr)
    {
        Vector2i mapSize = m_mapSetup->GetMapSize();
        int InfoUIWidth = m_infoUI->GetInfoUIWidth();
        return Vector2i(mapSize.x + InfoUIWidth, mapSize.y);
    }
    return Vector2i(0, 0);
}

Vector2i GUIManager::GetMapSize() const
{
    if (m_mapSetup != nullptr)
    {
        return m_mapSetup->GetMapSize();
    }
    return Vector2i(0, 0);
}

void GUIManager::InitiailizeTowerPrice(std::vector<std::unique_ptr<TowerEntity>>& templateTowers)
{
    for (const std::unique_ptr<TowerEntity>& towerPtr : templateTowers)
    {
        if (towerPtr->GetType() == TowerGeneratorData::TowerType::Rapid)
        {
            m_infoUI->SetWoodTowerPriceString(sf::String(std::to_string(towerPtr->GetCost())));
        }
        else if (towerPtr->GetType() == TowerGeneratorData::TowerType::Sniper)
        {
            m_infoUI->SetStoneTowerPriceString(sf::String(std::to_string(towerPtr->GetCost())));
        }
        else if (towerPtr->GetType() == TowerGeneratorData::TowerType::FlameThrower)
        {
            m_infoUI->SetFlameThrowerTowerPriceString(sf::String(std::to_string(towerPtr->GetCost())));
        }
    }
}

bool GUIManager::InitializeEntryTile(const sf::Vector2f& position)
{
    if (m_mapSetup->isEdgeTile(position))
    {
        m_mapSetup->PushPathTile(position);
        m_mapSetup->SetEntryTile(position);
        return true;
    }
    return false;
}

bool GUIManager::InitializeExitTile(const sf::Vector2f &position)
{
    if (m_mapSetup->isEdgeTile(position))
    {
        m_mapSetup->SetExitTile(position);
        m_mapSetup->HighlightEdgeTiles(Tile::Type::Grass);
        return true;
    }
    return false;
}

bool GUIManager::FinalizeExitTile(const sf::Vector2f &position)
{
    const Vector2f& exitTile = m_mapSetup->GetExitTile();
    if (position == exitTile)
    {
        m_mapSetup->PushPathTile(exitTile);
        return true;
    }
    return false;
}

void GUIManager::UpdateTowerHoverUI(std::unique_ptr<TowerEntity>& towerPtr)
{
    if (!m_infoUI)
    {
        std::cerr << "Error: InfoUI is nullptr\n";
        return;  // Prevent null pointer dereference
    }

    auto roundTwoDecimals = [](float value) {
        return std::round(value * 100.0f) / 100.0f;
    };

    TowerGeneratorData::TowerType type = towerPtr->GetType();
    m_infoUI->SetHoverTowerName(type);
    m_infoUI->SetHoverTowerLevel(towerPtr->GetLevel());
    m_infoUI->SetHoverTowerDamage(roundTwoDecimals(towerPtr->GetDamage()));
    m_infoUI->SetHoverTowerCooldown(roundTwoDecimals(towerPtr->GetMaxCooldown()));
    m_infoUI->SetHoverTowerRange(roundTwoDecimals(towerPtr->GetRange()));
    m_infoUI->SetHoverTowerSpeed(roundTwoDecimals(towerPtr->GetSpeed()));
    m_infoUI->SetHoverTowerUpgradeCost(towerPtr->GetUpgradeCost());
    m_infoUI->SetHoverTowerEffect(type);
}

void GUIManager::UpdateMonsterUi(MonsterGeneratorData::MonsterType type, int level)
{
    if (!m_infoUI)
    {
        std::cerr << "Error: InfoUI is nullptr\n";
        return;  // Prevent null pointer dereference
    }
    m_infoUI->SetNextMonsterTitleString("Up Next");
    m_infoUI->SetNextMonsterLevelString("Level: " + std::to_string(level + 1));

    switch (type)
    {
    case MonsterGeneratorData::MonsterType::Skeleton:
        m_infoUI->SetNextMonsterDescriptionString("Basic, vanilla baby");
        break;
    case MonsterGeneratorData::MonsterType::Reaper:
        m_infoUI->SetNextMonsterDescriptionString("Fast and weak");
        break;
    case MonsterGeneratorData::MonsterType::Golem:
        m_infoUI->SetNextMonsterDescriptionString("Slow but tanky");
        break;
    case MonsterGeneratorData::MonsterType::Minotaur:
        m_infoUI->SetNextMonsterDescriptionString("Strong and swift");
        break;
    case MonsterGeneratorData::MonsterType::Ogre:
        m_infoUI->SetNextMonsterDescriptionString("Balanced all-rounder");
        break;
    default:
        m_infoUI->SetNextMonsterDescriptionString("Unknown monster type");
        break;
    }
}

void GUIManager::BlinkTiles(Tile::Type type, sf::Time deltaTime)
{
    m_fElapsedTimeInSeconds += deltaTime.asSeconds();  // Use the passed deltaTime

    if (m_fElapsedTimeInSeconds >= 0.5f)
    {
        m_mapSetup->HighlightEdgeTiles(type);

        if (m_fElapsedTimeInSeconds >= 1.0f)
        {
            m_mapSetup->HighlightEdgeTiles(Tile::Type::Grass);
            m_fElapsedTimeInSeconds = 0.0f;  // Reset timer
        }
    }
}


void GUIManager::UpdatePathTiles()
{
    // If deleted path exist in the array, reset the tile type and texture of the deleted path for all elements in the array
    // Then remove all elements from the array
    if (!m_mapSetup->GetDeletedPath().empty())
    {
        for (Vector2f vector : m_mapSetup->GetDeletedPath())
        {
            m_mapSetup->SetTileType(vector, Tile::Type::Grass);

        }
        // Remove all elements from m_aDeletedPath
        m_mapSetup->ClearDeletedPath();
    }
    
    // Set tile type and change the texture of all current path tiles
    for (Vector2f vector : m_mapSetup->GetPath())
    {
        if (vector != m_mapSetup->GetEntryTile() && vector != m_mapSetup->GetExitTile())
        {
            m_mapSetup->SetTileType(vector, Tile::Type::Path);
        }
    }
}

void GUIManager::SetInstructionAndColor(const std::string &instruction, const Color &color)
{
    m_infoUI->SetInstructionString(instruction);
    m_infoUIView->SetInstructionTextColor(color);
}

void GUIManager::SetWarningAndColor(const std::string &warning, const Color &color)
{
    m_infoUI->SetWarningString(warning);
    m_infoUIView->SetWarningTextColor(color);
}

Vector2i GUIManager::GetGridSize() const
{
    Vector2i gridSize;
    gridSize.x = std::stoi(m_gameSetup->GetUserInputWindowWidth());                // converting sf::String -> std::string -> unsigned int
    gridSize.y = std::stoi(m_gameSetup->GetUserInputWindowHeight());
    return gridSize;
}