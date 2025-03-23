/**

@file Game.h

@brief Manages game states, rendering, and event handling.

The Game class initializes the game, manages user input, and updates/draws the game.
*/

#ifndef GAME_H
#define GAME_H

#include "Platform.h"

// GUI and Map
#include "GUI/GUIManager.h"

// Monster
#include "EntityManagers/MonsterManager.h"

// Tower
#include "EntityManagers/TowerManager.h"

#include <SFML/Graphics.hpp>
// ** Handle input class
#include <string>
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

    // // ** GAMESETUP VIEW
    // enum ClickedInputBox
    // {
    //     Width,
    //     Height,
    //     None
    // };

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

    // ** Load class
    void LoadPlayModeAssets();

    // ** Handle input class
    void HandleInput();
    void EditMapSizeInputText(Event& event, std::string& currentText);

    // Update class
    void HandlePlayAgain();
    void HandleGameRestart();
    void ResetEntities();
    void UpdateTiles();
    void UpdatePlay();
    void UpdateMonsters();
    void UpdateTowers();
    void UpdateAxes();
    void UpdateNextMonsterUI();
    void UpdateUI();

    // Draw class
    void DrawInitialSetUp();
    void DrawMapEditorMode();
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
    // ** Handle Input class
    Clock warningShown;
    Clock placementOrUpgradeTimer;
    // ** Update class
    const float m_fFrameTime = 0.07f; // Time per frame in seconds

    // Defines window dimensions (pixels), map size (pixels) and tile size (pixels).
    Vector2i m_vWindowSize;
    Vector2i m_vMapSize;
    int m_iTileSize;

    // **** Not used. Assign it if used multiple times
    std::vector<sf::Vector2f> m_aPath;
    sf::VertexArray m_sfPathLines; 

    // Managers
    GUIManager m_GUIManager;
    MonsterManager m_MonsterManager;
    TowerManager m_TowerManager;

    ///// Flags
    // ** handle Input class
    // For path editing
    PathEditingState m_eCurrentEditState = EntryState;
    bool m_IsPathingMousePressed = false;
    // For cursor hovering
    bool m_isHovering = false;
    // For tower reference for tower upgrade
    std::unique_ptr<TowerEntity>* m_lastHoveredTower = nullptr;
    // ** Game class
    // For game mode transition
    bool m_bIsRoundEnded = false;
    bool m_bIsMonsterGeneratorUpdated = false;

    // **** Bullet assets. Implement observer pattern for bullet/////////
    Texture m_RapidBulletTexture;
    Texture m_SniperBulletTexture;
    Texture m_FlameThrowerBulletTexture;
    Entity m_RapidBulletTemplate;
    Entity m_SniperBulletTemplate;
    Entity m_FlameThrowerBulletTemplate;
    Entity m_InvisibleFlameThrowerBulletTemplate;
	std::vector<Entity> m_aAxes;
    std::vector<Texture> m_aFlames;
    sf::Clock FlameThrowerClock;  // Use Clock to track time
    /////////////////////////////////////////////////////////////////////

    // Player stats
    int m_iCurrentLevel;
    int m_iInitialWealth;
    int m_iCurrentWealth;
};


#endif
