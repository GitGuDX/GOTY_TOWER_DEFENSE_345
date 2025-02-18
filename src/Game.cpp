/**

@file Game.cpp

@brief Implements game logic, handling updates and rendering.
*/

// NOTE: When path creation is completed, press enter on the keyboard to go to play mode

#define MAC               // FOR file path finding. use MAC for mac users and use WINDOW for window users
//#define DEBUG               // For debugging purposes

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include <limits>


#include "Math_Helpers.h"

using namespace sf;
using namespace std;

Game::Game(int initialWindowWidth, int initialWindowHeight)
    : m_Window(VideoMode(initialWindowWidth, initialWindowHeight), "Tower Defense 1")           // Initiliaze window screen
    , m_eGameMode(GameMode::InitialSetUp)                                                       // set current game mode to intial set up
    // Set previous game mode to initial set up. Later, this helps track when the game mode changes for the first time.
    , m_ePrevGameMode(GameMode::InitialSetUp)
    , m_vWindowSize(initialWindowWidth, initialWindowHeight)                                   // Set Window size
    , m_iTileSize(50)                                                                          // Set Tile size to 50px
    , m_eCurrentlyActiveInputBox(ClickedInputBox::None)
    , m_RapidBulletTemplate()
    // Monster generator initiliazed with base number of monsters and their increase rate per level
    , m_MonsterGenerator(3)
    , m_iCurrentLevel(1)
    #ifndef DEBUG
    , m_iCurrentWealth(500)
    #else
    , m_iCurrentWealth(10000)
    #endif
{
    m_vGridSize = Vector2i(initialWindowWidth/m_iTileSize, initialWindowWidth/m_iTileSize);      // Set Grid Size
    m_Window.setFramerateLimit(60);
    m_Window.setVerticalSyncEnabled(true);

    
    // Render Initial SetUp assets
    LoadInitialSetUpAssets();

}

Game::~Game()
{
}

void Game::Run()
{
    Clock clock;
    while (m_Window.isOpen())
    {
        m_DeltaTime = clock.restart();      // get elapsed time

        HandleInput();
        //m_Window.clear();
        // Depending on the game mode, update then draw
        switch (m_eGameMode)
        {
        case InitialSetUp:
        {
            UpdateInitialPrompt();
            DrawInitialSetUp();
            break;
        }
        case MapEditorMode:
        {   
            currentMode = "Mode: Map Editor Mode";
            // Load MapEditorMode assets only when MapEditorMode is initialized for the first time
            if (m_ePrevGameMode != MapEditorMode) {
                m_Window.create(VideoMode(m_vWindowSize.x + 300, m_vWindowSize.y), "New Game");
                LoadMapEditorAssets(); 
                LoadUIAssets();
                m_ePrevGameMode = MapEditorMode;
            }

            UpdateTiles();
            UpdateUI();
            
            DrawMapEditorMode();
            break;
        }
        case PlayMode:
        {
            currentMode = "Mode: Play Mode";
            // Load Play Mode assets once only when PlayMode is initialized for the first time then set previous mode to PlayMode so this condition
            // only triggers once
            if (m_ePrevGameMode != PlayMode)
            {
                LoadPlayModeAssets();
                LoadMonsterTextures();
                LoadTowerTextures();
                m_ePrevGameMode = PlayMode;
            }

            if(m_gameOver){
                HandleGameOver(); // Implement this function to show a game over screen, restart, etc.
            } else {
                // If round hasn't ended, game is still playing so keep updating
                if (!m_bIsRoundEnded)
                {
                    UpdatePlay();
                }
                // If the round ended, prepare for the next round.
                else
                {
                    if (!m_bIsMonsterGeneratorUpdated)
                    {
                        m_MonsterGenerator.updateNextRoundMonsterGenerator();
                        m_bIsMonsterGeneratorUpdated = true;
                        m_iCurrentLevel += 1;
                    }
                }
            }
            UpdateUI();
            DrawPlayMode();
            break;
        }
        case Pause:
        {
            currentMode = "Paused";
            break;
        }
        }
        
        //m_Window.display();                 //Placeholder, create new method
    }
}

void Game::LoadInitialSetUpAssets()
{
    #ifdef LINUX
    m_Font.loadFromFile("../src/Fonts/Kreon-Medium.ttf");  
    m_SubmitButtonTexture.loadFromFile("../src/Images/placeholder_play_button.png");                    // placeholder image. Change button image
    m_SubmitButtonPressedTexture.loadFromFile("../src/Images/placeholder_play_button_pressed.png");                    // placeholder image. Change button image
    #endif
    #ifdef MAC
    m_Font.loadFromFile("Fonts/Kreon-Medium.ttf");    
    m_SubmitButtonTexture.loadFromFile("Images/placeholder_play_button.png");                    // placeholder image. Change button image
    m_SubmitButtonPressedTexture.loadFromFile("Images/placeholder_play_button_pressed.png");                    // placeholder image. Change button image
    #endif
    #ifdef WINDOW
    // add for window
    #endif
    
    m_IntroText.setFont(m_Font);
    m_IntroText.setString("Welcome to Tower Defense Game!");
    m_IntroText.setCharacterSize(40);
    m_IntroText.setFillColor(Color::White);
    // Get text size
    float fIntroTextWidth = m_IntroText.getLocalBounds().width;
    float fIntroTextHeight = m_IntroText.getLocalBounds().height;
    // Reset the origin to the center of the text
    m_IntroText.setOrigin(Vector2f(fIntroTextWidth/2, fIntroTextHeight/2));
    // Set text to the center of the screen
    m_IntroText.setPosition(Vector2f(m_vWindowSize.x/2, m_vWindowSize.y/5));
    
    // Initialize "Enter Size" text
    m_EnterSizeText.setFont(m_Font);
    m_EnterSizeText.setString("Enter map size (width x height) in tiles:");
    m_EnterSizeText.setCharacterSize(25);
    //m_SizeLimitText.setScale(0.80, 0.80);
    // Get "Enter Size" text size
    float fEnterSizeTextWidth = m_EnterSizeText.getLocalBounds().width;
    float fEnterSizeTextHeight = m_EnterSizeText.getLocalBounds().height;
    // Reset the origin to the center of the text
    m_EnterSizeText.setOrigin(Vector2f(fEnterSizeTextWidth/2, fEnterSizeTextHeight/2));
    // Set "Enter Size" text to the center of the screen
    m_EnterSizeText.setPosition(Vector2f(m_vWindowSize.x/2, m_vWindowSize.y/3));
    m_EnterSizeText.setFillColor(Color::White);

    // Initialize "Size Limit" text
    m_SizeLimitText.setFont(m_Font);
    m_SizeLimitText.setString("Size must be between 10 and 20");
    m_SizeLimitText.setCharacterSize(20);
    // Get "Size Limit" text size
    float fSizeLimitTextWidth = m_SizeLimitText.getLocalBounds().width;
    float fSizeLimitTextHeight = m_SizeLimitText.getLocalBounds().height;
    // Reset the origin to the center of the text
    m_SizeLimitText.setOrigin(Vector2f(fSizeLimitTextWidth/2, fSizeLimitTextHeight/2));
    // Set "Size Limit" text to the center of the screen
    m_SizeLimitText.setPosition(Vector2f(m_vWindowSize.x/2, m_vWindowSize.y*4/5));
    m_SizeLimitText.setFillColor(Color::White);

    //Initialize width input box and store them in an array (index 0)
    RectangleShape InputBoxWidth(Vector2f(m_iInputFontSize * 1.5, m_iInputFontSize));
    InputBoxWidth.setOrigin(InputBoxWidth.getSize().x/2, InputBoxWidth.getSize().y/2);
    InputBoxWidth.setPosition(Vector2f(m_vWindowSize.x*3/8, m_vWindowSize.y/2));
    InputBoxWidth.setFillColor(Color::White);
    // InputBoxHeight.setOutlineColor(Color(128,128,128));
    // InputBoxHeight.setOutlineThickness(3.f);
    m_aUserInputBoxWindowSize[0] = InputBoxWidth;

    // Initialize window Width size input Text
    m_WidthSizeInput.setFont(m_Font);
    m_WidthSizeInput.setCharacterSize(m_iInputFontSize);
    m_WidthSizeInput.setString("10");                                                           // For test
    m_WidthSizeInput.setFillColor(Color::Red);
    float fWidthSizeInputHeight = m_WidthSizeInput.getLocalBounds().height;
    m_WidthSizeInput.setOrigin(0, fWidthSizeInputHeight);
    // Set position relative to the input box       
    m_WidthSizeInput.setPosition(InputBoxWidth.getPosition().x - InputBoxWidth.getSize().x/2 + 3, InputBoxWidth.getPosition().y + 1);  

    //Initialize height input box and store them in an array (index 1)
    RectangleShape InputBoxHeight(Vector2f(m_iInputFontSize * 1.5, m_iInputFontSize));
    InputBoxHeight.setOrigin(InputBoxHeight.getSize().x/2, InputBoxHeight.getSize().y/2);
    InputBoxHeight.setPosition(Vector2f(m_vWindowSize.x*5/8, m_vWindowSize.y/2));
    InputBoxHeight.setFillColor(Color::White);
    // InputBoxHeight.setOutlineColor(Color(128,128,128));
    // InputBoxHeight.setOutlineThickness(3.f);
    m_aUserInputBoxWindowSize[1] = InputBoxHeight;

    // Initialize window height size input Text
    m_HeightSizeInput.setFont(m_Font);
    m_HeightSizeInput.setCharacterSize(m_iInputFontSize);
    m_HeightSizeInput.setString("10");                                                                // For test
    m_HeightSizeInput.setFillColor(Color::Red);
    float fHeightSizeInputHeight = m_HeightSizeInput.getLocalBounds().height;
    m_HeightSizeInput.setOrigin(0, fHeightSizeInputHeight);
    // Set position relative to the input box
    m_HeightSizeInput.setPosition(InputBoxHeight.getPosition().x - InputBoxHeight.getSize().x/2 + 3, InputBoxHeight.getPosition().y + 1);

    // Initialize submit button and store it in the m_abuttonboxes array
    Sprite submitButton(m_SubmitButtonTexture);
    submitButton.setScale(Vector2f(5.f, 5.f));
    submitButton.setOrigin(m_SubmitButtonTexture.getSize().x/2, m_SubmitButtonTexture.getSize().y/2);
    submitButton.setPosition(Vector2f(m_vWindowSize.x/2,m_vWindowSize.y*2/3));
    m_aButtonBoxes.emplace_back(submitButton);
    //Initialise submit button text
    Sprite submitButtonPressed(m_SubmitButtonPressedTexture);
    submitButtonPressed.setScale(Vector2f(5.f, 5.f));
    submitButtonPressed.setOrigin(m_SubmitButtonPressedTexture.getSize().x/2, m_SubmitButtonTexture.getSize().y/2);
    submitButtonPressed.setPosition(Vector2f(m_vWindowSize.x/2,m_vWindowSize.y*2/3));
    m_aButtonBoxes.emplace_back(submitButtonPressed);
}


void Game::LoadMapEditorAssets()
{
    // Map editor mode assets
    #ifdef LINUX
    m_GrassTexture.loadFromFile("../src/Images/grass_Tile.png");
    m_PathTexture.loadFromFile("../src/Images/path_Tile.png");
    m_EntryTileTexture.loadFromFile("../src/Images/entry_Zone_Tile.png");
    m_ExitTileTexture.loadFromFile("../src/Images/exit_Zone_Tile.png");
    #endif
    #ifdef MAC

    m_GrassTexture.loadFromFile("Images/grass_Tile.png");
    m_PathTexture.loadFromFile("Images/path_Tile.png");
    m_EntryTileTexture.loadFromFile("Images/entry_Zone_Tile.png");
    m_ExitTileTexture.loadFromFile("Images/exit_Zone_Tile.png");
    #endif
    #ifdef WINDOW
    // add for window
    #endif






    // Create grass tiles and store them in a 2D array. The position of the item in the array correspond to the position of the tile in the game
    // (e.g. tile at [0][0] is displayed at the top left corner) 
    m_aTiles.clear();
    for (int i = 0; i < m_vGridSize.y; ++i)
    {
        std::vector<Tile> row;
        for (int j = 0; j < m_vGridSize.x; ++j)
        {
            Tile tempGrassTile;
            tempGrassTile.SetTexture(m_GrassTexture);
            tempGrassTile.SetScale(Vector2f(1.f, 1.f));
            tempGrassTile.SetTextureRect(sf::IntRect(0,0,50,50));
            tempGrassTile.SetOrigin(Vector2f(25, 25));
            tempGrassTile.SetPosition(Vector2f(j * m_iTileSize + m_iTileSize / 2, i * m_iTileSize + m_iTileSize / 2));
            tempGrassTile.setType(Tile::Type::Grass);                               // Define its tile type
            row.emplace_back(tempGrassTile);
        }
        m_aTiles.emplace_back(row);
    }


    // Load entry and exit zone tiles assets
    // Loop to create 8 highlight rectangles
    for (int i = 0; i < 8; ++i)
    {
        RectangleShape highlight;
        // Determine the size of the highlight based on whether 'i' is even or odd
        // If 'i' is even, make the highlight a wide horizontal rectangle
        // If 'i' is odd, make the highlight a tall vertical rectangle
        if (i % 2 == 0)
        {             
            highlight.setSize(Vector2f(m_vGridSize.x * m_iTileSize, m_iTileSize));
        }
        else
        {
            highlight.setSize(Vector2f(m_iTileSize, m_vGridSize.y * m_iTileSize));
        }
        // Assign color based on index
        // First 4 highlights are green and Last 4 highlights are red
        if (i < 4)
        {
            highlight.setFillColor(Color::Green);
        }
        else
        {
            highlight.setFillColor(Color::Red);
        }
        // If 'i' is 2 or 6, place it at the bottom-left corner
        if (i == 2 || i == 6)
        {
            highlight.setPosition(Vector2f(0.f, m_vGridSize.y * m_iTileSize - m_iTileSize));
        }
        // If 'i' is 3 or 7, place it at the top-right corner
        else if (i == 3 || i == 7)
        {
            highlight.setPosition(Vector2f(m_vGridSize.x * m_iTileSize - m_iTileSize, 0.f));
        }
        // Default position is the top-left corner (0,0)
        else 
        {
            highlight.setPosition(Vector2f(0.f, 0.f));
        }
        // Store the highlight in the array at index 'i'
        m_ahighlights[i] = highlight;
    }

    m_sfPathLines.setPrimitiveType(sf::LineStrip); // Set the drawing type to a continuous line
}

void Game::LoadTowerTextures() {
    for (int i = 1; i <= 6; ++i) {
        sf::Texture texture;
        #ifdef MAC
        if (!texture.loadFromFile("Images/Tower1_Frame_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Skeleton frame " << i << std::endl;
        }
        m_RapidTowerTextures.push_back(texture);

        if (!texture.loadFromFile("Images/Tower2_Frame_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Skeleton frame " << i << std::endl;
        }
        m_SniperTowerTextures.push_back(texture);
       #endif
    }
}

void Game::LoadMonsterTextures() {
    for (int i = 0; i <= 11; ++i) {
        sf::Texture texture;
        #ifdef LINUX
        if (!texture.loadFromFile("../src/Images/Running_Skeleton/0_Skeleton_Crusader_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Skeleton frame " << i << std::endl;
        }
        m_SkeletonTextures.push_back(texture);

        if (!texture.loadFromFile("../src/Images/Running_Reaper/0_Reaper_Man_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Reaper frame " << i << std::endl;
        }
        m_ReaperTextures.push_back(texture);

        if (!texture.loadFromFile("../src/Images/Running_Golem/0_Golem_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Golem frame " << i << std::endl;
        }
        m_GolemTextures.push_back(texture);

        if (!texture.loadFromFile("../src/Images/Running_Minotaur/0_Minotaur_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Minotaur frame " << i << std::endl;
        }
        m_MinotaurTextures.push_back(texture);

        if (!texture.loadFromFile("../src/Images/Running_Ogre/0_Ogre_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Ogre frame " << i << std::endl;
        }
        m_OgreTextures.push_back(texture);
        #endif
        #ifdef MAC
        if (!texture.loadFromFile("Images/Running_Skeleton/0_Skeleton_Crusader_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Skeleton frame " << i << std::endl;
        }
        m_SkeletonTextures.push_back(texture);

        if (!texture.loadFromFile("Images/Running_Reaper/0_Reaper_Man_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Reaper frame " << i << std::endl;
        }
        m_ReaperTextures.push_back(texture);

        if (!texture.loadFromFile("Images/Running_Golem/0_Golem_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Golem frame " << i << std::endl;
        }
        m_GolemTextures.push_back(texture);

        if (!texture.loadFromFile("Images/Running_Minotaur/0_Minotaur_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Minotaur frame " << i << std::endl;
        }
        m_MinotaurTextures.push_back(texture);

        if (!texture.loadFromFile("Images/Running_Ogre/0_Ogre_Running_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load Ogre frame " << i << std::endl;
        }
        m_OgreTextures.push_back(texture);
        #endif
        #ifdef WINDOW
        // add for window
        #endif
    }
}

void Game::LoadPlayModeAssets()
{
    // Load bullet texture

    m_RapidBulletTexture.loadFromFile("Images/Rapid_Bullet.png");
    m_SniperBulletTexture.loadFromFile("Images/Sniper_Bullet.png");


    // Reset entry and exit tile texture back to grass texture
    sf::Vector2i entryTileIndex = tileCenterPosToIndex(m_vEntryTile);
    m_aTiles[entryTileIndex.y][entryTileIndex.x].m_Sprite.setTexture(m_PathTexture);
    sf::Vector2i exitTileIndex = tileCenterPosToIndex(m_vExitTile);
    m_aTiles[exitTileIndex.y][exitTileIndex.x].m_Sprite.setTexture(m_PathTexture);

    m_TowerTexture.setSmooth(true);

	m_RapidBulletTemplate.SetTexture(m_RapidBulletTexture);
	m_RapidBulletTemplate.SetScale(sf::Vector2f(0.05, 0.05));
	m_RapidBulletTemplate.SetOrigin(sf::Vector2f(8, 8));

	m_SniperBulletTemplate.SetTexture(m_SniperBulletTexture);
	m_SniperBulletTemplate.SetScale(sf::Vector2f(0.05, 0.05));
	m_SniperBulletTemplate.SetOrigin(sf::Vector2f(8, 8));


}

void Game::LoadUIAssets()
{
    scoreTextPosition = Vector2f(m_vWindowSize.x + 150, m_vWindowSize.y/10 + 10);
    levelTextPosition = Vector2f(m_vWindowSize.x + 150, m_vWindowSize.y/10 + 35);
    instructionTextPosition = Vector2f(m_vWindowSize.x + 150, m_vWindowSize.y/10 + 135);
    warningTextPosition = Vector2f(m_vWindowSize.x + 150, m_vWindowSize.y - 30);
    modeTextPosition = Vector2f(m_vWindowSize.x + 150, m_vWindowSize.y/10 + 65);
    woodTowerPricePosition = Vector2f(m_vWindowSize.x + 130, m_vWindowSize.y/3 + 125);
    stoneTowerPricePosition = Vector2f(m_vWindowSize.x + 235, m_vWindowSize.y/3 + 125);
    gameOverTextPosition = Vector2f(m_vWindowSize.x/2, m_vWindowSize.y/2);
    towerDamagePosition = Vector2f(m_vWindowSize.x + 150, m_vWindowSize.y/10 + 170);
    towerCooldownPosition = Vector2f(m_vWindowSize.x + 150, m_vWindowSize.y/10 + 200);
    towerRangePosition = Vector2f(m_vWindowSize.x + 150, m_vWindowSize.y/10 + 230);
    towerSpeedPosition = Vector2f(m_vWindowSize.x + 150, m_vWindowSize.y/10 + 260);
    nextRoundTextPosition = Vector2f(m_vWindowSize.x + 230, m_vWindowSize.y/10 + 110); //Fix this because it should be the same values as instruciton but its not

    // Score text 
    m_scoreText.setFont(m_Font);               // Set font
    m_scoreText.setString("Score: " + std::to_string(m_iCurrentWealth));   // Set text
    FloatRect scoreTextBounds = m_scoreText.getLocalBounds();
    m_scoreText.setOrigin(scoreTextBounds.width / 2, scoreTextBounds.height / 2);
    m_scoreText.setCharacterSize(25);        // Set size
    m_scoreText.setFillColor(Color::Red);     // Set color
    m_scoreText.setPosition(scoreTextPosition);       // Set position

    // Level text 
    m_levelText.setFont(m_Font);               // Set font
    m_levelText.setString("Level: " + std::to_string(m_iCurrentLevel));   // Set text
    FloatRect levelTextBounds = m_levelText.getLocalBounds();
    m_levelText.setOrigin(levelTextBounds.width / 2, levelTextBounds.height / 2);
    m_levelText.setCharacterSize(25);        // Set size
    m_levelText.setFillColor(Color::Red);     // Set color
    m_levelText.setPosition(levelTextPosition);       // Set position

    // Warning text 
    m_warningText.setFont(m_Font);               // Set font
    m_warningText.setString(currentWarning);   // Set text
    FloatRect warningTextBounds = m_warningText.getLocalBounds();
    m_warningText.setOrigin(warningTextBounds.width / 2, warningTextBounds.height / 2);
    m_warningText.setCharacterSize(15);        // Set size
    m_warningText.setPosition(warningTextPosition);       // Set position

    // Wood tower price
    woodTowerPrice.setFont(m_Font);               // Set font
    woodTowerPrice.setString("Cost: 200");   // Set text
    FloatRect woodTowerPriceBounds = woodTowerPrice.getLocalBounds();
    woodTowerPrice.setOrigin(woodTowerPriceBounds.width / 2, woodTowerPriceBounds.height / 2);
    woodTowerPrice.setCharacterSize(12);        // Set size
    woodTowerPrice.setPosition(woodTowerPricePosition);       // Set position

    // Stone tower price
    stoneTowerPrice.setFont(m_Font);               // Set font
    stoneTowerPrice.setString("Cost: 300");   // Set text
    FloatRect stoneTowerPriceBounds = stoneTowerPrice.getLocalBounds();
    stoneTowerPrice.setOrigin(stoneTowerPriceBounds.width / 2, stoneTowerPriceBounds.height / 2);
    stoneTowerPrice.setCharacterSize(12);        // Set size
    stoneTowerPrice.setPosition(stoneTowerPricePosition);       // Set position

    // Current mode text 
    m_modeText.setFont(m_Font);               // Set font
    m_modeText.setString(currentMode);   // Set text
    FloatRect modeTextBounds = m_modeText.getLocalBounds();
    m_modeText.setOrigin(modeTextBounds.width / 2, modeTextBounds.height / 2);
    m_modeText.setCharacterSize(18);        // Set size
    m_modeText.setFillColor(Color::Red);     // Set color
    m_modeText.setPosition(modeTextPosition);       // Set position

    // Game Over text 
    m_gameOverText.setFont(m_Font);               // Set font
    m_gameOverText.setString("Game Over!");   // Set text
    FloatRect gameOverTextBounds = m_gameOverText.getLocalBounds();
    m_gameOverText.setOrigin(gameOverTextBounds.width/2, gameOverTextBounds.height/2);
    m_gameOverText.setCharacterSize(55);        // Set size
    m_gameOverText.setFillColor(Color::Red);     // Set color
    m_gameOverText.setPosition(gameOverTextPosition);       // Set position

    // Next Round text 
    m_nextRoundText.setFont(m_Font);               // Set font
    m_nextRoundText.setString("Press Enter for next round");   // Set text
    FloatRect nextRoundTextBounds = m_nextRoundText.getLocalBounds();
    m_nextRoundText.setOrigin(nextRoundTextBounds.width/2, nextRoundTextBounds.height/2);
    m_nextRoundText.setCharacterSize(15);        // Set size
    m_nextRoundText.setFillColor(Color::Green);     // Set color
    m_nextRoundText.setPosition(nextRoundTextPosition);       // Set position

    // instruction text 
    m_instructionText.setFont(m_Font);               // Set font
    m_instructionText.setCharacterSize(20);        // Set size
    m_instructionText.setPosition(instructionTextPosition);       // Set position

    // Damage text 
    m_towerDamage.setFont(m_Font);               // Set font
    m_towerDamage.setCharacterSize(15);        // Set size
    m_towerDamage.setPosition(towerDamagePosition);       // Set position

    // Cooldown text 
    m_towerCooldown.setFont(m_Font);               // Set font
    m_towerCooldown.setCharacterSize(15);        // Set size
    m_towerCooldown.setPosition(towerCooldownPosition);       // Set position

    // Range text 
    m_towerRange.setFont(m_Font);               // Set font
    m_towerRange.setCharacterSize(15);        // Set size
    m_towerRange.setPosition(towerRangePosition);       // Set position

    // Speed text 
    m_towerSpeed.setFont(m_Font);               // Set font
    m_towerSpeed.setCharacterSize(15);        // Set size
    m_towerSpeed.setPosition(towerSpeedPosition);       // Set position

    //Loading tower selection
    Tower tower1;
    #ifdef LINUX
    m_towerTexture1.loadFromFile("../src/Images/Tower1_Frame_1.png");
    m_towerTexture2.loadFromFile("../src/Images/Tower2_Frame_1.png");
    #endif
    #ifdef MAC
    m_towerTexture1.loadFromFile("Images/Tower1_Frame_1.png");
    m_towerTexture2.loadFromFile("Images/Tower2_Frame_1.png");
    #endif
    #ifdef WINDOW
    // Add for window
    #endif
    //MENU ASSETS
    tower1.SetTexture(m_towerTexture1);
    tower1.SetScale(Vector2f(0.7f, 0.7f));
    FloatRect tower1Bounds = tower1.GetSprite().getLocalBounds(); // Assuming getSprite() returns an sf::Sprite reference
    tower1.SetOrigin(Vector2f(tower1Bounds.width / 2, tower1Bounds.height / 2));
    tower1.SetTextureRect(sf::IntRect(0,0,70,100));
    tower1.SetPosition(Vector2f(m_vWindowSize.x + 100, m_vWindowSize.y/3 + 75));
    a_towerMenu.push_back(tower1);

    Tower tower2;
    tower2.SetTexture(m_towerTexture2);
    FloatRect tower2Bounds = tower2.GetSprite().getLocalBounds(); // Assuming getSprite() returns an sf::Sprite reference
    tower2.SetOrigin(Vector2f(tower2Bounds.width / 2, tower2Bounds.height / 2));
    tower2.SetScale(Vector2f(0.7f, 0.7f));
    tower2.SetTextureRect(sf::IntRect(0,0,70,100));
    tower2.SetPosition(Vector2f(m_vWindowSize.x + 200, m_vWindowSize.y/3 + 75));
    a_towerMenu.push_back(tower2);
}

void Game::ShowGameOverScreen()
{   
    m_Window.draw(m_gameOverText);
}

void Game::HandleGameOver()
{
    // Stop game logic
    m_aMonstersQueue.clear(); // Remove all monsters
    m_bIsRoundEnded = true; // Ensure no new rounds start
    m_bIsMonsterGeneratorUpdated = false; // Reset for next playthrough

    // Display Game Over message (implement this in your UI system)
    ShowGameOverScreen();
    /*
    // Wait for user input to restart or return to main menu
    if (PlayerPressedRestart()) // Implement input check
    {
        ResetGame();
    }
    else if (PlayerPressedMainMenu())
    {
        SwitchToMainMenu();
    }
    */
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
        // Handle inputs for initial SetUp //
        if (m_eGameMode == InitialSetUp)
        {
            Vector2i mousePosition = Mouse::getPosition(m_Window);                                  // Get mouse position by pixel
            Vector2f translatedPosition = m_Window.mapPixelToCoords(mousePosition);                 // Translate mouse position to game coordinate
            if (event.type == Event::MouseButtonPressed) {
                // Input box conditions
                if (m_aUserInputBoxWindowSize[0].getGlobalBounds().contains(translatedPosition))        // Check if mouse position is within the width input box
                {
                    m_eCurrentlyActiveInputBox = ClickedInputBox::Width;
                } 
                else if (m_aUserInputBoxWindowSize[1].getGlobalBounds().contains(translatedPosition))   // Check if mouse position is within the height input box
                {
                    m_eCurrentlyActiveInputBox = ClickedInputBox::Height;
                }
                else                                                                                    // If clicked anywhere outside the input box
                {
                    m_eCurrentlyActiveInputBox = ClickedInputBox::None;                                 
                }

                // When submit button is clicked
                if (m_aButtonBoxes[0].getGlobalBounds().contains(translatedPosition))
                {
                    m_SubmitButtonClicked = true;   
                }
            }
            if (event.type == Event::MouseButtonReleased)
            {
                // When submit button click is released, resize window with given inputs, switch game mode, and load map editor assets
                if (m_aButtonBoxes[1].getGlobalBounds().contains(translatedPosition))
                {
                    m_SubmitButtonClicked = false;
                    // convert the user input string to unsigned int and reassign the new grid size
                    m_vGridSize.x = std::stoi(m_WidthSizeInput.getString().toAnsiString());                // converting sf::String -> std::string -> unsigned int
                    m_vGridSize.y = std::stoi(m_HeightSizeInput.getString().toAnsiString());
                    // apply input limit from 10 to 25
                    if (m_vGridSize.x >= 10 && m_vGridSize.x <= 20 && m_vGridSize.y >= 10 && m_vGridSize.y <= 20)
                    {
                        // Reset window size
                        m_vWindowSize = Vector2i(m_vGridSize.x*m_iTileSize, m_vGridSize.y*m_iTileSize);
                        m_eGameMode = GameMode::MapEditorMode;
                    }
                    else
                    {
                        m_bIsSizeLimitTextShown = true;
                    }
                }
            }

            if (event.type == Event::TextEntered)
            {
                // Depending on which box is clicked, update the corresponding text
                switch (m_eCurrentlyActiveInputBox)
                {
                case ClickedInputBox::Width:
                {
                    String currentText = m_WidthSizeInput.getString();
                    ChangeSizeInputText(event, currentText);
                    m_WidthSizeInput.setString(currentText);
                    break;
                }
                case ClickedInputBox::Height:
                {
                    String currentText = m_HeightSizeInput.getString();
                    ChangeSizeInputText(event, currentText);
                    m_HeightSizeInput.setString(currentText);
                }
                case ClickedInputBox::None:
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
                if (event.mouseButton.button == sf::Mouse::Left && clickedPos.x <= m_vWindowSize.x && clickedPos.y <= m_vWindowSize.y)
                {
                    // If EntryState, check if the tile clicked is from the edge tiles then save the clicked tile as the entry tile then append is to the arrays
                    if (m_eCurrentEditState == EntryState)
                    {
                        if (isEdgeTile(gridPos))
                        {
                            m_vEntryTile = gridPos;
                            m_eCurrentEditState = ExitState;
                            m_aPath.clear();
                            m_aPath.push_back(m_vEntryTile);
                            m_sfPathLines.clear();
                            m_sfPathLines.append(sf::Vertex(m_vEntryTile, sf::Color::Green));
                        }
                    }
                    // if ExitState, check if the tile clicked is from the edge tiles then sanve the clicked tile as the exit tile
                    // the exit tile will be appended to the arrays later when the entry tile and the exit tiles are linked together with path tile
                    else if (m_eCurrentEditState == ExitState) 
                    {
                        if (isEdgeTile(gridPos))
                        {
                            m_vExitTile = gridPos;
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
                
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && m_eCurrentEditState == FinishedPathingState) {
                    sf::Vector2f mousePos = m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window));

                    for (auto& tile : a_towerMenu) {
                        if (tile.GetSpriteNonConst().getGlobalBounds().contains(mousePos)) {
                            //sf::Sprite& clickedSprite = tile.GetSpriteNonConst(); // Get the sprite
                            break; // Stop after finding the first tile
                        }
                    }
                }

                

                //PATHING RELATED
                if (m_IsPathingMousePressed && m_eCurrentEditState == PathState)
                {
                    sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
                    sf::Vector2f gridPos = MathHelpers::getNearestTileCenterPosition(mousePos, m_iTileSize);      // Snap the mouse position to the grid
                    if (!m_aPath.empty() && MathHelpers::isAdjacent(m_aPath.back(), gridPos, m_iTileSize))
                    {
                        // When the path tile overlaps with the exit tile, we reached the end of pathing. Append exit tile. Ensure we don't move beyond the exit tile
                        if (gridPos == m_vExitTile)
                        {
                            m_aPath.push_back(m_vExitTile);
                            m_sfPathLines.append(sf::Vertex(m_vExitTile, sf::Color::Red));
                            m_eCurrentEditState = FinishedPathingState;
                        }
                        // Prevent backtracking
                        else if (m_aPath.size() > 1 && m_aPath[m_aPath.size() - 2] == gridPos)
                        {
                            // Append the path tile to the deleted path array
                            m_aDeletedPath.push_back(m_aPath.back());
                            
                            // Remove the path tile from the path array
                            m_aPath.pop_back();
                            // Remove the path tile from the path lines array
                            m_sfPathLines.resize(m_aPath.size());
                        }
                        // Skeleton pathing. first check if the current tile is not the previous tile then append path tile
                        else if (m_aPath.back().x != gridPos.x || m_aPath.back().y != gridPos.y)
                        {
                            m_aPath.push_back(gridPos);
                            m_sfPathLines.append(sf::Vertex(gridPos, sf::Color::White));
                        }
                        std::cout << "m_aPath size: " << m_aPath.size() << std::endl;

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
                    if (ValidatePath())
                    {
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

        //Removes built towers on click
        if(event.mouseButton.button == sf::Mouse::Left && !isDraggingTower){
            if (justPlacedTower && placementOrUpgradeTimer.getElapsedTime().asMilliseconds() < 200) {
                return;  // Ignore clicks right after placement
            }
            justPlacedTower = false;  // Reset flag after some time
            sf::Vector2f newPos = m_Window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            Vector2f snapGrid = MathHelpers::getNearestTileCenterPosition(newPos, 50);

            for (auto it = a_allActiveTowers.begin(); it != a_allActiveTowers.end(); ++it) {
                if (it->GetPosition().x == snapGrid.x && it->GetPosition().y == snapGrid.y) {
                    currentWarning = "Successfully removed a tower\n";
                    m_warningText.setFillColor(Color::Green);
                    warningShown.restart();
                    m_iCurrentWealth += it->GetCost()/2;

                    //  Remove the clicked tower
                    if (std::find(a_activeWoodTowers.begin(), a_activeWoodTowers.end(), *it) != a_activeWoodTowers.end()) {
                        // Tower is in wood towers list, remove it
                        a_activeWoodTowers.erase(std::remove(a_activeWoodTowers.begin(), a_activeWoodTowers.end(), *it), a_activeWoodTowers.end());
                    } else if (std::find(a_activeStoneTowers.begin(), a_activeStoneTowers.end(), *it) != a_activeStoneTowers.end()) {
                        // Tower is in stone towers list, remove it
                        a_activeStoneTowers.erase(std::remove(a_activeStoneTowers.begin(), a_activeStoneTowers.end(), *it), a_activeStoneTowers.end());
                    }

                    // Remove the tower from all active towers
                    a_allActiveTowers.erase(it);
                    break;  // Stop looping after removing one tower
                }
            }
        }


        // TOWER DRAGGING RELATED
        if (m_eGameMode == PlayMode || m_eGameMode == MapEditorMode){
            // Handle mouse click (start dragging)
            sf::Vector2f mousePos = m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window));
            if (Mouse::isButtonPressed(Mouse::Left) && m_eCurrentEditState == FinishedPathingState) {
                //for (auto& tower : a_towerMenu) 
                for (size_t i = 0; i < a_towerMenu.size(); ++i)
                {
                    Tower& tower = a_towerMenu[i];
                    sf::Vector2f mousePos = m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window));
                    if (tower.GetSpriteNonConst().getGlobalBounds().contains(mousePos) && draggedSprite == nullptr) 
                    {
                        draggedSprite = (tower.GetSpriteNonConst().getTexture() != nullptr) ? &tower.GetSpriteNonConst() : nullptr;
            
                        if (draggedSprite) { // Only proceed if draggedSprite is valid
                            draggedTower.SetTexture(*draggedSprite->getTexture());
                            draggedTower.SetScale(Vector2f(0.7f, 0.7f));
                            draggedTower.SetPosition(tower.GetPosition());
            
                            FloatRect draggedTowerBounds = draggedTower.GetSprite().getLocalBounds();
                            draggedTower.SetOrigin(Vector2f(draggedTowerBounds.width / 2, draggedTowerBounds.height / 2 + 10));
                            draggedTower.SetTextureRect(sf::IntRect(0, 0, 70, 100));
                            isDraggingTower = true;
                        }
                        break;
                    }
                }
            }

            // Handle dragging when the mouse moves
            //if (event.type == sf::Event::MouseMoved && draggedSprite != nullptr) 
            if (std::abs(mousePos.x - draggedTower.GetPosition().x) > 0.01f ||            // Prevent unnecessary updates when movement is too small.
                std::abs(mousePos.y - draggedTower.GetPosition().y) > 0.01f)
            {
                //sf::Vector2f newPos = m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window)); //+ offset;
                draggedTower.SetPosition(mousePos);       // Updates the dragged towers position while dragging
            }

            // Handle mouse release (stop dragging)
            if (event.type == sf::Event::MouseButtonReleased && m_eCurrentEditState == FinishedPathingState) {
                Vector2i mousePos = sf::Mouse::getPosition(m_Window);
                Vector2f mouseWorldPos = m_Window.mapPixelToCoords(mousePos);
                Vector2f snapGrid = MathHelpers::getNearestTileCenterPosition(mouseWorldPos, 50);
                std::cout << "Mouse released\n";
                // Check for existing towers at the snapGrid position
                for (auto& tower : a_allActiveTowers) {
                    if (tower.GetPosition().x == snapGrid.x && tower.GetPosition().y == snapGrid.y && draggedSprite != nullptr) {
                        currentWarning = "Warning: There's already a tower here...\n";
                        m_warningText.setFillColor(Color::Red);
                        warningShown.restart();
                        draggedSprite = nullptr;
                        break;
                    }
                }

                for (auto& tilePos : m_aPath) {
                    if (tilePos.x == snapGrid.x && tilePos.y == snapGrid.y && draggedSprite != nullptr) {
                        currentWarning = "Warning: Cannot place on path...\n";
                        m_warningText.setFillColor(Color::Red);
                        warningShown.restart();
                        draggedSprite = nullptr;
                        break;
                    }
                }
                std::cout << "For loop done\n";
                if(mouseWorldPos.x <= m_vWindowSize.x && mouseWorldPos.y <= m_vWindowSize.y && draggedSprite != nullptr){
                    std::cout << "Mouse released inside window\n";
                    draggedTower.SetPosition(snapGrid);
                    std::cout << "Dragged tower position set\n";
                    std::cout << "Before checking texture\n";
                    std::cout << "draggedSprite address: " << draggedSprite << std::endl;
                    std::cout << "Texture address: " << draggedSprite->getTexture() << std::endl;
                    std::cout << (draggedSprite->getTexture() == nullptr) << std::endl;
                    std::cout << "Im here\n";
                    //if (draggedSprite != nullptr && draggedSprite->getTexture() == &m_towerTexture1)
                    if (draggedSprite->getTexture() == &m_towerTexture1) {             // Avoid accessing a null pointer
                        std::cout << "start at tower 1\n";
                        draggedTower.SetType(TowerType::Rapid);
                        std::cout << "tower 1 - 2\n";
                        if(m_iCurrentWealth < 200){
                            std::cout << "tower 1 - 2a\n";
                            currentWarning = "Warning: Cannot afford this tower...\n";
                            m_warningText.setFillColor(Color::Red);
                            warningShown.restart();
                            draggedSprite = nullptr;
                            isDraggingTower = false;
                            break;
                        } else{
                            std::cout << "tower 1 - 3\n";
                            m_iCurrentWealth -= 200;
                            a_activeWoodTowers.push_back(draggedTower);
                            a_allActiveTowers.push_back(draggedTower);
                            justPlacedTower = true;
                            placementOrUpgradeTimer.restart();
                            std::cout << "tower 1 - 4\n";
                        }
                        std::cout << "break at tower 1\n";
                    }
                    else if(draggedSprite->getTexture() == &m_towerTexture2)
                    {
                        
                        std::cout << "start at tower 2\n";
                        draggedTower.SetType(TowerType::Sniper);
                        std::cout << "tower 2 - 2\n";
                        if(m_iCurrentWealth < 300){
                            std::cout << "tower 2 - 2a\n";
                            currentWarning = "Warning: Cannot afford this tower...\n";
                            m_warningText.setFillColor(Color::Red);
                            warningShown.restart();
                            draggedSprite = nullptr;
                            break;
                        } else{
                            std::cout << "tower 2 - 3\n";
                            m_iCurrentWealth -= 300;
                            a_activeStoneTowers.push_back(draggedTower);
                            a_allActiveTowers.push_back(draggedTower);
                            justPlacedTower = true;
                            placementOrUpgradeTimer.restart();
                            std::cout << "tower 2 - 4\n";
                        }
                        std::cout << "break at tower 2\n";
                    }
                    else 
                    {
                        std::cerr << "Error: Unknown tower texture\n"; // Added error handling for unknown texture
                    }
                    std::cout << "break at end\n";
                    draggedSprite = nullptr;
                    currentWarning = "Successfully placed tower\n";
                    m_warningText.setFillColor(Color::Green);
                    warningShown.restart();
                } else {
                    std::cout << "Mouse released outside window\n";
                    draggedSprite = nullptr;
                }
                std::cout << "Mouse released done\n";
                isDraggingTower = false;
            }
            
            // To start a new round
            static bool bTWasPressedLastUpdate = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                if (!bTWasPressedLastUpdate && m_eGameMode == PlayMode)
                {
                    m_eGameMode = PlayMode;
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


        if (event.type == sf::Event::MouseMoved && !isDraggingTower) {
            sf::Vector2f newPos = m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window));
            Vector2f snapGrid = MathHelpers::getNearestTileCenterPosition(newPos, 50);
            hoveringOnTower = false;
            //for (auto& tower : a_allActiveTowers) 
            for (size_t i = 0; i < a_allActiveTowers.size(); ++i)       // Modifying a_allActiveTowers while iterating may cause iterators/pointers to become invalid. Use index based iteration
            {
                Tower& tower = a_allActiveTowers[i]; 
                if (tower.GetPosition().x == snapGrid.x && tower.GetPosition().y == snapGrid.y) {
                    xPosition = Vector2f(snapGrid.x, snapGrid.y);
                    hoveringOnTower = true;
                    break;
                }
            }
        }
        
        // Makes X go away right after releasing on them
        
        if(event.type == sf::Event::MouseButtonReleased){
            hoveringOnTower = false;
        }
        
    }
    
    

    if (hoveringOnTower) {
        if(placementOrUpgradeTimer.getElapsedTime().asMilliseconds() > 800){
            currentWarning = "Hover and press Q for info";
            m_warningText.setFillColor(Color::Red);

            Vector2i mousePos = sf::Mouse::getPosition(m_Window);
            Vector2f mouseWorldPos = m_Window.mapPixelToCoords(mousePos);
            Vector2f snapGrid = MathHelpers::getNearestTileCenterPosition(mouseWorldPos, 50);
            for (Tower& tower : a_allActiveTowers) {
                if (tower.GetPosition().x == snapGrid.x && tower.GetPosition().y == snapGrid.y) {
                    hoverTowerDamage = round(tower.GetDamage() * 100.0f) / 100.0f;
                    hoverTowerCooldown = round(tower.GetCooldown() * 100.0f) / 100.0f;
                    hoverTowerRange = round(tower.GetRange() * 100.0f) / 100.0f;
                    hoverTowerSpeed = round(tower.GetSpeed() * 100.0f) / 100.0f;
                }
            }
        }
        // Show upgrade info when Q is pressed
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            Vector2f mousePos = m_Window.mapPixelToCoords(Mouse::getPosition(m_Window));
            Vector2f snapGrid = MathHelpers::getNearestTileCenterPosition(mousePos, 50);
            
            // Check which tower we're hovering over
            for (Tower& tower : a_allActiveTowers) {
                if (tower.GetPosition().x == snapGrid.x && tower.GetPosition().y == snapGrid.y) {
                    m_pSelectedTower = &tower;
                    m_bShowUpgradeUI = true;
                    break;
                }
            }
        }
        
        // Perform upgrade when E is pressed
        if (Keyboard::isKeyPressed(Keyboard::E) && m_bShowUpgradeUI) {
            if (m_pSelectedTower && m_pSelectedTower->CanUpgrade()) {
                int upgradeCost = m_pSelectedTower->GetUpgradeCost();
                if (m_iCurrentWealth >= upgradeCost) {
                    if (m_pSelectedTower->Upgrade()) {
                        m_iCurrentWealth -= upgradeCost;
                        currentWarning = "Tower upgraded successfully!";
                        m_warningText.setFillColor(Color::Green);
                        placementOrUpgradeTimer.restart();
                    }
                } else {
                    currentWarning = "Not enough money for upgrade!";
                    m_warningText.setFillColor(Color::Red);
                    placementOrUpgradeTimer.restart();
                }
                warningShown.restart();
            }
            m_bShowUpgradeUI = false;
            m_pSelectedTower = nullptr;
        }
    } else{
        m_pSelectedTower = nullptr;
        m_bShowUpgradeUI = false;
    }
}


void Game::ChangeSizeInputText(Event& event, String& currentText)                   // Add limit condition for input (input must be between 5 and 30??)
{
    // when keyboard input is a digit, append the text
    if (event.text.unicode >= '0' && event.text.unicode <= '9')
    {
        currentText += static_cast<char>(event.text.unicode);
    }
    // when key board input is backspace and if the text is not empty, delete the last character of the text
    else if (event.text.unicode == 8 && !currentText.isEmpty())
    {
        currentText.erase(currentText.getSize() - 1);
        
    }
}

void Game::UpdateInitialPrompt()
{
    // Add chanage cursor when over text input box
    // Add blinking text cursor when one of the text input box is selected
}

void Game::UpdateTiles()
{
    // Change the colors, set tile type of entry, exit.
    if (m_eCurrentEditState == ExitState)
    {
        sf::Vector2i entryTileIndex = tileCenterPosToIndex(m_vEntryTile);
        Tile& entryTile = m_aTiles[entryTileIndex.y][entryTileIndex.x];
        entryTile.m_Sprite.setTexture(m_EntryTileTexture);
        entryTile.setType(Tile::Type::Entry);
    }
    else if (m_eCurrentEditState == PathState)
    {
        sf::Vector2i exitTileIndex = tileCenterPosToIndex(m_vExitTile);
        Tile& exitTile = m_aTiles[exitTileIndex.y][exitTileIndex.x];
        exitTile.m_Sprite.setTexture(m_ExitTileTexture);
        exitTile.setType(Tile::Type::Exit);

        // If deleted path exist in the array, reset the tile type and texture of the deleted path for all elements in the array
        // Then remove all elements from the array
        if (!m_aDeletedPath.empty())
        {
            for (Vector2f vector : m_aDeletedPath)
            {
                sf::Vector2i tileIndex = tileCenterPosToIndex(vector);
                Tile& tile = m_aTiles[tileIndex.y][tileIndex.x];
                tile.setType(Tile::Type::Grass);
                tile.SetTexture(m_GrassTexture);
    
            }
            // Remove all elements from m_aDeletedPath
            m_aDeletedPath.clear();
        }
        

        // Set tile type and change the texture of all current path tiles
        std::cout << "path size before applying texture: " << m_aPath.size() << std::endl;
        for (Vector2f vector : m_aPath)
        {
            sf::Vector2i tileIndex = tileCenterPosToIndex(vector);
            Tile& tile = m_aTiles[tileIndex.y][tileIndex.x];
            if (tile.getType() == Tile::Type::Grass)
            {
                tile.setType(Tile::Type::Path);
                tile.SetTexture(m_PathTexture);
            }

        }
    }

}

void Game::UpdatePlay()
{
    UpdateMonsters();
    UpdateTowers();
    UpdateAxes();

    if (m_MonsterGenerator.getIsAllMonstersSpawned() && m_aMonstersQueue.empty())
    {
        m_bIsRoundEnded = true;
    }

    if (m_iCurrentWealth < 0){
        m_gameOver = true;
    }
}

void Game::UpdateMonsters()
{
    // Generate monsters FIRST, before movement updates
    m_MonsterGenerator.incrementTimeSinceLastGeneration(m_DeltaTime.asSeconds());
    if (m_aMonstersQueue.empty() || m_MonsterGenerator.hasPassedGenerationCoolDown())
    {
        m_MonsterGenerator.generateMonster(*this);
        m_MonsterGenerator.resetTimeSinceLastGeneration();
    }

    // Remove finished monsters
    m_aMonstersQueue.erase(std::remove_if(m_aMonstersQueue.begin(), m_aMonstersQueue.end(),
        [this](Monster& monster) {
            if (monster.GetCurrentPathIndex() >= m_aPath.size() - 1) {
                m_iCurrentWealth -= monster.GetStrength();
                return true;
            }
            return false;
        }), m_aMonstersQueue.end());


    // ALL ENEMY ANIMATION RELATED
    if (enemyAnimationDelay.getElapsedTime().asSeconds() >= frameTime) {
        std::cout <<"Current enemy frame: " << currentEnemyFrame << '\n';
        if (m_eCurrentEditState == FinishedPathingState) {
            std::cout << "Updating enemy textures\n";
            for (auto& enemy : m_aMonstersQueue) {
                if(enemy.GetMonsterType() == MonsterGenerator::Type::Skeleton){
                    std::cout << "Setting skeleton texture\n";
                    enemy.SetTexture(m_SkeletonTextures[currentEnemyFrame]);
                    enemy.SetScale(sf::Vector2f(0.08f, 0.08f));
                    FloatRect monsterSize = enemy.m_Sprite.getLocalBounds();                           // Get Monster sprite width and height
                    enemy.SetOrigin(sf::Vector2f(monsterSize.width / 2, monsterSize.height / 2));      // Set Monster anchor to the center of the sprite
                }
                if(enemy.GetMonsterType() == MonsterGenerator::Type::Reaper){
                    enemy.SetTexture(m_ReaperTextures[currentEnemyFrame]);
                    enemy.SetScale(sf::Vector2f(0.08f, 0.08f));
                    FloatRect monsterSize = enemy.m_Sprite.getLocalBounds();                           // Get Monster sprite width and height
                    enemy.SetOrigin(sf::Vector2f(monsterSize.width / 2, monsterSize.height / 2));      // Set Monster anchor to the center of the sprite
                }
                if(enemy.GetMonsterType() == MonsterGenerator::Type::Golem){
                    enemy.SetTexture(m_GolemTextures[currentEnemyFrame]);
                    enemy.SetScale(sf::Vector2f(0.08f, 0.08f));
                    FloatRect monsterSize = enemy.m_Sprite.getLocalBounds();                           // Get Monster sprite width and height
                    enemy.SetOrigin(sf::Vector2f(monsterSize.width / 2, monsterSize.height / 2));      // Set Monster anchor to the center of the sprite
                }
                if(enemy.GetMonsterType() == MonsterGenerator::Type::Minotaur){
                    enemy.SetTexture(m_MinotaurTextures[currentEnemyFrame]);
                    enemy.SetScale(sf::Vector2f(0.08f, 0.08f));        
                    FloatRect monsterSize = enemy.m_Sprite.getLocalBounds();                           // Get Monster sprite width and height
                    enemy.SetOrigin(sf::Vector2f(monsterSize.width / 2, monsterSize.height / 2));      // Set Monster anchor to the center of the sprite
                }
                if(enemy.GetMonsterType() == MonsterGenerator::Type::Ogre){
                    enemy.SetTexture(m_OgreTextures[currentEnemyFrame]);
                    enemy.SetScale(sf::Vector2f(0.08f, 0.08f));        
                    FloatRect monsterSize = enemy.m_Sprite.getLocalBounds();                           // Get Monster sprite width and height
                    enemy.SetOrigin(sf::Vector2f(monsterSize.width / 2, monsterSize.height / 2));      // Set Monster anchor to the center of the sprite
                }
            }
            
            currentEnemyFrame++;
            if (currentEnemyFrame > 10) {
                currentEnemyFrame = 0;
            }
            enemyAnimationDelay.restart();
        }
    }


    // Update monster positions
    for (Monster& monster : m_aMonstersQueue)
    {
        size_t monsterCurrentTileIndex = monster.GetCurrentPathIndex();
        if (monsterCurrentTileIndex < m_aPath.size() - 1)
        {
            Vector2f nextTilePos = m_aPath[monsterCurrentTileIndex + 1];
            Vector2f tileToMonster = nextTilePos - monster.GetPosition();
            float distanceToNext = MathHelpers::Length(tileToMonster);

            // Calculate movement step based on speed and time
            float dt = std::min(m_DeltaTime.asSeconds(), 0.1f);                 // Fix delta time fluctuations
            float moveStep = dt * monster.GetSpeed();

            // Ensure we don't overshoot
            moveStep = std::min(moveStep, distanceToNext);

            // Normalize safely
            Vector2f direction = (distanceToNext > 1e-6f) ? MathHelpers::getNormalize(tileToMonster) : Vector2f(0, 0);

            // Move the monster with the adjusted moveStep
            monster.Move(direction * moveStep);

            // If the monster has reached the tile, update its path index
            if (distanceToNext <= moveStep + 1e-6f)  // Small epsilon to handle float precision issues
            {
                monster.SetCurrentPathIndex(monsterCurrentTileIndex + 1);
                monster.SetPosition(nextTilePos); // Snap position exactly
            }
        }
    }
}



void Game::UpdateUI()
{
    
    m_scoreText.setString("Score: " + std::to_string(m_iCurrentWealth));   // Set text
    FloatRect scoreTextBounds = m_scoreText.getLocalBounds();
    m_scoreText.setOrigin(scoreTextBounds.width / 2, scoreTextBounds.height / 2);

    m_levelText.setString("Level: " + std::to_string(m_iCurrentLevel));   // Set text
    FloatRect levelTextBounds = m_levelText.getLocalBounds();
    m_levelText.setOrigin(levelTextBounds.width / 2, levelTextBounds.height / 2);

    m_warningText.setString(currentWarning);   // Set text
    FloatRect warningTextBounds = m_warningText.getLocalBounds();
    m_warningText.setOrigin(warningTextBounds.width / 2, warningTextBounds.height / 2);

    m_modeText.setString(currentMode);   // Set text
    FloatRect modeTextBounds = m_modeText.getLocalBounds();
    m_modeText.setOrigin(modeTextBounds.width / 2, modeTextBounds.height / 2);

    if(warningShown.getElapsedTime().asSeconds() > 3){
        currentWarning = "";
    }
    
    if (m_eCurrentEditState == ExitState){
        m_instructionText.setString("Choose an exit Tile...");   // Set text
        FloatRect instructionTextBounds = m_instructionText.getLocalBounds();
        m_instructionText.setOrigin(instructionTextBounds.width / 2, instructionTextBounds.height / 2);
        m_instructionText.setFillColor(Color::Red);     // Set color
    } else if (m_eCurrentEditState == EntryState){
        m_instructionText.setString("Choose an entry Tile...");   // Set text
        FloatRect instructionTextBounds = m_instructionText.getLocalBounds();
        m_instructionText.setOrigin(instructionTextBounds.width / 2, instructionTextBounds.height / 2);
        m_instructionText.setFillColor(Color::Green);     // Set color
    } else if (m_eCurrentEditState == PathState){
        m_instructionText.setString("Draw a path\nstarting from entrance\nand click enter\nto start...");   // Set text
        FloatRect instructionTextBounds = m_instructionText.getLocalBounds();
        m_instructionText.setOrigin(instructionTextBounds.width / 2, instructionTextBounds.height / 2);
        m_instructionText.setFillColor(Color::Blue);     // Set color
    } else {
        m_instructionText.setString("Tower Selection");   // Set text
        FloatRect instructionTextBounds = m_instructionText.getLocalBounds();
        m_instructionText.setOrigin(instructionTextBounds.width / 2, instructionTextBounds.height / 2);
        m_instructionText.setFillColor(Color::White);     // Set color
    }

    m_towerDamage.setString("Damage: " + to_string(hoverTowerDamage));   // Set text
    FloatRect towerDamageBounds = m_towerDamage.getLocalBounds();
    m_towerDamage.setOrigin(towerDamageBounds.width / 2, towerDamageBounds.height / 2);

    m_towerCooldown.setString("Cooldown: " + to_string(hoverTowerCooldown));   // Set text
    FloatRect towerCooldownBounds = m_towerCooldown.getLocalBounds();
    m_towerCooldown.setOrigin(towerCooldownBounds.width / 2, towerCooldownBounds.height / 2);

    m_towerRange.setString("Range: " + to_string(hoverTowerRange));   // Set text
    FloatRect towerRangeBounds = m_towerRange.getLocalBounds();
    m_towerRange.setOrigin(towerRangeBounds.width / 2, towerRangeBounds.height / 2);

    m_towerSpeed.setString("Speed: " + to_string(hoverTowerSpeed));   // Set text
    FloatRect towerSpeedBounds = m_towerSpeed.getLocalBounds();
    m_towerSpeed.setOrigin(towerSpeedBounds.width / 2, towerSpeedBounds.height / 2);

    if (hoveringOnTower){
        m_instructionText.setString("Tower Information:");   // Set text
        FloatRect instructionTextBounds = m_instructionText.getLocalBounds();
        m_instructionText.setOrigin(instructionTextBounds.width / 2, instructionTextBounds.height / 2);
        m_instructionText.setFillColor(Color::White);     // Set color
    }





    // Update upgrade UI if shown
    if (m_bShowUpgradeUI && m_pSelectedTower) {
        m_upgradeText.setFont(m_Font);
        
        std::string upgradeString;
        if (m_pSelectedTower->CanUpgrade()) {
            upgradeString = "Upgrade Cost: " + std::to_string(m_pSelectedTower->GetUpgradeCost()) + 
                          "\nLevel: " + std::to_string(m_pSelectedTower->GetLevel()) +
                          "\nClick to upgrade";
        } else {
            upgradeString = "Max Level Reached";
        }
        
        m_upgradeText.setString(upgradeString);
        m_upgradeText.setCharacterSize(15);
        m_upgradeText.setFillColor(Color::White);
        m_upgradeText.setPosition(m_pSelectedTower->GetPosition() + Vector2f(30, -30));
    }
}

void Game::UpdateTowers()
{
    for (Tower& tower : a_allActiveTowers)
    {
        // Update individual tower cooldown
        tower.UpdateCooldown(m_DeltaTime.asSeconds());

        if (tower.CanShoot()) {
            Entity* pNearestEnemy = nullptr;
            float fShortestDistance = std::numeric_limits<float>::max();
            
            // Find nearest monster within this tower's range
            for (Entity& monster : m_aMonstersQueue)
            {
                sf::Vector2f vTowerToMonster = monster.GetPosition() - tower.GetPosition();
                float fDistance = MathHelpers::Length(vTowerToMonster);
                if (fDistance < fShortestDistance && fDistance < tower.GetRange())
                {
                    fShortestDistance = fDistance;
                    pNearestEnemy = &monster;
                }
            }
    
            if (pNearestEnemy != nullptr)
            {
                // Create and setup new axe
                //Entity& newAxe = m_aAxes.emplace_back(m_RapidBulletlate);
                
                if (tower.GetType() == TowerType::Rapid) {
                    m_aAxes.push_back(m_RapidBulletTemplate);
                } else if (tower.GetType() == TowerType::Sniper) {
                    m_aAxes.push_back(m_SniperBulletTemplate);
                }
                //ADD BULLET WHEN I ADD TOWERS


                Entity& newAxe = m_aAxes.back();
                FloatRect newAxeBounds = newAxe.GetSprite().getLocalBounds(); // Assuming getSprite() returns an sf::Sprite reference
                newAxe.SetOrigin(Vector2f(newAxeBounds.width / 2, newAxeBounds.height / 2));
                newAxe.SetPosition(Vector2f(tower.GetPosition().x, tower.GetPosition().y));
                newAxe.SetScale(Vector2f(0.3f, 0.3f));

                //Depending on tower the bullet will be faster or slower and do more or less damage
                newAxe.m_speed = tower.GetSpeed();
                newAxe.m_fDamage = tower.GetDamage();
                
                // Calculate direction to enemy
                sf::Vector2f vTowerToMonster = pNearestEnemy->GetPosition() - tower.GetPosition();
                vTowerToMonster = MathHelpers::getNormalize(vTowerToMonster);
                // Calculate the angle in degrees
                float angle = atan2(vTowerToMonster.y, vTowerToMonster.x) * 180.0f / M_PI + 90.0f;
                newAxe.SetDirection(vTowerToMonster);
                newAxe.SetRotation(angle);
                

                tower.ResetCooldown(); // Reset this tower's cooldown
            }
        }
    }

    //INSERT HERE
    // ALL TOWER ANIMATION RELATED
    if (towerAnimationDelay.getElapsedTime().asSeconds() >= frameTime) {
        if (m_eCurrentEditState == FinishedPathingState) {
            // Set the texture for each tower
            for (auto& tower : a_activeWoodTowers) {
                tower.SetTexture(m_RapidTowerTextures[currentTowerFrame]);
                /*
                if (std::find(a_allActiveTowers.begin(), a_allActiveTowers.end(), tower) != a_allActiveTowers.end()) {
                    tower.SetTexture(tower1TempTexture);
                }
                */
            }
            for (auto& tower : a_activeStoneTowers) {
                tower.SetTexture(m_SniperTowerTextures[currentTowerFrame]);
                /*
                if (std::find(a_allActiveTowers.begin(), a_allActiveTowers.end(), tower) != a_allActiveTowers.end()) {
                    tower.SetTexture(tower2TempTexture);
                }
                */
            }

            // Update currentFrame and reset if necessary
            currentTowerFrame++;
            if (currentTowerFrame > 5) {
                currentTowerFrame = 0;
            }
            // Restart the clock after updating the frame
            towerAnimationDelay.restart();
        }
    }


    // INSERT HERE

}

void Game::UpdateAxes()
{
    const float COLLISION_DISTANCE = 25.0f; // Adjust collision radius as needed

    for (auto it = m_aAxes.begin(); it != m_aAxes.end();)
    {
        bool hitMonster = false;
        
        // Move axe
        it->Move(it->GetDirection() * it->GetSpeed() * m_DeltaTime.asSeconds());
        
        // Check collision with monsters
        for (auto& monster : m_aMonstersQueue)
        {
            sf::Vector2f diff = monster.GetPosition() - it->GetPosition();
            float distance = MathHelpers::Length(diff);
            
            if (distance < COLLISION_DISTANCE)
            {
                string hitMonsterName;
                if(static_cast<int>(monster.GetMonsterType()) == 0){
                    hitMonsterName = "Skeleton";
                } else if (static_cast<int>(monster.GetMonsterType()) == 1){
                    hitMonsterName = "Reaper";
                }else if (static_cast<int>(monster.GetMonsterType()) == 2){
                    hitMonsterName = "Golem";
                }else if (static_cast<int>(monster.GetMonsterType()) == 3){
                    hitMonsterName = "Ogre";
                }else if (static_cast<int>(monster.GetMonsterType()) == 4){
                    hitMonsterName = "Minotaur";
                }
                std::cout << "Debug: Axe hit " << hitMonster << " at position ("
                          << monster.GetPosition().x << ", "
                          << monster.GetPosition().y << ")" << std::endl;
                hitMonster = true;
                monster.SetHealth(monster.GetHealth()-it->GetDamage());
                cout << "\n"<<monster.GetHealth()<<"\n";
                if (monster.GetHealth() <= 0){
                    // Handle the monster's death (e.g., remove it from the queue)
                    std::cout << "Monster destroyed!" << std::endl;
                    // Remove the monster from the queue (if applicable)
                    auto monsterIt = std::find(m_aMonstersQueue.begin(), m_aMonstersQueue.end(), monster);
                    if (monsterIt != m_aMonstersQueue.end()) {
                        m_aMonstersQueue.erase(monsterIt);
                        m_iCurrentWealth += monster.GetReward();
                    }
                }
                break;
            }
        }
        
        // Remove axe if it hit something or went off screen
        if (hitMonster || 
            it->GetPosition().x < 0 || 
            it->GetPosition().x > m_vWindowSize.x ||
            it->GetPosition().y < 0 || 
            it->GetPosition().y > m_vWindowSize.y)
        {
            it = m_aAxes.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Game::DrawInitialSetUp()
{
    // Erases everything that was drawn last frame
	m_Window.clear();

    // Draw all text
    m_Window.draw(m_IntroText);
    m_Window.draw(m_EnterSizeText);
    if (m_bIsSizeLimitTextShown)
    {
        m_Window.draw(m_SizeLimitText);
    }

    for (RectangleShape box : m_aUserInputBoxWindowSize)
    {
        m_Window.draw(box);
    }
    m_Window.draw(m_WidthSizeInput);
    m_Window.draw(m_HeightSizeInput);

    // Apply submit button press effect
    if (m_SubmitButtonClicked)
    {
        m_Window.draw(m_aButtonBoxes[1]);
    }
    else
    {
        m_Window.draw(m_aButtonBoxes[0]);
    }
    m_Window.display();
}

void Game::DrawMapEditorMode()
{
    // Erases everything that was drawn last frame
	m_Window.clear();

    // Draw all tiles
    for (std::vector<Tile> row : m_aTiles)
    {
        for (Entity tile : row)
        {
            m_Window.draw(tile.m_Sprite);
        }
    }

    ////////// Redo highlight logic??
    // Highlight tiles that are available to choose for the entry (green) and the exit (red) tiles
    m_fElapesdTimeInSeconds += m_DeltaTime.asSeconds();                                     // Measure elapsed time
    // highligt assests are store in an array, the first four is the entry highlights and the second four is the exit highlights
    if (m_eCurrentEditState == EntryState || m_eCurrentEditState == ExitState)
    {
        size_t start = 0;
        if (m_eCurrentEditState == ExitState)
        {
            start = 4;
        }
        // Allow the highlight to blink every 0.5 seconds
        if (m_fElapesdTimeInSeconds >= 0.5)
        {
            for (size_t i = start; i < start + 4; ++i)
            {
                m_Window.draw(m_ahighlights[i]);
            }
            // reset time after 0.5 seconds
            if (m_fElapesdTimeInSeconds >= 1)
            {
                m_fElapesdTimeInSeconds = 0;
            }
        }
    }
    
        // UI RELATED
    m_Window.draw(m_scoreText);
    m_Window.draw(m_levelText);
    m_Window.draw(m_instructionText);
    m_Window.draw(m_warningText);
    m_Window.draw(m_modeText);
    
    if(m_eCurrentEditState == FinishedPathingState && !hoveringOnTower){
        for (auto& tower : a_towerMenu) {
            m_Window.draw(tower);  // If Tile is derived from sf::Drawable               //ADD TOWER INFO HERE
        }
        m_Window.draw(woodTowerPrice);
        m_Window.draw(stoneTowerPrice);
    } else if (hoveringOnTower){
        m_Window.draw(m_towerDamage);
        m_Window.draw(m_towerCooldown);
        m_Window.draw(m_towerRange);
        m_Window.draw(m_towerSpeed);
    }


    if(m_eCurrentEditState == FinishedPathingState){
        for (auto& tower : a_activeWoodTowers) {
            m_Window.draw(tower);  // If Tile is derived from sf::Drawable
        }
    }
    if(m_eCurrentEditState == FinishedPathingState){
        for (auto& tower : a_activeStoneTowers) {
            m_Window.draw(tower);  // If Tile is derived from sf::Drawable
        }
    }
    if(draggedSprite != nullptr){
        m_Window.draw(draggedTower);
    }
    m_Window.draw(m_sfPathLines);
    //m_Window.draw(m_MonsterTemplate.m_Sprite);

    if(hoveringOnTower){
        sf::Vector2f position(xPosition.x-15, xPosition.y-15); // Top-left position of X
        float lineThickness = 6.0f;     // Thickness of X
        float lineLength = 30.0f;       // Length of each line in X

        // Create two diagonal lines using RectangleShape
        sf::RectangleShape line1(sf::Vector2f(lineLength, lineThickness));
        line1.setFillColor(sf::Color::Red);
        line1.setOrigin(lineLength / 2, lineThickness / 2);
        line1.setPosition(position + sf::Vector2f(lineLength / 2, lineLength / 2));
        line1.setRotation(45);  // Diagonal top-left to bottom-right

        sf::RectangleShape line2(sf::Vector2f(lineLength, lineThickness));
        line2.setFillColor(sf::Color::Red);
        line2.setOrigin(lineLength / 2, lineThickness / 2);
        line2.setPosition(position + sf::Vector2f(lineLength / 2, lineLength / 2));
        line2.setRotation(-45); // Diagonal top-right to bottom-left

        m_Window.draw(line1);
        m_Window.draw(line2);
    }

    if(m_gameOver){
        ShowGameOverScreen();
    }

    if (m_bShowUpgradeUI && m_pSelectedTower) {
        m_Window.draw(m_upgradeText);
    }
    
    m_Window.display();
}

void Game::DrawPlayMode()
{

    m_Window.clear();

    ////// Draw Tiles
    for (std::vector<Tile>& row : m_aTiles)
    {
        for (Entity& tile : row)
        {
            m_Window.draw(tile.m_Sprite);
        }
    }

    ////// Draw test monster



    for (Monster& monster : m_aMonstersQueue)
    {
        if (monster.GetCurrentPathIndex() < m_aPath.size() - 1)
        {
            m_Window.draw(monster);
        } 
    }

    // UI RELATED
    m_Window.draw(m_scoreText);
    m_Window.draw(m_levelText);
    m_Window.draw(m_instructionText);
    m_Window.draw(m_warningText);
    m_Window.draw(m_modeText);
    
    if(m_eCurrentEditState == FinishedPathingState && !hoveringOnTower){
        for (auto& tower : a_towerMenu) {
            m_Window.draw(tower);  // If Tile is derived from sf::Drawable               //ADD TOWER INFO HERE
        }
        m_Window.draw(woodTowerPrice);
        m_Window.draw(stoneTowerPrice);
    } else if (hoveringOnTower){
        m_Window.draw(m_towerDamage);
        m_Window.draw(m_towerCooldown);
        m_Window.draw(m_towerRange);
        m_Window.draw(m_towerSpeed);
    }

    if(m_bIsRoundEnded){
        m_Window.draw(m_nextRoundText);
    }


    // Draw the towers and enemies (every frame, without waiting for the animation delay)
    if(m_eCurrentEditState == FinishedPathingState){
        for (auto& tower : a_activeStoneTowers) {
            m_Window.draw(tower);  // Draw each tower
        }
    }
    if(m_eCurrentEditState == FinishedPathingState){
        for (auto& tower : a_activeWoodTowers) {
            m_Window.draw(tower);  // If Tile is derived from sf::Drawable
        }
    }
    for (const Entity& bullet : m_aAxes)
    {
        m_Window.draw(bullet);
    }

    if(draggedSprite != nullptr){
        m_Window.draw(draggedTower);
    }

    #ifdef DEBUG
    // Draw path lines
    m_Window.draw(m_sfPathLines);
    #endif

    if(hoveringOnTower){
        sf::Vector2f position(xPosition.x-15, xPosition.y-15); // Top-left position of X
        float lineThickness = 6.0f;     // Thickness of X
        float lineLength = 30.0f;       // Length of each line in X

        // Create two diagonal lines using RectangleShape
        sf::RectangleShape line1(sf::Vector2f(lineLength, lineThickness));
        line1.setFillColor(sf::Color::Red);
        line1.setOrigin(lineLength / 2, lineThickness / 2);
        line1.setPosition(position + sf::Vector2f(lineLength / 2, lineLength / 2));
        line1.setRotation(45);  // Diagonal top-left to bottom-right

        sf::RectangleShape line2(sf::Vector2f(lineLength, lineThickness));
        line2.setFillColor(sf::Color::Red);
        line2.setOrigin(lineLength / 2, lineThickness / 2);
        line2.setPosition(position + sf::Vector2f(lineLength / 2, lineLength / 2));
        line2.setRotation(-45); // Diagonal top-right to bottom-left

        m_Window.draw(line1);
        m_Window.draw(line2);
    }

    if(m_gameOver){
        ShowGameOverScreen();
    }

    // Draw upgrade UI if shown
    if (m_bShowUpgradeUI && m_pSelectedTower) {
        m_Window.draw(m_upgradeText);
    }

    //m_Window.draw(m_MonsterTemplate);
    
    m_Window.display();
}

// Check if path is valid
bool Game::ValidatePath()
{
    if (!m_aPath.empty())
    {
        // Check if the path is connected
        for (size_t i = 0; i < m_aPath.size() - 1; ++i)
        {
            Vector2f currentTile = m_aPath[i];
            Vector2f nextTile = m_aPath[i + 1];
            Vector2f tileToTile = nextTile - currentTile;
            float distance = MathHelpers::Length(tileToTile);
            if (distance > m_iTileSize)
            {
                return false;
            }
        }

        // Check if the path is connected to the entry and exit
        if (m_aPath[0] != m_vEntryTile || m_aPath[m_aPath.size() - 1] != m_vExitTile)
        {
            return false;
        }

        return true;
    }
    return false;
}

// Helper functions //

// Check if the given tile is on the edge of the grid
bool Game::isEdgeTile(sf::Vector2f tile)
{
    // Check if the tile is on the left or right edge
    bool isOnHorizontalEdge = (tile.x <= m_iTileSize / 2) || (tile.x >= (m_vGridSize.x - 1) * m_iTileSize + m_iTileSize / 2);
    // Check if the tile is on the top or bottom edge
    bool isOnVerticalEdge = (tile.y <= m_iTileSize / 2) || (tile.y >= (m_vGridSize.y - 1) * m_iTileSize + m_iTileSize / 2);

    return isOnHorizontalEdge || isOnVerticalEdge;
}

Vector2i Game::tileCenterPosToIndex(Vector2f gridPos)
{
    return Vector2i(static_cast<int>(gridPos.x/m_iTileSize), static_cast<int>(gridPos.y/m_iTileSize));
}
