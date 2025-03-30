/**

@file Game.cpp

@brief Implements game logic, handling updates and rendering.
*/


#include "Game.h"
#include "Helpers/Math_Helpers.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

using namespace sf;
using namespace std;

Game::Game(int initialWindowWidth, int initialWindowHeight)
    : m_Window(VideoMode(initialWindowWidth, initialWindowHeight), "Tower Defense Game")           // Initiliaze window screen
    , m_vInitialWindowSize(Vector2i(initialWindowWidth, initialWindowHeight))                    // Set initial window sizes
    , m_eGameMode(GameMode::MainMenu)                                                       // set current game mode to intial set up
    // Initialize previous game mode to InitialSetUp to track game mode transitions later 
    , m_ePrevGameMode(GameMode::None)
    // Initialize managers
    , m_GUIManager(m_Window)
    , m_MonsterManager(m_Window)
    , m_TowerManager(m_Window, m_MonsterManager)
    // ** Projectile observer class
    , m_RapidBulletTemplate()
    , m_iCurrentLevel(1)
    #ifdef DEBUG
    , m_iInitialWealth(10000)
    #else
    , m_iInitialWealth(1000)
    #endif
   
{
    m_Window.setFramerateLimit(60);
    m_Window.setVerticalSyncEnabled(true);
}

/**
 * @brief Main game loop that manages game states and updates the game accordingly.
 * 
 * This function runs the main loop of the game, handling user input, updating game logic, 
 * and rendering different game states such as the main menu, map selection, map editor mode, 
 * and play mode. It ensures that assets are loaded only once when entering a new state 
 * and updates elements like UI and game entities as needed.
 * 
 * @note The function uses a game clock to manage time-based updates and handles transitions 
 * between different game modes.
 */

void Game::Run()
{
    Clock clock;
    // ** Projectile observer class
    Clock FlameThrowerClock;
    while (m_Window.isOpen())
    {
        m_DeltaTime = clock.restart();      // get elapsed time
        //FlameThrowerClock.restart();

        HandleInput();
        
        // Depending on the game mode, update then draw
        switch (m_eGameMode)
        {
        case MainMenu:
        {
            // Initialize main menu only once
            if (m_ePrevGameMode == None)
            {
                m_iCurrentWealth = m_iInitialWealth;
                m_GUIManager.InitializeMainMenu();
                m_ePrevGameMode = MainMenu;
                #ifdef DEBUG
                m_DebugLogger.Log("Main menu assets initialized.");
                #endif
            }
            DrawMainMenu();
            break;
        }
        case MapSelectionMenu:
            if (m_ePrevGameMode == MainMenu)
            {
                m_GUIManager.InitializeMapSelectionMenu();
                m_ePrevGameMode = MapSelectionMenu;
                #ifdef DEBUG
                m_DebugLogger.Log("Map selection menu assets initialized.");
                #endif
            }
            DrawMapSelectionMenu();
            break;
        case InitialSetUp:
        {
            DrawInitialSetUp();
            break;
        }
        case MapEditorMode:
        {   
            // Load MapEditorMode assets only when MapEditorMode is initialized for the first time
            if (m_ePrevGameMode != MapEditorMode)
            {
                InitializeMapEditorMode();

                m_eCurrentEditState = PathEditingState::EntryState;
                m_ePrevGameMode = MapEditorMode;
                #ifdef DEBUG
                m_DebugLogger.Log("Map editor assets initialized.");
                #endif
            }

            UpdateTiles();
            UpdateUI();

            DrawMapEditorMode();
            break;
        }
        case PlayMode:
        {
            // Reset the flame thrower animation
            // Load Play Mode assets once only when PlayMode is initialized for the first time then set previous mode to PlayMode so this condition
            // only triggers once
            if (m_ePrevGameMode != PlayMode)
            {
                // Bullet texture is loaded here. Need to be implemented by the bullet observer pattern
                LoadPlayModeAssets();
                m_ePrevGameMode = PlayMode;

                #ifdef DEBUG
                m_DebugLogger.Log("Play mode assets initialized.");
                #endif
            }

            // If round hasn't ended, game is still playing so keep updating
            if (!m_bIsRoundEnded)
            {
                UpdatePlay();
            }
            // If the round ended, stop updating the play and prepare for the next round.
            else
            {
                // Condition to update the monster generator only once after the round ends
                if (!m_bIsMonsterGeneratorUpdated)
                {
                    // Prepare the next wave of monsters
                    // m_MonsterManager.PrepareNextWave();
                    m_bIsMonsterGeneratorUpdated = true;
                }
            }
            UpdateUI();

            DrawPlayMode();
            break;
        }
        case Pause:
        {
            break;
        }
        case GameOver:
        {
            DrawPlayMode();
            break;
        }
        default:
            break;
        }
    }
}

void Game::InitializeUIAndEntities()
{
    // Initialize InfoUI and InfoUIView objects and load their assets
    m_GUIManager.InitializeInfoUI();
    m_GUIManager.GetInfoUI()->SetCurrentWealth(m_iCurrentWealth);
    m_GUIManager.GetInfoUI()->SetCurrentLevel(m_iCurrentLevel);

    // Resize window to fit the map size + UI width
    m_vWindowSize = m_GUIManager.GetWindowSize();
    m_Window.create(VideoMode(m_vWindowSize.x, m_vWindowSize.y), "New Game");

    m_iTileSize = m_GUIManager.GetMapSetup()->GetTileSize();

    // Initialize Tower manager with mapSize and load its assets
    m_vMapSize = m_GUIManager.GetMapSize();
    int infoUIWidth = m_GUIManager.GetInfoUI()->GetInfoUIWidth();
    m_TowerManager.SetMapSize(m_vMapSize);
    m_TowerManager.SetInfoUIWidth(infoUIWidth);
    m_TowerManager.InitializeGameSetup();

    m_MonsterManager.SetMapSize(m_vMapSize);
    m_MonsterManager.SetInfoUIWidth(infoUIWidth);

    // Get tower price from TowerManager and give it to the InfoUI
    std::vector<std::unique_ptr<TowerEntity>>& templateTowers = m_TowerManager.GetTemplateTowers();
    m_GUIManager.InitiailizeTowerPrice(templateTowers);
}

void Game::LoadMap(std::string& filepath)
{
    #ifdef DEBUG
    m_DebugLogger.Log("Loading a map. Filename: " + filepath);
    #endif
    std::vector<sf::Vector2f> newPath;
    Vector2i gridSize; 
    if (!m_MapStorage.loadData(newPath, gridSize, filepath))
    {
        #ifdef DEBUG
        m_DebugLogger.Log("Map loading failed");
        #endif
    }

    InitializeLoadedMap(newPath, gridSize);
}

void Game::InitializeLoadedMap(std::vector<sf::Vector2f>& newPath, Vector2i& gridSize)
{
    m_GUIManager.InitializeLoadedMapSetup(gridSize);
    m_GUIManager.GetMapSetup()->SetupDefaultTiles();
    m_GUIManager.GetMapSetup()->SetPath(newPath);
    m_GUIManager.GetMapSetup()->EditTilesFromPath();

    InitializeUIAndEntities();

    m_eCurrentEditState = PathEditingState::FinishedPathingState;
    m_ePrevGameMode = MapEditorMode;
}

void Game::InitializeMapEditorMode()
{
    // Initialize the Map with user given grid size and GameSetupView objects and load thier assets
    m_GUIManager.InitializeMapSetup();
    m_GUIManager.GetMapSetup()->SetupDefaultTiles();
    
    InitializeUIAndEntities();
}


void Game::LoadPlayModeAssets()
{
    // Load Monster assets
    m_MonsterManager.LoadMonsterAssets();

    // Assign the entry tile position and prepare the first wave of monsters
    Vector2f entryTile = m_GUIManager.GetMapSetup()->GetEntryTile();
    m_MonsterManager.InitializeMonsters(entryTile);
    m_MonsterManager.UpdateNextMonster();
    UpdateNextMonsterUI();

    m_MonsterManager.UpdateCurrentMonster();
    UpdateCurrentMonsterUI();

    // Bullet observer pattern need to be implemented
    #ifdef LINUX
    m_RapidBulletTexture.loadFromFile("../src/Images/Rapid_Bullet.png");
    m_SniperBulletTexture.loadFromFile("../src/Images/Sniper_Bullet.png");
    m_FlameThrowerBulletTexture.loadFromFile("../src/Images/Flame_1.png");
    for (int i = 1; i <= 8; ++i) {
        sf::Texture texture;
        if (!texture.loadFromFile("../src/Images/Flame_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load tower frame " << i << std::endl;
        }
        m_aFlames.push_back(texture);
    }

    #endif
    #ifdef MAC
    m_RapidBulletTexture.loadFromFile("Images/Rapid_Bullet.png");
    m_SniperBulletTexture.loadFromFile("Images/Sniper_Bullet.png");
    m_FlameThrowerBulletTexture.loadFromFile("Images/Flame_A.png");
    #endif

	m_RapidBulletTemplate.SetTexture(m_RapidBulletTexture);
	m_RapidBulletTemplate.SetScale(Vector2f(0.3, 0.3));
	m_RapidBulletTemplate.SetOrigin(Vector2f(8, 8));

	m_SniperBulletTemplate.SetTexture(m_SniperBulletTexture);
	m_SniperBulletTemplate.SetScale(Vector2f(0.5, 0.5));
	m_SniperBulletTemplate.SetOrigin(Vector2f(8, 8));

    m_FlameThrowerBulletTemplate.SetTexture(m_FlameThrowerBulletTexture);
    m_FlameThrowerBulletTemplate.SetScale(Vector2f(0.5, 0.5));
    m_FlameThrowerBulletTemplate.SetOrigin(Vector2f(8, 8));
}

void Game::HandlePlayAgain()
{
    m_ePrevGameMode = PlayMode;
    m_eGameMode = PlayMode;

    m_bIsRoundEnded = true;
    m_bIsMonsterGeneratorUpdated = true;

    m_iCurrentWealth = 0;
    UpdateWealth(m_iInitialWealth);

    m_iCurrentLevel = 0;
    UpdateLevel();

    ResetEntities();
}

void Game::HandleGameRestart()
{
    m_Window.create(VideoMode(m_vInitialWindowSize.x, m_vInitialWindowSize.y), "Tower Defense Game");

    m_ePrevGameMode = None;
    m_eGameMode = MainMenu;

    // Reset flags
    m_eCurrentEditState = EntryState;
    m_IsPathingMousePressed = false;
    m_isHovering = false;
    m_lastHoveredTower = nullptr;
    m_bIsRoundEnded = false;
    m_bIsMonsterGeneratorUpdated = false;

    // Reset player stat
    m_iCurrentLevel = 1;
    m_iCurrentWealth = m_iInitialWealth;

    ResetEntities();
}

void Game::ResetEntities()
{
    // Clear towers and reinitialize
    m_TowerManager.RemoveAllTowers();
    m_TowerManager.InitializeGameSetup();

    // Clear monsters and reinitialize
    m_MonsterManager.PrepareFirstWave();

    // Clear projectiles and reinitialize
    m_aAxes.clear();
}

void Game::HandleInput()
{
    Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            m_Window.close();
        }
        if (m_ePrevGameMode == MainMenu && m_eGameMode == MainMenu)
        {
            Vector2i mousePosition = Mouse::getPosition(m_Window);                                  // Get mouse position by pixel
            Vector2f translatedPosition = m_Window.mapPixelToCoords(mousePosition);
            MainMenuDriver* mainMenuPtr = m_GUIManager.GetMainMenu();
            mainMenuPtr->HandleButtonHover(translatedPosition);

            if (event.type == Event::MouseButtonPressed)
            {
                mainMenuPtr->HandleButtonClicked(translatedPosition);
            }
            if (event.type == Event::MouseButtonReleased)
            {
                const Button* chooseMapButtonPtr = mainMenuPtr->GetChooseMapButton();
                const Button* MapEditorButtonPtr = mainMenuPtr->GetMapEditorButton();
                const Button* ExitButtonPtr = mainMenuPtr->GetExitButton(); 
                if (chooseMapButtonPtr->IsMouseOver(translatedPosition))
                {
                    m_eGameMode = MapSelectionMenu;
                }
                else if (MapEditorButtonPtr->IsMouseOver(translatedPosition))
                {
                    m_eGameMode = InitialSetUp;
                } 
                else if (ExitButtonPtr->IsMouseOver(translatedPosition))
                {
                    m_Window.close();
                }

            }
        }
        else if (m_ePrevGameMode == MapSelectionMenu && m_eGameMode == MapSelectionMenu)
        {
            Vector2i mousePosition = Mouse::getPosition(m_Window);                                  // Get mouse position by pixel
            Vector2f translatedPosition = m_Window.mapPixelToCoords(mousePosition);
            MapSelectionDriver* mapSelectionMenuPtr = m_GUIManager.GetMapSelectionMenu();
            mapSelectionMenuPtr->HandleButtonHover(translatedPosition);
            if (event.type == Event::MouseButtonPressed)
            {
                mapSelectionMenuPtr->HandleButtonClicked(translatedPosition);
            }
            if (event.type == Event::MouseButtonReleased)
            {
                const Button* MediumButtonPtr = mapSelectionMenuPtr->GetMediumMapButton();
                const Button* HardButtonPtr = mapSelectionMenuPtr->GetHardMapButton();
                const Button* BackButtonPtr = mapSelectionMenuPtr->GetBackButton(); 
                if (MediumButtonPtr->IsMouseOver(translatedPosition))
                {
                    LoadMap(m_MapStorage.GetMediumMapFilePath());
                    m_eGameMode = MapSelectionMenu;
                    m_eGameMode = MapEditorMode;
                }
                else if (HardButtonPtr->IsMouseOver(translatedPosition))
                {
                    LoadMap(m_MapStorage.GetHardMapFilePath());
                    m_eGameMode = MapSelectionMenu;
                    m_eGameMode = MapEditorMode;
                } 
                else if (BackButtonPtr->IsMouseOver(translatedPosition))
                {
                    m_eGameMode = MainMenu;
                    m_ePrevGameMode = MainMenu;
                }
            }
        }
        // Handle inputs for initial SetUp //
        else if (m_eGameMode == InitialSetUp)
        {
            
            if (m_ePrevGameMode == MainMenu)
            {
                // Some logic 
                m_ePrevGameMode = InitialSetUp;
            }
            
            Vector2i mousePosition = Mouse::getPosition(m_Window);                                  // Get mouse position by pixel
            Vector2f translatedPosition = m_Window.mapPixelToCoords(mousePosition);                 // Translate mouse position to game tile coordinate
            //std::array<sf::Sprite, 2>& buttonBoxArray = m_GUIManager.GetGameSetupView()->GetButtonBoxes();              
            GameSetupView* gameSetupViewPtr = m_GUIManager.GetGameSetupView();
            gameSetupViewPtr->HandleButtonHover(translatedPosition);
            if (event.type == Event::MouseButtonPressed) 
            {
                // When input box is clicked
                std::array<sf::RectangleShape, 2>& userInputBoxArray = m_GUIManager.GetGameSetupView()->GetUserInputBoxWindowSize();
                if (userInputBoxArray[0].getGlobalBounds().contains(translatedPosition))        // Check if mouse position is within the width input box
                {
                    m_GUIManager.GetGameSetupView()->SetCurrentlyActiveInputBox(GameSetupView::Width);
                } 
                else if (userInputBoxArray[1].getGlobalBounds().contains(translatedPosition))   // Check if mouse position is within the height input box
                {
                    m_GUIManager.GetGameSetupView()->SetCurrentlyActiveInputBox(GameSetupView::Height);
                }
                else                                                                                    // If clicked anywhere outside the input box
                {   
                    gameSetupViewPtr->HandleButtonCliked(translatedPosition);
                    m_GUIManager.GetGameSetupView()->SetCurrentlyActiveInputBox(GameSetupView::None);                     
                }
            }
            if (event.type == Event::MouseButtonReleased)
            {
                const Button* playButtonPtr = gameSetupViewPtr->GetPlayButton();
                const Button* backButtonPtr = gameSetupViewPtr->GetBackButton();
                if (playButtonPtr->IsMouseOver(translatedPosition))
                {
                    //Get the grid size from the user input
                    Vector2i gridSize = m_GUIManager.GetGridSize();
                    // Apply input limit from 10 to 20
                    if (gridSize.x >= 10 && gridSize.x <= 20 && gridSize.y >= 10 && gridSize.y <= 20)
                    {
                        m_eGameMode = MapEditorMode;
                    }
                    else
                    {
                        m_GUIManager.GetGameSetupView()->SetIsSizeLimitTextShown(true);
                    }
                }
                else if (backButtonPtr->IsMouseOver(translatedPosition))
                {
                    m_GUIManager.ResetGameSetup();
                    m_eGameMode = MainMenu;
                    m_ePrevGameMode = MainMenu;
                } 
            }

            // **** Need separate class for InputHandle
            if (event.type == Event::TextEntered)
            {
                // Depending on which box is clicked, update the corresponding text
                const GameSetupView::ClickedInputBox& currentlyActiveInputBox = m_GUIManager.GetGameSetupView()->GetCurrentlyActiveInputBox();
                switch (currentlyActiveInputBox)
                {
                case GameSetupView::Width:
                {
                    std::string currentText = m_GUIManager.GetGameSetup()->GetUserInputWindowWidth();
                    EditMapSizeInputText(event, currentText);
                    m_GUIManager.GetGameSetup()->SetUserInputWindowWidth(currentText);
                    break;
                }
                case GameSetupView::Height:
                {
                    std::string currentText = m_GUIManager.GetGameSetup()->GetUserInputWindowHeight();
                    EditMapSizeInputText(event, currentText);
                    m_GUIManager.GetGameSetup()->SetUserInputWindowHeight(currentText);
                }
                case GameSetupView::None:
                {
                    break;
                }
                }
            }
        }

        // Handle inputs for Map Editor Mode //
        if (m_eGameMode == MapEditorMode)
        {
            ////////////// Need reset button and functionality

            if (event.type == sf::Event::MouseButtonPressed) 
            {
                sf::Vector2f clickedPos(event.mouseButton.x, event.mouseButton.y);
                sf::Vector2f gridPos = MathHelpers::getNearestTileCenterPosition(clickedPos, m_iTileSize);

                if (event.mouseButton.button == sf::Mouse::Left && clickedPos.x <= m_vMapSize.x && clickedPos.y <= m_vMapSize.y)
                {
                    // If EntryState, check if the tile clicked is from the edge tiles then save the clicked tile as the entry tile then append is to the arrays
                    if (m_eCurrentEditState == EntryState)
                    {
                        if (m_GUIManager.InitializeEntryTile(gridPos))
                        {
                            m_eCurrentEditState = ExitState;
                        }
                    }
                    // if ExitState, check if the tile clicked is from the edge tiles then sanve the clicked tile as the exit tile
                    // the exit tile will be appended to the arrays later when the entry tile and the exit tiles are linked together with path tile
                    else if (m_eCurrentEditState == ExitState) 
                    {
                        if (m_GUIManager.InitializeExitTile(gridPos))
                        {
                            m_eCurrentEditState = PathState;
                        }

                    }
                    else if (m_eCurrentEditState == PathState)
                    {
                        m_IsPathingMousePressed = true;
                    }
                }
            }

            // Enable dragging mouse for linking path
            if (event.type == sf::Event::MouseMoved)
            {
                // PATHING RELATED
                // If this is true, mouse is being dragged within the map
                if (m_IsPathingMousePressed)
                {

                    sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);

                    // Constrain gridPos to the window boundaries
                    sf::Vector2f gridPos = MathHelpers::getNearestTileCenterPosition(mousePos, m_iTileSize);      // Snap the mouse position to the grid
                    gridPos.x = std::clamp(gridPos.x, 0.f, static_cast<float>(m_vMapSize.x));  // Clamp x-coordinate
                    gridPos.y = std::clamp(gridPos.y, 0.f, static_cast<float>(m_vMapSize.y));  // Clamp y-coordinate

                    // Check if the gridPos is adjacent to the last path tile
                    std::vector<sf::Vector2f>& path = m_GUIManager.GetMapSetup()->GetPath();
                    if (!path.empty() && MathHelpers::isAdjacent(path.back(), gridPos, m_iTileSize))
                    {
                        // When the path tile overlaps with the exit tile, we reached the end of pathing. Append exit tile. Ensure we don't move beyond the exit tile
                        if (m_GUIManager.FinalizeExitTile(gridPos))
                        {
                            m_eCurrentEditState = FinishedPathingState;
                        }
                        // Prevent backtracking
                        else if (path.size() > 1 && path[path.size() - 2] == gridPos)
                        {
                            // Append the path tile to the deleted path array
                            m_GUIManager.GetMapSetup()->PushDeletedPathTile(path.back());
                            
                            // Remove the path tile from the path array
                            m_GUIManager.GetMapSetup()->PopPathTile();
                            // ** For white line implementation. Remove the path tile from the path lines array
                        }
                        // Skeleton pathing. first check if the current tile is not the previous tile then append path tile
                        else if (path.back().x != gridPos.x || path.back().y != gridPos.y)
                        {
                            m_GUIManager.GetMapSetup()->PushPathTile(gridPos);
                        }
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    m_IsPathingMousePressed = false;
                }
            }

            static bool bTWasPressedLastUpdate = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                if (!bTWasPressedLastUpdate)
                {
                    // Go to play mode only when there is a valid path
                    if (m_GUIManager.GetMapSetup()->ValidatePath())
                    {
                        #ifdef SAVE_MAP
                        m_MapStorage.saveData(m_GUIManager.GetMapSetup()->GetPath(), m_GUIManager.GetMapSetup()->GetGridSize(), m_MapStorage.GetPlaceHolderFilePath());
                        #endif
                        m_eGameMode = PlayMode;
                    }
                }
                bTWasPressedLastUpdate = true;
            }
            else
            {
                bTWasPressedLastUpdate = false;
            }
        }

        // Handle inputs for Play Mode and Map Editor Mode
        // Only handle inputs after map editor assets have loaded => m_eGameMode == MapEditorMode
        if (m_eGameMode == PlayMode || (m_eGameMode == MapEditorMode && m_ePrevGameMode == MapEditorMode)){
            
            sf::Vector2f mousePos = m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window));
            Vector2f snapGrid = MathHelpers::getNearestTileCenterPosition(mousePos, 50);
            
            // std::vector<TowerEntity>& templateTowers = m_TowerManager.GetTemplateTowers();
            // std::vector<TowerEntity>& activeTowers = m_TowerManager.GetActiveTowers();
            std::vector<std::unique_ptr<TowerEntity>>& templateTowers = m_TowerManager.GetTemplateTowers();
            std::vector<std::unique_ptr<TowerEntity>>& activeTowers = m_TowerManager.GetActiveTowers();

            InfoUIView* infoUIView = m_GUIManager.GetInfoUIView();
            TowerEntityView& towerView = m_TowerManager.GetTowerEntityView();
            const TowerEntityView::TowerEntityData* draggedTowerData = towerView.GetDraggedTowerEntityData();

            // Handle mouse click (start dragging)
            if (Mouse::isButtonPressed(Mouse::Left) && m_eCurrentEditState == FinishedPathingState) {
                
                //for (size_t i = 0; i < templateTowers.size(); ++i)
                for (std::unique_ptr<TowerEntity>& towerPtr : templateTowers)
                {
                    // TowerEntity* tower = templateTowers[i];
                    
                    const TowerEntityView::TowerEntityData* towerData = towerView.GetTowerEntityData(towerPtr.get());

                    // Check if tower exists in the view, the mouse is within the bounds of the tower sprite, and no tower is currently being dragged...
                    if (towerData != nullptr && towerData->sprite.getGlobalBounds().contains(mousePos) && draggedTowerData == nullptr)
                    {
                        towerView.StartDraggingTower(towerData);
                    }
                }
            }

            // Update dragged tower position while dragging
            towerView.UpdateDraggedTower(mousePos);

            // Handle mouse release (stop dragging)
            if (event.type == sf::Event::MouseButtonReleased && m_eCurrentEditState == FinishedPathingState) {

                
                // **RIGHT CLICK TO REMOVE A TOWER**
                if (event.mouseButton.button == sf::Mouse::Right) 
                {
                    for (std::unique_ptr<TowerEntity>& towerPtr : activeTowers) 
                    {
                        Vector2f towerPosition = towerPtr->GetPosition();
                        if (std::abs(towerPosition.x - snapGrid.x) < 0.5f &&
                            std::abs(towerPosition.y - snapGrid.y) < 0.5f)
                        {
                            int cost = towerPtr->GetCost();
                            float sellRate = m_TowerManager.GetSellRate();
                            UpdateWealth(cost * sellRate);

                            m_TowerManager.RemoveTowerAtPosition(snapGrid);

                            m_GUIManager.SetWarningAndColor("Tower removed", sf::Color::Green);

                            warningShown.restart();

                            return; // Exit after removing one tower
                        }
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Check for existing towers at the snapGrid position
                    bool towerExists = false;
                    for (const std::unique_ptr<TowerEntity>& towerPtr : activeTowers) 
                    {
                        const float tolerance = 0.5f;
                        Vector2f towerPosition = towerPtr->GetPosition();
                        if (std::abs(towerPosition.x - snapGrid.x) < tolerance &&
                            std::abs(towerPosition.y - snapGrid.y) < tolerance)
                        {
                            towerExists = true; // No need to check further once we find an existing tower
                            break;
                        }
                    }

                    if (towerExists) 
                    {
                        m_GUIManager.SetWarningAndColor("Warning: There's already a tower here", sf::Color::Red);
                        warningShown.restart();   // Start the timer to show the warning for a short time
                        towerView.StopDraggingTower();
                    }
                    else
                    {
                        // Check if the position is on the path
                        const std::vector<sf::Vector2f>& path = m_GUIManager.GetMapSetup()->GetPath();
                        bool onPath = false;
                        for (const auto& tilePos : path) 
                        {
                            if (tilePos.x == snapGrid.x && tilePos.y == snapGrid.y) 
                            {
                                onPath = true;
                                break;
                            }
                        }

                        if (draggedTowerData != nullptr && snapGrid.x >= 0 && snapGrid.y >= 0 && snapGrid.x < m_vMapSize.x && snapGrid.y < m_vMapSize.y && !onPath) 
                        {
                            int cost = draggedTowerData->cost;
                            if (m_iCurrentWealth < cost)
                            {
                                m_GUIManager.SetWarningAndColor("Warning: Cannot afford this tower", sf::Color::Red);
                                warningShown.restart();
                            }
                            else
                            {
                                UpdateWealth(-cost);

                                m_TowerManager.CreateTower(draggedTowerData->type, snapGrid);

                                m_GUIManager.SetWarningAndColor("Successfully placed tower", sf::Color::Green);
                                warningShown.restart();
                            }

                            towerView.StopDraggingTower();
                        }
                        // Invalid placement
                        else
                        {
                            if (draggedTowerData != nullptr)
                            {
                                m_GUIManager.SetWarningAndColor("Warning: Invalid tower placement", sf::Color::Red);
                                warningShown.restart();   // Start the timer to show the warning for a short time
                            }
                            
                            towerView.StopDraggingTower();
                        }
                    }
                }
            }

            if (event.type == sf::Event::MouseMoved && draggedTowerData == nullptr ) {

                m_isHovering = false;  // Reset the flag to false
                for (size_t i = 0; i < activeTowers.size(); ++i)       // Modifying a_allActiveTowers while iterating may cause iterators/pointers to become invalid. Use index based iteration
                {
                    std::unique_ptr<TowerEntity>& towerPtr = activeTowers[i]; 
                    Vector2f towerPosition = towerPtr->GetPosition();
                    if (towerPosition.x == snapGrid.x && towerPosition.y == snapGrid.y) 
                    {
                        infoUIView->UpdateCrossShapePosition(snapGrid);
                        m_isHovering = true;  // Set flag to true if hovering over this tower

                        m_lastHoveredTower = &towerPtr; // Update the last hovered tower
                        
                        break;
                    }
                }

                // If the mouse is not over any tower, reset the hover state
                if (!m_isHovering) {
                    
                    m_lastHoveredTower = nullptr;
                }

                // Set m_isHoveringOnTower based on whether the mouse is over a tower
                infoUIView->SetHoveringOnTower(m_isHovering);
                towerView.SetHoveringOnTower(m_isHovering);
                m_MonsterManager.GetMonsterEntityView().SetHoveringOnTower(m_isHovering);
            }   

            // ** UI
            if (m_isHovering) {
                
                if(placementOrUpgradeTimer.getElapsedTime().asMilliseconds() > 800){
                 
                    for (std::unique_ptr<TowerEntity>& towerPtr : activeTowers) {

                        Vector2f towerPosition = towerPtr->GetPosition();
                        if (towerPosition.x == snapGrid.x && towerPosition.y == snapGrid.y) {
                            
                            m_GUIManager.UpdateTowerHoverUI(towerPtr);
                            break;
                        }
                    }
                }
            } 
            

            // Perform upgrade when E is pressed
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E && m_lastHoveredTower != nullptr) 
            {
                
                int upgradeCost = (*m_lastHoveredTower)->GetUpgradeCost();
                if (m_iCurrentWealth >= upgradeCost) 
                {
                    if ((*m_lastHoveredTower) && (*m_lastHoveredTower)->CanUpgrade())  
                    {
                        UpdateWealth(-(upgradeCost));

                         // Apply all upgrades (decorators)
                        m_TowerManager.ApplyUpgrades(m_lastHoveredTower);

                        // Upgrade the tower level and notifychange 
                        (*m_lastHoveredTower)->IncrementLevel();

                        m_GUIManager.SetWarningAndColor("Tower upgraded successfully!", sf::Color::Green);
                    }
                    else 
                    {
                        m_GUIManager.SetWarningAndColor("Warning: Tower is at max level!", sf::Color::Red);
                    }
                    
                } 
                else 
                {
                    m_GUIManager.SetWarningAndColor("Warning: Not enough money for upgrade!", sf::Color::Red);
                    
                }
                warningShown.restart();
            }
            
            // To start a new round
            static bool bTWasPressedLastUpdate = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                
                if (!bTWasPressedLastUpdate && m_eGameMode == PlayMode && m_bIsRoundEnded == true)
                {
                    m_MonsterManager.PrepareNextWave();
                    
                    m_MonsterManager.UpdateNextMonster();
                    UpdateNextMonsterUI();

                    m_MonsterManager.UpdateCurrentMonster();
                    UpdateCurrentMonsterUI();

                    m_bIsRoundEnded = false;
                    m_bIsMonsterGeneratorUpdated = false;
                }
                bTWasPressedLastUpdate = true;
            }
            else
            {
                bTWasPressedLastUpdate = false;
            }
        }
        if (m_eGameMode == GameOver)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
            {
                HandlePlayAgain();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            {
                HandleGameRestart();
            }
        }
    }
}

void Game::EditMapSizeInputText(Event& event, std::string& currentText)                   // Add limit condition for input (input must be between 5 and 30??)
{
    // when keyboard input is a digit, append the text
    if (event.text.unicode >= '0' && event.text.unicode <= '9')
    {
        currentText += static_cast<char>(event.text.unicode);
    }
    // when key board input is backspace and if the text is not empty, delete the last character of the text
    else if (event.text.unicode == 8 && !currentText.empty())
    {
        currentText.pop_back();
    }
}

// ** MAP
void Game::UpdateTiles()
{
    if (m_eCurrentEditState == EntryState)
    {
        m_GUIManager.BlinkTiles(Tile::Type::EntryHighlight, m_DeltaTime);
    }
    // Change the colors, set tile type of entry, exit.
    else if (m_eCurrentEditState == ExitState)
    {
        m_GUIManager.BlinkTiles(Tile::Type::ExitHighlight, m_DeltaTime);
    }
    else if (m_eCurrentEditState == PathState)
    {
        // If deleted path exist in the array, reset the tile type and texture of the deleted path for all elements in the array
        // Then remove all elements from the array
        // And, set tile type and change the texture of all current path tiles
        m_GUIManager.UpdatePathTiles();      
    }
}

void Game::UpdatePlay()
{
    UpdateMonsters();
    UpdateTowers();
    UpdateAxes();

    if (m_MonsterManager.IsAllMonstersSpawned() && m_MonsterManager.IsAllMonstersDead())
    {
        IncreaseLevel();
        
        m_bIsRoundEnded = true;
    }

    if (m_iCurrentWealth < 0){
        m_eGameMode = GameOver;
    }
}

void Game::UpdateMonsters()
{
    const std::vector<sf::Vector2f>& path = m_GUIManager.GetMapSetup()->GetPath();
    std::vector<std::unique_ptr<MonsterEntity>>& activeMonsters = m_MonsterManager.GetActiveMonsters();

    // Generate monsters
    m_MonsterManager.GenerateCurrentWave(m_DeltaTime.asSeconds());

    // Update monsters
    for (std::unique_ptr<MonsterEntity>& monsterPtr : activeMonsters)
    {
        if (monsterPtr->GetIsDead() == false && monsterPtr->GetIsDying() == false)
        { 
            if (monsterPtr->GetHealth() <= 0)
            {
                #ifdef DEBUG
                m_DebugLogger.Log("Monster destroyed!");
                #endif
                UpdateWealth(monsterPtr->GetReward());
                monsterPtr->SetIsDying(true);
            }
            // If monster reaches the exit tile, player looses wealth then monster is removed
            else if (monsterPtr->GetCurrentPathIndex() >= path.size() - 1)
            {
                UpdateWealth(-(monsterPtr->GetStrength()));

                m_MonsterManager.RemoveMonster(monsterPtr.get()); 
            }

            m_MonsterManager.UpdateSpeedDebuff(monsterPtr, m_DeltaTime.asSeconds());
            m_MonsterManager.UpdateBurnEffect(monsterPtr, m_DeltaTime.asSeconds());
        }

        // If monster is finished dying, remove monster
        if (monsterPtr->GetIsFinishedDying() == true && monsterPtr->GetIsDead() == false)
        {
            m_MonsterManager.RemoveMonster(monsterPtr.get());
        }
    }


    // Monster animation related
    m_MonsterManager.UpdateMonsterAnimations(m_fFrameTime);


    // Update monster positions
    for (std::unique_ptr<MonsterEntity>& monsterPtr : activeMonsters)
    {
        size_t monsterCurrentTileIndex = monsterPtr->GetCurrentPathIndex();
        if (monsterPtr->GetIsDying() == false && monsterPtr->GetIsDead() == false && monsterCurrentTileIndex < path.size() - 1)
        {
            Vector2f nextTilePos = path[monsterCurrentTileIndex + 1];
            Vector2f tileToMonster = nextTilePos - monsterPtr->GetPosition();
            float distanceToNext = MathHelpers::Length(tileToMonster);

            // Calculate movement step based on speed and time
            float dt = std::min(m_DeltaTime.asSeconds(), 0.1f);                 // Fix delta time fluctuations
            float moveStep = dt * monsterPtr->GetSpeed();

            // Ensure we don't overshoot
            moveStep = std::min(moveStep, distanceToNext);

            // Normalize safely
            Vector2f direction = (distanceToNext > 1e-6f) ? MathHelpers::getNormalize(tileToMonster) : Vector2f(0, 0);

            // Move the monster with the adjusted moveStep
            monsterPtr->Move(direction * moveStep);

            // If the monster has reached the tile, update its path index
            if (distanceToNext <= moveStep + 1e-6f)  // Small epsilon to handle float precision issues
            {
                monsterPtr->SetCurrentPathIndex(monsterCurrentTileIndex + 1);
                monsterPtr->SetPosition(nextTilePos); // Snap position exactly
            }
        }
    }
}


// ** UI
void Game::UpdateUI()
{
    // Update the UI elements    
    if(warningShown.getElapsedTime().asSeconds() > 3){
        m_GUIManager.GetInfoUI()->SetWarningString("");
    }
    
    // Handle different game edit states
    switch (m_eCurrentEditState) 
    {
        case ExitState:
            m_GUIManager.SetInstructionAndColor("Choose an exit Tile...", Color::Red);
            break;
        case EntryState:
            m_GUIManager.SetInstructionAndColor("Choose an entry Tile...", Color::Green);
            break;
        case PathState:
            m_GUIManager.SetInstructionAndColor("Drag to draw a path from entry to exit", Color::Yellow);
            break;
        default:
            m_GUIManager.SetInstructionAndColor("Press Enter to Begin the Round!", Color::Green);
            break;
    }
}

void Game::UpdateTowers()
{
    std::vector<std::unique_ptr<TowerEntity>>& activeTowers = m_TowerManager.GetActiveTowers();
    std::vector<std::unique_ptr<MonsterEntity>>& activeMonsters = m_MonsterManager.GetActiveMonsters();

    for (std::unique_ptr<TowerEntity>& towerPtr : activeTowers)
    {
        // Update individual tower cooldown
        towerPtr->UpdateCooldown(m_DeltaTime.asSeconds());

        if (towerPtr->CanShoot()) {
            MonsterEntity* pNearestEnemy = nullptr;
            //float fShortestDistance = std::numeric_limits<float>::max();
            
            // **** Related to strategy pattern
            // Find nearest monster within this tower's range
            // for (MonsterEntity& monster : activeMonsters)
            // {
            //     sf::Vector2f vTowerToMonster = monster.GetPosition() - towerPtr->GetPosition();
            //     float fDistance = MathHelpers::Length(vTowerToMonster);
            //     if (!monster.GetIsDying() && !monster.GetIsDead() && fDistance < fShortestDistance && fDistance < towerPtr->GetRange())
            //     {
            //         fShortestDistance = fDistance;
            //         pNearestEnemy = &monster;
            //     }
            // }
            pNearestEnemy = towerPtr->SelectTarget(activeMonsters);
    
            if (pNearestEnemy != nullptr)
            {
                // Create and setup new axe
                if (towerPtr->GetType() == TowerGeneratorData::TowerType::Rapid) 
                {
                    m_aAxes.push_back(m_RapidBulletTemplate);
                } 
                else if (towerPtr->GetType() == TowerGeneratorData::TowerType::Sniper) 
                {
                    m_aAxes.push_back(m_SniperBulletTemplate);
                }
                else if (towerPtr->GetType() == TowerGeneratorData::TowerType::FlameThrower)
                {
                    m_aAxes.push_back(m_InvisibleFlameThrowerBulletTemplate);
                    towerPtr->SetIsFlameThrowerActive(true);
                }
                else
                {
                    std::cerr << "Error: Invalid tower type" << std::endl;
                }
                
                // **** Bullet observer pattern needed
                //ADD BULLET WHEN I ADD TOWERS
                //Regular Bullets
                if(!m_aAxes.empty()){
                    Entity& newAxe = m_aAxes.back();
                    newAxe.SetProjectileType(towerPtr->GetType());
                    FloatRect newAxeBounds = newAxe.GetSprite().getLocalBounds(); // Assuming getSprite() returns an sf::Sprite reference
                    newAxe.SetOrigin(Vector2f(newAxeBounds.width / 2, newAxeBounds.height / 2));
                    newAxe.SetPosition(Vector2f(towerPtr->GetPosition().x, towerPtr->GetPosition().y));
                    //Depending on tower the bullet will be faster or slower and do more or less damage
                    newAxe.m_speed = towerPtr->GetSpeed();
                    newAxe.m_fDamage = towerPtr->GetDamage();
                    // Calculate direction to enemy
                    sf::Vector2f vTowerToMonster = pNearestEnemy->GetPosition() - towerPtr->GetPosition();
                    vTowerToMonster = MathHelpers::getNormalize(vTowerToMonster);
                    // Calculate the angle in degrees
                    float angle = atan2(vTowerToMonster.y, vTowerToMonster.x) * 180.0f / M_PI + 90.0f;
                    newAxe.SetDirection(vTowerToMonster);
                    newAxe.SetRotation(angle);
                }

                // Flame Thrower Bullets
                if (towerPtr->GetType() == TowerGeneratorData::TowerType::FlameThrower) {
                    // Flame thrower animation turning on

                    sf::Clock& clock = towerPtr->GetFlameClock();
                    if (pNearestEnemy && clock.getElapsedTime().asMilliseconds() > 85) {
                        //MonsterEntity* target = static_cast<MonsterEntity*>(pNearestEnemy);

                        int frame = towerPtr->GetFlameFrame();
                        towerPtr->GetFlameSprite().SetTexture(m_aFlames[frame]);

                        towerPtr->IncrementFlameFrame();
                        if (towerPtr->GetFlameFrame() >= 7)
                            towerPtr->SetFlameFrame(4);

                        clock.restart();
                    }

                    // Set flame position and rotation
                    if (pNearestEnemy) {
                        sf::Vector2f towerPos = towerPtr->GetPosition();
                        sf::Vector2f dir = MathHelpers::getNormalize(pNearestEnemy->GetPosition() - towerPos);
                        float angle = atan2(dir.y, dir.x) * 180.0f / M_PI + 90.0f;
                        float offset = 60.0f;

                        sf::FloatRect flameBounds = towerPtr->GetFlameSprite().GetSprite().getLocalBounds();
                        towerPtr->GetFlameSprite().SetOrigin(sf::Vector2f(flameBounds.width / 2, flameBounds.height / 2));
                        towerPtr->GetFlameSprite().SetPosition(towerPos + dir * offset);
                        towerPtr->GetFlameSprite().SetRotation(angle);
                        towerPtr->GetFlameSprite().SetScale(Vector2f(0.5f, 0.5f));
                    }
                }
                towerPtr->ResetCooldown(); // Reset this tower's cooldown
                
            } else {
                if (towerPtr->GetType() == TowerGeneratorData::TowerType::FlameThrower) {

                    sf::Clock& clock = towerPtr->GetFlameClock();

                    if (!pNearestEnemy && towerPtr->GetIsFlameThrowerActive()) {
                        if (clock.getElapsedTime().asMilliseconds() > 100 && towerPtr->GetFlameFrame() > 0) {
                            towerPtr->GetFlameSprite().SetTexture(m_aFlames[towerPtr->GetFlameFrame()]);
                            towerPtr->DecrementFlameFrame();
                            clock.restart();
                        }
                        if (towerPtr->GetFlameFrame() == 0)
                            towerPtr->SetIsFlameThrowerActive(false);
                    }
                    
                    // Set flame position and rotation
                    if (pNearestEnemy && towerPtr->GetIsFlameThrowerActive()) {
                        sf::Vector2f towerPos = towerPtr->GetPosition();
                        sf::Vector2f dir = MathHelpers::getNormalize(pNearestEnemy->GetPosition() - towerPos);
                        float angle = atan2(dir.y, dir.x) * 180.0f / M_PI + 90.0f;
                        float offset = 60.0f;

                        sf::FloatRect flameBounds = towerPtr->GetFlameSprite().GetSprite().getLocalBounds();
                        towerPtr->GetFlameSprite().SetOrigin(sf::Vector2f(flameBounds.width / 2, flameBounds.height / 2));
                        towerPtr->GetFlameSprite().SetPosition(towerPos + dir * offset);
                        towerPtr->GetFlameSprite().SetRotation(angle);
                        towerPtr->GetFlameSprite().SetScale(Vector2f(0.5f, 0.5f));
                    }
                }
            }
        }
    }
    // ALL TOWER ANIMATION RELATED
    m_TowerManager.UpdateTowerAnimations(m_fFrameTime);

}

void Game::UpdateAxes()
{
    const float COLLISION_DISTANCE = 25.0f; // Adjust collision radius as needed
    std::vector<std::unique_ptr<MonsterEntity>>& activeMonsters = m_MonsterManager.GetActiveMonsters();

    for (auto it = m_aAxes.begin(); it != m_aAxes.end();)
    {
        bool hitMonster = false;

        // Move axe
        it->Move(it->GetDirection() * it->GetSpeed() * m_DeltaTime.asSeconds());

        // ** Strategy Pattern
        // Check collision with monsters
        // for (int i = static_cast<int>(activeMonsters.size()) - 1; i >= 0; --i)
        for (std::unique_ptr<MonsterEntity>& monsterPtr : activeMonsters)
        {
            sf::Vector2f diff = monsterPtr->GetPosition() - it->GetPosition();
            float distance = MathHelpers::Length(diff);


            if (monsterPtr->GetIsDead() == false && monsterPtr->GetIsDying() == false && distance < COLLISION_DISTANCE)
            {
                std::string hitMonsterName;

                #ifdef DEBUG
                    switch (static_cast<int>(monsterPtr->GetType()))
                    {
                        case 0: hitMonsterName = "Skeleton"; break;
                        case 1: hitMonsterName = "Reaper"; break;
                        case 2: hitMonsterName = "Golem"; break;
                        case 3: hitMonsterName = "Ogre"; break;
                        case 4: hitMonsterName = "Minotaur"; break;
                        default: hitMonsterName = "Unknown"; break;
                    }
                    m_DebugLogger.Log("Debug: Axe hit %s at position (%.2f, %.2f)", 
                       hitMonsterName.c_str(), 
                       monsterPtr->GetPosition().x, 
                       monsterPtr->GetPosition().y);
                #endif


                hitMonster = true;
                monsterPtr->SetHealth(monsterPtr->GetHealth() - it->GetDamage());
                
                if (it->GetProjectileType() == TowerGeneratorData::TowerType::Sniper)
                {
                    #ifdef DEBUG
                    m_DebugLogger.Log("applying speed debuff");
                    #endif
                    m_MonsterManager.ApplySpeedDebuffToMonster(monsterPtr);
                }
                else if (it->GetProjectileType() == TowerGeneratorData::TowerType::FlameThrower)
                {
                    m_MonsterManager.ApplyBurnEffectToMonster(monsterPtr);
                }
                break;
            }
        }

        // Remove axe if it hit something or went off screen
        if (hitMonster ||
            it->GetPosition().x < 0 ||
            it->GetPosition().x > m_vMapSize.x ||
            it->GetPosition().y < 0 ||
            it->GetPosition().y > m_vMapSize.y)
        {
            it = m_aAxes.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Game::UpdateNextMonsterUI()
{
    std::unique_ptr<MonsterEntity>& nextMonster = m_MonsterManager.GetNextMonster();
    m_GUIManager.UpdateMonsterUi(nextMonster->GetType(), nextMonster->GetLevel());
}

void Game::UpdateCurrentMonsterUI()
{
    std::unique_ptr<MonsterEntity>& currentMonster = m_MonsterManager.GetCurrentMonster();
    m_GUIManager.UpdateCurrentMonsterUi(currentMonster->GetType(), currentMonster->GetLevel());
}

void Game::DrawMainMenu()
{
    m_Window.clear();

    m_GUIManager.GetMainMenu()->Draw();

    m_Window.display();
}

void Game::DrawMapSelectionMenu()
{
    m_Window.clear();

    m_GUIManager.GetMapSelectionMenu()->Draw();

    m_Window.display();
}

// ** EDIT TO IMPLEMENT GAMESETUP VIEW CLASS
void Game::DrawInitialSetUp()
{
    // Erases everything that was drawn last frame
	m_Window.clear();

    m_GUIManager.GetGameSetupView()->Draw();

    m_Window.display();
}

// ** EDIT TO IMPLEMENT MAPSETUP VIEW CLASS AND UI VIEW CLASS
void Game::DrawMapEditorMode()
{
    // Erases everything that was drawn last frame
	m_Window.clear();

    // Draw map
    m_GUIManager.GetMapSetupView()->Draw(m_GUIManager.GetMapSetup());
    // Draw Path lines
    m_GUIManager.GetMapSetupView()->DrawPathLine(m_GUIManager.GetMapSetup());

    // Draw HUD
    m_GUIManager.GetInfoUIView()->DrawHUD();
    m_GUIManager.GetInfoUIView()->DrawInstructionText();

    // Draw Template towers or tower info
    if(m_eCurrentEditState == FinishedPathingState)
    {
        m_TowerManager.GetTowerEntityView().Draw();
        m_GUIManager.GetInfoUIView()->DrawTowerInfo();
        m_MonsterManager.GetMonsterEntityView().Draw();
    }

    // Draw cross that indicate tower to be deleted
    m_GUIManager.GetInfoUIView()->DrawCrossShape();
    
    m_Window.display();
}

void Game::DrawPlayMode()
{
    m_Window.clear();

    // Draw Map
    m_GUIManager.GetMapSetupView()->Draw(m_GUIManager.GetMapSetup());
    #ifdef DEBUG
    // Draw path lines
    m_GUIManager.GetMapSetupView()->DrawPathLine(m_GUIManager.GetMapSetup());
    #endif

    // Draw HUD
    m_GUIManager.GetInfoUIView()->DrawHUD();

    // Draw template towers or tower info
    m_GUIManager.GetInfoUIView()->DrawTowerInfo(); 

    if(m_bIsRoundEnded){
        m_GUIManager.GetInfoUIView()->DrawInstructionText();
    }

    // Draw Towers
    m_TowerManager.GetTowerEntityView().Draw();

    // Draw cross that indicate tower to be deleted
    m_GUIManager.GetInfoUIView()->DrawCrossShape();

    // Draw Monsters
    m_MonsterManager.GetMonsterEntityView().Draw();

    m_MonsterManager.GetHealthBarView().Draw();

    // Draw Axes
    for (const Entity& bullet : m_aAxes)
    {
        m_Window.draw(bullet.m_Sprite);
    }

    for (const auto& towerPtr : m_TowerManager.GetActiveTowers()) {
        if(towerPtr->GetType() == TowerGeneratorData::TowerType::FlameThrower && towerPtr->GetIsFlameThrowerActive()){
            m_Window.draw(towerPtr->GetFlameSprite());
        }
    }

    if(m_eGameMode == GameOver){
        m_GUIManager.GetInfoUIView()->DrawGameOverText();
    }

    m_Window.display();
}
