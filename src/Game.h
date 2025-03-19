/**

@file Game.h

@brief Manages game states, rendering, and event handling.

The Game class initializes the game, manages user input, and updates/draws the game.
*/

#ifndef GAME_H
#define GAME_H

#include "Platform.h"

// GUI and Map
#include "Entities/Tile.h"
#include "GUI/GUIManager.h"

// Monster
#include "EntityManagers/MonsterManager.h"

// Tower
#include "EntityManagers/TowerManager.h"


#include "GameEventManager.h"
#include "ProjectileManager.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <vector>


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
    ~Game() = default; 

    /**
    @brief Enumeration for different game modes.
    */
    enum GameMode
    {
        InitialSetUp,   ///< Setup mode for entering grid size.
        PlayMode,       ///< Main gameplay mode.
        MapEditorMode,  ///< Map creation mode.
        Pause,          ///< Paused state.
        GameOver,       ///< Game over state.
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

    void InitializeMapEnditorMode();

    /** * @brief Loads assets for the play mode. */
    void LoadPlayModeAssets();

    void HandlePlayAgain();

    void HandleGameRestart();

    /** * @brief Handles user input. */
    void HandleInput();

    void EditMapSizeInputText(Event& event, std::string& currentText);

    void ResetEntities();

    /** * @brief Updates tile states. */
    void UpdateTiles();

    /** * @brief Updates game elements during play mode. */
    void UpdatePlay();

    /** * @brief Updates all monsters. */
    void UpdateMonsters();

    /** * @brief Updates tower mechanics. */
    void UpdateTowers();

    void UpdateAxes();

    void UpdateNextMonsterUI();

    /** * @brief Updates UI components. */
    void UpdateUI();

    /** * @brief Draws elements in initial setup mode. */
    void DrawInitialSetUp();

    /** * @brief Draws elements in map editor mode. */
    void DrawMapEditorMode();

    /** * @brief Draws elements in play mode. */
    void DrawPlayMode();

    void UpdateLevel()
    {
        InfoUI* infoUI = m_GUIManager.GetInfoUI();
        if (infoUI != nullptr)
        {
            infoUI->SetCurrentLevel(m_iCurrentLevel);
        }
        else
        {
            std::cerr << "InfoUI is nullptr\n";
        }
    }

    void IncreaseLevel()
    {
        m_iCurrentLevel++;
        UpdateLevel();
    }

    void UpdateWealth(int wealth)
    {
        m_iCurrentWealth += wealth;
        InfoUI* infoUI = m_GUIManager.GetInfoUI();
        if (infoUI != nullptr)
        {
            infoUI->SetCurrentWealth(m_iCurrentWealth);
        }
        else
        {
            std::cerr << "InfoUI is nullptr\n";
        }
    }

private:
    RenderWindow m_Window;
    Vector2i m_vInitialWindowSize;
    GameMode m_eGameMode;
    GameMode m_ePrevGameMode;
    
    // Time management
    Time m_DeltaTime;
    float m_fTimeInPlayMode = 0.0f;
    
    Clock warningShown;
    Clock placementOrUpgradeTimer;
    const float m_fFrameTime = 0.07f; // Time per frame in seconds

    // Defines window dimensions (pixels), map size (pixels) and tile size (pixels).
    Vector2i m_vWindowSize;
    Vector2i m_vMapSize;
    int m_iTileSize;

    // **** Not used. Assign it if used multiple times
    std::vector<sf::Vector2f> m_aPath;
    sf::VertexArray m_sfPathLines; 

    // GUI Driver class
    GUIManager m_GUIManager;

    // ** Tower
    TowerManager m_TowerManager;

    // ** MONSTER
    MonsterManager m_MonsterManager;

    ///// Flags
    // For path editing
    PathEditingState m_eCurrentEditState = EntryState;
    bool m_IsPathingMousePressed = false;
    // For cursor hovering
    bool m_isHovering = false;
    // For tower reference for tower upgrade
    TowerEntity* m_lastHoveredTower = nullptr;
    // For game mode transition
    bool m_bIsRoundEnded = false;
    bool m_bIsMonsterGeneratorUpdated = false;

    // **** Bullet assets. Implement observer pattern for bullet
    Texture m_RapidBulletTexture;
    Texture  m_SniperBulletTexture;
    Entity m_RapidBulletTemplate;
    Entity m_SniperBulletTemplate;
	std::vector<Entity> m_aAxes;

    // Player stats
    int m_iCurrentLevel;
    int m_iInitialWealth;
    int m_iCurrentWealth;

    // REMOVE?
    GameEventManager m_GameEventManager;   
    ProjectileManager m_ProjectileManager;

};


#endif
