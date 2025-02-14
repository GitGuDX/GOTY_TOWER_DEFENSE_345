#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <vector>

#include "Tile.h"
#include "Monster.h"
#include "Monster_Generator.h"

using namespace sf;

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
    void UpdateMonsters();
    void UpdateText();

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
    Text m_EnterSizeText;
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

    std::vector<std::vector<Tile>> m_aTiles;
    
    std::array<RectangleShape, 8> m_ahighlights;

    std::vector<sf::Vector2f> m_aPath;                                                  // Stores the path tiles
    sf::Vector2f m_vEntryTile, m_vExitTile;                                             // Entry and exit tile positions
    sf::VertexArray m_sfPathLines;                                                      // SFML Vertex Array for drawing the path
    


    // Play mode 
    MonsterGenerator m_MonsterGenerator;

    int m_iCurrentLevel;

    Texture m_MonsterTexture;
    Monster m_MonsterTemplate;

    std::vector<Monster> m_aMonstersQueue;


    // UI Info
    Text m_Text;
    Text m_Text1;

    Vector2f scoreTextPosition;
    Vector2f levelTextPosition;
    
};


#endif
