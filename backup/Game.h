#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <vector>

#include "Grass_Tile.h"

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

    void Run();

private:
    void LoadInitialSetUpAssets();
    void LoadMapEditorAssets();

    void HandleInput();
    void ChangeSizeInputText(Event& event, String& currentText);
    
    void UpdateInitialPrompt();

    void DrawInitialSetUp();
    void DrawMapEditorMode();
    

private:
    RenderWindow m_Window;
    GameMode m_eGameMode;
    GameMode m_ePrevGameMode;

    Vector2i m_vGameWindowSize;
    const int m_iTileSize = 50;

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

    // Play mode
    Texture m_GrassTexture;

    std::vector<std::vector<Entity>> m_aTiles;
    Tile m_GrassTileTemplate;
    

};
