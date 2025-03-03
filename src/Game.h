/**

@file Game.h

@brief Manages game states, rendering, and event handling.

The Game class initializes the game, manages user input, and updates/draws the game.
*/

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <vector>

#include "Platform.h"
#include "GUI/Tile.h"
#include "Monster.h"
#include "Monster_Generator.h"
#include "Tower.h"
#include "GameEventManager.h"
#include "ProjectileManager.h"
#include "TowerView.h"
#include "MonsterView.h"
#include "GUI/GUIManager.h"

using namespace sf;
using namespace std;

/**

@class Game

@brief Main game management class.

* This class controls the flow of the game, updates the game state, and handles user input.
*/

class Game
{
public:
    /**
    @brief Constructs the game window.
    @param initialWindowWidth Initial width of the game window.
    @param initialWindowHeight Initial height of the game window.
    */
    Game(int initialWindowWidth, int initialWindowHeight);

    /** @brief Destructor for Game. */
    ~Game(); 

    /**
    @brief Enumeration for different game modes.
    */
    enum GameMode
    {
        InitialSetUp,   ///< Setup mode for entering grid size.
        PlayMode,       ///< Main gameplay mode.
        MapEditorMode,  ///< Map creation mode.
        Pause,          ///< Paused state.
    };

    // ** GAMESETUP VIEW
    enum ClickedInputBox
    {
        Width,
        Height,
        None
    };

    enum PathEditingState
    {
        EntryState,
        ExitState,
        PathState,
        FinishedPathingState
    };

    /** @brief Runs the game loop. */
    void Run(); 

private:
    /** * @brief Loads assets for the initial setup screen. */
    void LoadInitialSetUpAssets();

    /** * @brief Loads assets for the map editor mode.*/
    void LoadMapEditorAssets();

    /** * @brief Loads assets for the play mode. */
    void LoadPlayModeAssets();

    /** * @brief Loads assets for the UI screen. */
    void LoadUIAssets();

    /** * @brief Handles game over logic. */
    void HandleGameOver();

    /** * @brief Handles user input. */
    void HandleInput();

    void EditMapSizeInputText(Event& event, std::string& currentText);

    void ShowGameOverScreen();
    //void delayedTurnOffDragging();
    void LoadMonsterTextures();
    void LoadTowerTextures();
    //void PlayerPressedRestart();
    void ResetGame(bool);
    //void PlayerPressedMainMenu();
    //void SwitchToMainMenu();
    
    /** * @brief Updates game objects during initial setup. */
    void UpdateInitialPrompt();

    /** * @brief Updates tile states. */
    void UpdateTiles();

    /** * @brief Updates game elements during play mode. */
    void UpdatePlay();

    /** * @brief Updates all monsters. */
    void UpdateMonsters();

    /** * @brief Updates tower mechanics. */
    void UpdateTowers();


    void UpdateAxes();
    void UpdateText();

    /** * @brief Updates UI components. */
    void UpdateUI();
    //void Animate();

    /** * @brief Draws elements in initial setup mode. */
    void DrawInitialSetUp();

    /** * @brief Draws elements in map editor mode. */
    void DrawMapEditorMode();

    /** * @brief Draws elements in play mode. */
    void DrawPlayMode();

    void BlinkTiles(Tile::Type type);

    // bool ValidatePath();

    // bool isEdgeTile(sf::Vector2f tile);
    //Vector2i tileCenterPosToIndex(Vector2f gridPos);

private:
    RenderWindow m_Window;
    GameMode m_eGameMode;
    GameMode m_ePrevGameMode;
    Time m_DeltaTime;
    float m_fTimeInPlayMode = 0.0f;

    // GUI Driver class
    GUIManager m_GUIManager;

    // ** GUIMANAGER
    Vector2i m_vWindowSize;
    // ** MAP
    Vector2i m_vGridSize;
    const int m_iTileSize;

    float m_fElapesdTimeInSeconds;

    // ** GAMESETUP AND GAMESETUP VIEW
    // Initial SetUp 
    Font m_Font;
    Text m_IntroText;
    Text m_EnterSizeText;
    Text m_SizeLimitText;
    bool m_bIsSizeLimitTextShown = false;               // GAMESETUP VIEW
    int m_iInputFontSize = 30;                          // GAMESETUP VIEW
    Text m_WidthSizeInput;
    Text m_HeightSizeInput;
    std::string m_UserInputWindowHeight = "";           // COPIED TO GAMESETUP
    std::string m_UserInputWindowWidth = "";            // COPIED TO GAMESETUP
    std::array<RectangleShape, 2> m_aUserInputBoxWindowSize;            // GAMESETUP VIEW, Array storing current input box assets
    ClickedInputBox m_eCurrentlyActiveInputBox;                         // GAMESETUP VIEW
    Texture m_SubmitButtonTexture;                                      // GAMESETUP VIEW
    Texture m_SubmitButtonPressedTexture;                               // GAMESETUP VIEW
    std::vector<Sprite> m_aButtonBoxes;                                 // GAMESETUP VIEW, Array storing button box assets
    bool m_SubmitButtonClicked = false;                                 // GAMESETUP VIEW

    // Map editor mode
    // Comment this later
    PathEditingState m_eCurrentEditState = EntryState;
    bool m_IsPathingMousePressed = false;

    // ** MAP VIEW
    Texture m_EntryTileTexture;
    Texture m_ExitTileTexture;
    Texture m_GrassTexture;
    Texture m_PathTexture;


    Texture m_TowerTexture;
    Texture m_RapidBulletTexture;
    Texture  m_SniperBulletTexture;

    Entity m_RapidBulletTemplate;
    Entity m_SniperBulletTemplate;

    // ** MAP
    std::vector<std::vector<Tile>> m_aTiles;


	std::vector<Entity> m_aAxes;
    

    Text m_upgradeText;
    bool m_bShowUpgradeUI = false;
    Tower* m_pSelectedTower = nullptr;
    
    
    // * MAP
    std::array<RectangleShape, 8> m_ahighlights;


    std::vector<sf::Vector2f> m_aPath;
    std::vector<sf::Vector2f> m_aDeletedPath;                                                    // Stores the path tiles
    sf::Vector2f m_vEntryTile, m_vExitTile;                                             // Entry and exit tile positions
    sf::VertexArray m_sfPathLines;                                                      // SFML Vertex Array for drawing the path
    


    // Play mode 
    MonsterGenerator m_MonsterGenerator;
    bool m_bIsRoundEnded = false;
    bool m_gameOver = false;
    bool m_bIsMonsterGeneratorUpdated = false;

    int m_iCurrentLevel;
    int m_iCurrentWealth;

    std::vector<Monster> m_aMonstersQueue;
    std::vector<Monster*> m_aEliminatedMonstersQueue;
    bool justPlacedTower = false;
    sf::Clock placementOrUpgradeTimer;  // Timer to track recent tower placements
    GameEventManager m_GameEventManager;   
    ProjectileManager m_ProjectileManager;
    TowerView m_TowerView;
    MonsterView m_MonsterView;

    void DebugPrintGameState() const {
        std::cout << "Game State:\n"
                  << "Mode: " << m_eGameMode << "\n"
                  << "Grid Size: " << m_vGridSize.x << "x" << m_vGridSize.y << "\n"
                  << "Tower Count: " << a_allActiveTowers.size() << "\n";
    }
    

    friend class MonsterGenerator;                  // make MonsterGenerator friend of Game so that MonsterGenerator has access to Game class's private members



    // ** INFOUIVIEW
    Text m_scoreText;
    Text m_levelText;
    Text m_instructionText;
    Text m_towerDamage;
    Text m_towerCooldown;
    Text m_towerRange;
    Text m_towerSpeed;
    Text m_warningText;
    Text m_modeText;
    Text woodTowerPrice;
    Text stoneTowerPrice;
    Text m_gameOverText;
    Text m_nextRoundText;
    Vector2f scoreTextPosition;
    Vector2f levelTextPosition;
    Vector2f instructionTextPosition;
    Vector2f towerDamagePosition;
    Vector2f towerCooldownPosition;
    Vector2f towerRangePosition;
    Vector2f towerSpeedPosition;
    Vector2f warningTextPosition;
    Vector2f modeTextPosition;
    Vector2f woodTowerPricePosition;
    Vector2f stoneTowerPricePosition;
    Vector2f gameOverTextPosition;
    Vector2f nextRoundTextPosition;
    vector<Tower> a_towerMenu;
    sf::Vector2f xPosition; // Center the X at the hovered tower
    Sprite* draggedSprite = nullptr;
    Texture m_towerTexture1;        // Done
    Texture m_towerTexture2;        // Done
    // Tower tower1;
    // Tower tower2;
    
    // ** INFOUI
    String currentWarning = "";
    String currentMode = "";
    Clock warningShown;
    bool hoveringOnTower;
    float hoverTowerDamage;
    float hoverTowerCooldown;
    float hoverTowerRange;
    float hoverTowerSpeed;

    // Tower interaction. Leave it in the Game class for now
    vector<Tower> a_allActiveTowers;
    vector<Tower> a_activeWoodTowers;
    vector<Tower> a_activeStoneTowers;
    Tower draggedTower;
    bool isDraggingTower = false;
    sf::Clock dragTimer;
    bool isTimerRunning = false;



    // Animation related
    std::vector<sf::Texture> m_SkeletonTextures;
    std::vector<sf::Texture> m_ReaperTextures;
    std::vector<sf::Texture> m_GolemTextures;
    std::vector<sf::Texture> m_MinotaurTextures;
    std::vector<sf::Texture> m_OgreTextures;

    std::vector<Monster> m_aDeadMonsters;
    std::vector<sf::Texture> m_SkeletonDeathTextures;
    std::vector<sf::Texture> m_ReaperDeathTextures;
    std::vector<sf::Texture> m_GolemDeathTextures;
    std::vector<sf::Texture> m_MinotaurDeathTextures;
    std::vector<sf::Texture> m_OgreDeathTextures;

    std::vector<sf::Texture> m_RapidTowerTextures;
    std::vector<sf::Texture> m_SniperTowerTextures;

    Clock enemyAnimationDelay;
    Clock towerAnimationDelay;
    int currentTowerFrame = 1;
    int currentEnemyFrame = 0;
    const float frameTime = 0.07f; // Time per frame in seconds
    //Texture tower1TempTexture;
    //Texture tower2TempTexture;
    
    Monster m_MonsterTemplate;




};


#endif
