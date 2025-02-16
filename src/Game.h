#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <vector>

#include "Tile.h"
#include "Monster.h"
#include "Monster_Generator.h"
#include "Tower.h"

using namespace sf;
using namespace std;

class Game
{
public:
    Game(int initialWindowWidth, int initialWindowHeight);
    ~Game();

    enum GameMode
    {
        InitialSetUp,
        PlayMode,
        MapEditorMode,
        Pause,
    };

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

    void Run();

private:
    void LoadInitialSetUpAssets();
    void LoadMapEditorAssets();
    void LoadPlayModeAssets();

    void HandleInput();
    void ChangeSizeInputText(Event& event, String& currentText);
    
    void UpdateInitialPrompt();
    void UpdateTiles();
    void UpdatePlay();
    void UpdateMonsters();
    void UpdateTowers();
    void UpdateAxes();
    void UpdateText();
    void UpdateUI();
    void Animate();

    void DrawInitialSetUp();
    void DrawMapEditorMode();
    void DrawPlayMode();

    bool isEdgeTile(sf::Vector2f tile);
    Vector2i tileCenterPosToIndex(Vector2f gridPos);

private:
    RenderWindow m_Window;
    GameMode m_eGameMode;
    GameMode m_ePrevGameMode;
    Time m_DeltaTime;
    float m_fTimeInPlayMode = 0.0f;

    Vector2i m_vWindowSize;
    Vector2i m_vGridSize;
    const int m_iTileSize;

    float m_fElapesdTimeInSeconds;

    // Initial SetUp 
    Font m_Font;
    Text m_IntroText;
    Text m_EnterSizeText;
    Text m_SizeLimitText;
    bool m_bIsSizeLimitTextShown = false;
    int m_iInputFontSize = 30;
    Text m_WidthSizeInput;
    Text m_HeightSizeInput;
    std::string m_UserInputWindowHeight = "";
    std::string m_UserInputWindowWidth = "";
    std::array<RectangleShape, 2> m_aUserInputBoxWindowSize;            // Array storing current input box assets
    ClickedInputBox m_eCurrentlyActiveInputBox;

    Texture m_SubmitButtonTexture;
    Texture m_SubmitButtonPressedTexture;
    std::vector<Sprite> m_aButtonBoxes;                                              // Array storing button box assets
    bool m_SubmitButtonClicked = false;

    // Map editor mode
    // Comment this later
    PathEditingState m_eCurrentEditState = EntryState;
    bool m_IsPathingMousePressed = false;

    Texture m_EntryTileTexture;
    Texture m_ExitTileTexture;
    Texture m_GrassTexture;
    Texture m_PathTexture;
    Texture m_TowerTexture;
    Texture m_BulletTexture;

    Entity m_AxeTemplate;

    std::vector<std::vector<Tile>> m_aTiles;
	std::vector<Entity> m_aAxes;
    
    
    std::array<RectangleShape, 8> m_ahighlights;

    std::vector<sf::Vector2f> m_aPath;                                                  // Stores the path tiles
    sf::Vector2f m_vEntryTile, m_vExitTile;                                             // Entry and exit tile positions
    sf::VertexArray m_sfPathLines;                                                      // SFML Vertex Array for drawing the path
    


    // Play mode 
    MonsterGenerator m_MonsterGenerator;
    bool m_bIsRoundEnded = false;
    bool m_bIsMonsterGeneratorUpdated = false;

    int m_iCurrentLevel;
    int m_iCurrentWealth;

    Texture m_MonsterTexture;
    Monster m_MonsterTemplate;

    std::vector<Monster> m_aMonstersQueue;
    std::vector<Monster*> m_aEliminatedMonstersQueue;

    void DebugPrintGameState() const {
        std::cout << "Game State:\n"
                  << "Mode: " << m_eGameMode << "\n"
                  << "Grid Size: " << m_vGridSize.x << "x" << m_vGridSize.y << "\n"
                  << "Tower Count: " << a_allActiveTowers.size() << "\n";
    }
    

    friend class MonsterGenerator;                  // make MonsterGenerator friend of Game so that MonsterGenerator has access to Game class's private members



    // UI Info
    Text m_scoreText;
    Text m_levelText;
    Text m_instructionText;
    Text m_warningText;
    Text m_modeText;
    String currentWarning = "";
    String currentMode = "";
    Clock warningShown;


    Vector2f scoreTextPosition;
    Vector2f levelTextPosition;
    Vector2f instructionTextPosition;
    Vector2f warningTextPosition;
    Vector2f modeTextPosition;
    vector<Tower> a_towerMenu;
    vector<Tower> a_allActiveTowers;
    vector<Tower> a_activeWoodTowers;
    vector<Tower> a_activeStoneTowers;


    Sprite* draggedSprite = nullptr;
    Texture m_towerTexture1;
    Texture m_towerTexture2;
    Tower tower1;
    Tower tower2;
    Tower draggedTower;


    // Animation related
    Clock animationDelay;
    int currentTowerFrame = 1;
    int currentEnemyFrame = 1;
    const float frameTime = 0.1f; // Time per frame in seconds
    Texture tower1TempTexture;
    Texture tower2TempTexture;
    Texture enemy1TempTexture;
    


};


#endif
