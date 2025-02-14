// NOTE: When path creation is completed, press t on the keyboard to go to play mode

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <algorithm>

#include "Math_Helpers.h"

using namespace sf;

Game::Game(int initialWindowWidth, int initialWindowHeight)
    : m_Window(VideoMode(initialWindowWidth, initialWindowHeight), "Tower Defense 1")           // Initiliaze window screen
    , m_eGameMode(GameMode::InitialSetUp)                                                       // set current game mode to intial set up
    // Set previous game mode to initial set up. Later, this helps track when the game mode changes for the first time.
    , m_ePrevGameMode(GameMode::InitialSetUp)
    , m_vWindowSize(initialWindowWidth, initialWindowHeight)                                   // Set Window size
    , m_iTileSize(50)                                                                          // Set Tile size to 50px
    , m_eCurrentlyActiveInputBox(ClickedInputBox::None)
    // Monster generator initiliazed with base number of monsters and their increase rate per level                
    , m_MonsterGenerator(1, 2)
    , m_iCurrentLevel(1)
    ,m_AxeTemplate()                                                                                                             
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
            // Load MapEditorMode assets only when MapEditorMode is initialized for the first time
            if (m_ePrevGameMode != MapEditorMode) {
                m_Window.create(VideoMode(m_vWindowSize.x, m_vWindowSize.y), "New Game");
                LoadMapEditorAssets(); 
                m_ePrevGameMode = MapEditorMode;
            }

            UpdateTiles();
            
            DrawMapEditorMode();
            break;
        }
        case PlayMode:
        {
            // Load Play Mode assets once only when PlayMode is initialized for the first time then set previous mode to PlayMode so this condition
            // only triggers once
            if (m_ePrevGameMode != PlayMode)
            {
                LoadPlayModeAssets();
                m_ePrevGameMode = PlayMode;
            }
            
            UpdateMonsters();
            UpdateTowers();
            UpdateAxes();
            DrawPlayMode();
            break;
        }
        case Pause:
        {
            break;
        }
        }
        
        //m_Window.display();                 //Placeholder, create new method
    }
}

void Game::LoadInitialSetUpAssets()
{
    m_Font.loadFromFile("Fonts/Kreon-Medium.ttf");
    
    // Initialize "Enter Size" text
    m_EnterSizeText.setFont(m_Font);
    m_EnterSizeText.setString("Enter the size of the map");
    // Get "Enter Size" text size
    float fEnterSizeTextWidth = m_EnterSizeText.getLocalBounds().width;
    float fEnterSizeTextHeight = m_EnterSizeText.getLocalBounds().height;
    // Reset the origin to the center of the text
    m_EnterSizeText.setOrigin(Vector2f(fEnterSizeTextWidth/2, fEnterSizeTextHeight/2));
    // Set "Enter Size" text to the center of the screen
    m_EnterSizeText.setPosition(Vector2f(m_vWindowSize.x/2, m_vWindowSize.y/3));
    m_EnterSizeText.setFillColor(Color::White);

    //Initialize width input box and store them in an array (index 0)
    RectangleShape InputBoxWidth(Vector2f(m_iInputFontSize * 2.5, m_iInputFontSize));
    InputBoxWidth.setOrigin(InputBoxWidth.getSize().x/2, InputBoxWidth.getSize().y/2);
    InputBoxWidth.setPosition(Vector2f(m_vWindowSize.x*1/4, m_vWindowSize.y/2));
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
    RectangleShape InputBoxHeight(Vector2f(m_iInputFontSize * 2.5, m_iInputFontSize));
    InputBoxHeight.setOrigin(InputBoxHeight.getSize().x/2, InputBoxHeight.getSize().y/2);
    InputBoxHeight.setPosition(Vector2f(m_vWindowSize.x*3/4, m_vWindowSize.y/2));
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
    m_SubmitButtonTexture.loadFromFile("Images/placeholder_play_button.png");                    // placeholder image. Change button image
    Sprite submitButton(m_SubmitButtonTexture);
    submitButton.setScale(Vector2f(5.f, 5.f));
    submitButton.setOrigin(m_SubmitButtonTexture.getSize().x/2, m_SubmitButtonTexture.getSize().y/2);
    submitButton.setPosition(Vector2f(m_vWindowSize.x/2,m_vWindowSize.y*2/3));
    m_aButtonBoxes.emplace_back(submitButton);
    //Initialise submit button text
    m_SubmitButtonPressedTexture.loadFromFile("Images/placeholder_play_button_pressed.png");                    // placeholder image. Change button image
    Sprite submitButtonPressed(m_SubmitButtonPressedTexture);
    submitButtonPressed.setScale(Vector2f(5.f, 5.f));
    submitButtonPressed.setOrigin(m_SubmitButtonPressedTexture.getSize().x/2, m_SubmitButtonTexture.getSize().y/2);
    submitButtonPressed.setPosition(Vector2f(m_vWindowSize.x/2,m_vWindowSize.y*2/3));
    m_aButtonBoxes.emplace_back(submitButtonPressed);
}

void Game::LoadMapEditorAssets()
{
    // Map editor mode assets
    m_GrassTexture.loadFromFile("Images/grass_Tile.png");
    m_PathTexture.loadFromFile("Images/path_Tile.png");
    m_EntryTileTexture.loadFromFile("Images/entry_Zone_Tile.png");
    m_ExitTileTexture.loadFromFile("Images/exit_Zone_Tile.png");

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
            tempGrassTile.SetPosition(Vector2f(j * m_iTileSize, i * m_iTileSize));
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

void Game::LoadPlayModeAssets()
{
    // Load monster texture
    m_MonsterTexture.loadFromFile("Images/monster_1.png");
    m_TowerTexture.loadFromFile("Images/tower.png");
    m_TowerTexture.setSmooth(true);
    m_AxeTexture.loadFromFile("Images/Axe.png");
	m_AxeTemplate.SetTexture(m_AxeTexture);
	m_AxeTemplate.SetScale(sf::Vector2f(0.05, 0.05));
	m_AxeTemplate.SetOrigin(sf::Vector2f(8, 8));


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
                    // Reset window size
                    m_vWindowSize = Vector2i(m_vGridSize.x*m_iTileSize, m_vGridSize.y*m_iTileSize);
                    m_eGameMode = GameMode::MapEditorMode;
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
                if (event.mouseButton.button == sf::Mouse::Left) 
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
            if (event.type == sf::Event::MouseMoved && m_eCurrentEditState == PathState)
            {
                //std::cout << "Number of path tiles created: " << m_aPath.size() <<'\n';
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
                            m_aPath.pop_back();
                            m_sfPathLines.resize(m_aPath.size());
                        }
                        // Normal pathing. first check if the current tile is not the previous tile then append path tile
                        else if (m_aPath.back().x != gridPos.x || m_aPath.back().y != gridPos.y)
                        {
                            m_aPath.push_back(gridPos);
                            m_sfPathLines.append(sf::Vertex(gridPos, sf::Color::White));
                        }
                    }
                }
                
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                   // std::cout << "[DEBUG] " << std::endl;

                    m_IsPathingMousePressed = false;
                }
            }
            //// For test. 
            // In normal game, user should be allowed to place towers then press play button to start game
            static bool bTWasPressedLastUpdate = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
             //   std::cout << "one of the keys was pressed! " << std::endl;
                if (!bTWasPressedLastUpdate)
                {
                 //   std::cout << "play mode activated" << std::endl;
                    m_eGameMode = PlayMode;
                }
                bTWasPressedLastUpdate = true;
            }
            else
            {
                bTWasPressedLastUpdate = false;
            }
        }

        if (m_eGameMode == PlayMode) {
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2f clickedPos(event.mouseButton.x, event.mouseButton.y);
                    Vector2f gridPos = MathHelpers::getNearestTileCenterPosition(clickedPos, m_iTileSize);
                    std::cout << "Click detected at: " << clickedPos.x << "," << clickedPos.y << "\n";
                std::cout << "Snapped to grid: " << gridPos.x << "," << gridPos.y << "\n";
        
                Vector2i tileIndex = tileCenterPosToIndex(gridPos);
                std::cout << "Tile index: " << tileIndex.x << "," << tileIndex.y << "\n";
        
        // Validate tile bounds
                if (tileIndex.x >= 0 && tileIndex.x < m_vGridSize.x && 
                 tileIndex.y >= 0 && tileIndex.y < m_vGridSize.y) {
            // ...existing placement code...
                    } else {
                std::cout << "Invalid tile position!\n";
         }
                    if (m_aTiles[tileIndex.y][tileIndex.x].getType() == Tile::Type::Grass) {
                        Tower newTower;
                        newTower.SetTexture(m_TowerTexture);
                        newTower.SetScale(Vector2f(1.0f, 1.0f));  // Adjust scale to fit one tile
                        newTower.SetTextureRect(sf::IntRect(0, 0, 50, 50));
                        Vector2f towerOrigin(m_iTileSize / 2.0f, m_iTileSize / 2.0f);  // Center point of tower
                        newTower.SetOrigin(towerOrigin);
                        newTower.SetPosition(gridPos);
                        m_aTowers.push_back(newTower);
                    }
                }
            }
        }
        
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

        // Set tile type and change the texture of all current path tiles
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

    ////////////// Need to re-skin paths
    ////////////// Need tile path reset update

}

void Game::UpdateMonsters()
{
    // Generate the first monster and add it to the array
    if (m_aMonstersQueue.empty())
    {
        m_MonsterGenerator.generateMonster(*this);              // Dereference the pointer and pass the address of 'this'. generateMonstert takes pass by reference
    }
    /////////// To move Monster to the next path tile
    //std::cout << m_aMonstersQueue.size() <<'\n';
    for (Monster& monster : m_aMonstersQueue)
    {
        // Get Monster's current tile index
        size_t monsterCurrentTileIndex = monster.GetCurrentPathIndex();
        // While Monster's current index is less than the size of the path array move the monster
        if (monsterCurrentTileIndex < m_aPath.size())
        {
            // Get the position of the next tile
            Vector2f nextTilePos = m_aPath[monsterCurrentTileIndex + 1];
            // Get the vector difference between the monster and the next tile
            Vector2f tileToMonster = nextTilePos - monster.GetPosition();
            // Normalize the distance
            tileToMonster = MathHelpers::getNormalize(tileToMonster);
            // Check if the monster is close enough to the target tile (e.g., within 0.1f units).
            if (std::abs(monster.GetPosition().x - nextTilePos.x) < 0.1f &&
                std::abs(monster.GetPosition().y - nextTilePos.y) < 0.1f)
            {
                // The reason for set position is needed here despite the fact that the move function would have already adjusted the monster's position is that 
                // the Move adjusts the position by a very small increment. This presents a floating-point precision errors and small misalignment can add up over time.
                // Without "snapping" to the next tile position, the monster might slowly drift off the grid, causing pathfinding position check to become inaccurate.
                monster.SetPosition(nextTilePos);
                monster.SetCurrentPathIndex(monsterCurrentTileIndex + 1);
                /////////// Generate Monsters - need update
                m_MonsterGenerator.generateMonster(*this);
            }
            else
            {
                // std::cout << m_DeltaTime.asSeconds() <<"\n";
                // std::cout << monster.GetSpeed() <<"\n";
                // std::cout << tileToMonster.x << ' ' << tileToMonster.y << '\n';
                //Vector2f test = tileToMonster * m_DeltaTime.asSeconds() * monster.GetSpeed();
                //std::cout << test.x << ' ' << test.y << '\n';
                monster.Move(tileToMonster * m_DeltaTime.asSeconds() * monster.GetSpeed());
            }    
        }
    }
    
}

void Game::UpdateTowers()
{
    static float shootCooldown = 0.0f;  // Track time since last shot

    // Update cooldown timer
    shootCooldown -= m_DeltaTime.asSeconds();
    for (Entity& tower : m_aTowers)
    {
        if (shootCooldown <= 0.0f) {
            Entity* pNearestEnemy = nullptr;
            float fShortestDistance  = std::numeric_limits<float>::max();
            for  (Entity& monster : m_aMonstersQueue)
            {
                sf::Vector2f vTowerToMonster = monster.GetPosition() - tower.GetPosition();
                float fDistance = MathHelpers::Length(vTowerToMonster);
                if (fDistance < fShortestDistance)
                {
                    fShortestDistance = fDistance;
                    pNearestEnemy = &monster;
                }
                
            }
    
            if (pNearestEnemy != nullptr && fShortestDistance < 300.0f) // 300 is attack range
            {
                // Create and setup new axe
                Entity& newAxe = m_Axes.emplace_back(m_AxeTemplate);
                newAxe.SetPosition(tower.GetPosition());
                
                // Calculate direction to enemy
                sf::Vector2f vTowerToMonster = pNearestEnemy->GetPosition() - tower.GetPosition();
                vTowerToMonster = MathHelpers::getNormalize(vTowerToMonster);
                newAxe.m_Direction = vTowerToMonster;// Store initial direction

                // Debug: Print axe creation and movement info
                std::cout << "Axe created at: (" << tower.GetPosition().x << "," << tower.GetPosition().y << ")\n";
                std::cout << "Target monster at: (" << pNearestEnemy->GetPosition().x << "," 
                          << pNearestEnemy->GetPosition().y << ")\n";
                std::cout << "Direction vector: (" << vTowerToMonster.x << "," << vTowerToMonster.y << ")\n";
                std::cout << "Movement speed: " << 500.0f * m_DeltaTime.asSeconds() << "\n";
                
                // Move axe in that direction
              //  newAxe.Move(vTowerToMonster * 500.0f * m_DeltaTime.asSeconds());
                shootCooldown = 3.0f;  // Reset cooldown timer
                
                // Debug: Print new axe position after movement
                std::cout << "Axe new position: (" << newAxe.GetPosition().x << "," 
                          << newAxe.GetPosition().y << ")\n";
                std::cout << "Total axes in game: " << m_Axes.size() << "\n\n";
            }
        }
    }
    // Update tower logic
}

void Game::UpdateAxes()
{
    for (auto it = m_Axes.begin(); it != m_Axes.end();)
    {
        // Use stored direction to move axe
        it->Move(it->m_Direction * 1000.0f * m_DeltaTime.asSeconds());
        
        // Remove if off screen
        sf::Vector2f pos = it->GetPosition();
        if (pos.x < 0 || pos.x > m_vWindowSize.x || 
            pos.y < 0 || pos.y > m_vWindowSize.y)
        {
            it = m_Axes.erase(it);
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

    m_Window.draw(m_EnterSizeText);

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
    

    m_Window.draw(m_sfPathLines);
    //m_Window.draw(m_MonsterTemplate.m_Sprite);
    
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

    for (Tower& tower : m_aTowers) {
        m_Window.draw(tower);
        //tower.DebugPrint();

    }

    for (const Entity& axe : m_Axes)
    {
        m_Window.draw(axe);
    }

    ////// Draw test monster
    for (Monster& monster : m_aMonstersQueue)
    {
        if (monster.GetCurrentPathIndex() < m_aPath.size() - 1)
        {
            m_Window.draw(monster);
        }
    }

    
    

    m_Window.display();
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
