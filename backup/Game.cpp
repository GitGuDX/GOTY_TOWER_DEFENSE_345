#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <algorithm>

using namespace sf;

Game::Game(int initialWindowWidth, int initialWindowHeight)
    : m_Window(VideoMode(initialWindowWidth, initialWindowHeight), "Tower Defense 1")
    , m_eGameMode(GameMode::InitialSetUp)
    , m_ePrevGameMode(GameMode::InitialSetUp)
    , m_vGameWindowSize(initialWindowWidth, initialWindowWidth)                                                               // Set default game window size
    , m_eCurrentlyActiveInputBox(ClickedInputBox::None)                                              
{
    m_Window.setFramerateLimit(60);


    // Render Initial SetUp assets
    LoadInitialSetUpAssets(); 
}

Game::~Game()
{
}

void Game::Run()
{
    
    while (m_Window.isOpen())
    {
        HandleInput();

        m_Window.clear();       //Placeholder, create new method

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
            if (m_ePrevGameMode != MapEditorMode) {
                m_Window.create(VideoMode(m_vGameWindowSize.x * m_iTileSize, m_vGameWindowSize.y * m_iTileSize), "New Game");
                LoadMapEditorAssets(); 
                m_ePrevGameMode = MapEditorMode;
            }
            // update;
            DrawMapEditorMode();
            break;
        }
        }
        

        
        m_Window.display();                 //Placeholder, create new method
    }
}

void Game::LoadInitialSetUpAssets()
{
    m_Font.loadFromFile("../Fonts/Kreon-Medium.ttf");
    
    // Initialize "Enter Size" text
    m_EnterSizeText.setFont(m_Font);
    m_EnterSizeText.setString("Enter the size of the map");
    // Get "Enter Size" text size
    float fEnterSizeTextWidth = m_EnterSizeText.getLocalBounds().width;
    float fEnterSizeTextHeight = m_EnterSizeText.getLocalBounds().height;
    // Reset the origin to the center of the text
    m_EnterSizeText.setOrigin(Vector2f(fEnterSizeTextWidth/2, fEnterSizeTextHeight/2));
    // Set "Enter Size" text to the center of the screen
    m_EnterSizeText.setPosition(Vector2f(m_vGameWindowSize.x/2, m_vGameWindowSize.y/3));
    m_EnterSizeText.setFillColor(Color::White);

    //Initialize width input box and store them in an array (index 0)
    RectangleShape InputBoxWidth(Vector2f(m_iInputFontSize * 2.5, m_iInputFontSize));
    InputBoxWidth.setOrigin(InputBoxWidth.getSize().x/2, InputBoxWidth.getSize().y/2);
    InputBoxWidth.setPosition(m_vGameWindowSize.x*1/4, m_vGameWindowSize.y/2);
    InputBoxWidth.setFillColor(Color::White);
    // InputBoxHeight.setOutlineColor(Color(128,128,128));
    // InputBoxHeight.setOutlineThickness(3.f);
    m_aUserInputBoxWindowSize[0] = InputBoxWidth;

    // Initialize window Width size input Text
    m_WidthSizeInput.setFont(m_Font);
    m_WidthSizeInput.setCharacterSize(m_iInputFontSize);
    //m_WidthSizeInput.setString(std::to_string(m_vGameWindowSize.y));                          // Get default window size as placeholder
    m_WidthSizeInput.setString("10");                                                           // For test
    m_WidthSizeInput.setFillColor(Color::Red);
    float fWidthSizeInputHeight = m_WidthSizeInput.getLocalBounds().height;
    m_WidthSizeInput.setOrigin(0, fWidthSizeInputHeight);
    // Set position relative to the input box       
    m_WidthSizeInput.setPosition(InputBoxWidth.getPosition().x - InputBoxWidth.getSize().x/2 + 3, InputBoxWidth.getPosition().y + 1);  

    //Initialize height input box and store them in an array (index 1)
    RectangleShape InputBoxHeight(Vector2f(m_iInputFontSize * 2.5, m_iInputFontSize));
    InputBoxHeight.setOrigin(InputBoxHeight.getSize().x/2, InputBoxHeight.getSize().y/2);
    InputBoxHeight.setPosition(m_vGameWindowSize.x*3/4, m_vGameWindowSize.y/2);
    InputBoxHeight.setFillColor(Color::White);
    // InputBoxHeight.setOutlineColor(Color(128,128,128));
    // InputBoxHeight.setOutlineThickness(3.f);
    m_aUserInputBoxWindowSize[1] = InputBoxHeight;
    FloatRect InputBoxHeightBounds = InputBoxHeight.getLocalBounds();

    // Initialize window height size input Text
    m_HeightSizeInput.setFont(m_Font);
    m_HeightSizeInput.setCharacterSize(m_iInputFontSize);
    //m_HeightSizeInput.setString(std::to_string(m_vGameWindowSize.y));                               // Get default window size as placeholder
    m_HeightSizeInput.setString("10");                                                                // For test
    m_HeightSizeInput.setFillColor(Color::Red);
    float fHeightSizeInputHeight = m_HeightSizeInput.getLocalBounds().height;
    m_HeightSizeInput.setOrigin(0, fHeightSizeInputHeight);
    // Set position relative to the input box
    m_HeightSizeInput.setPosition(InputBoxHeight.getPosition().x - InputBoxHeight.getSize().x/2 + 3, InputBoxHeight.getPosition().y + 1);

    // Initialize submit button and store it in the m_abuttonboxes array
    m_SubmitButtonTexture.loadFromFile("../Images/placeholder_play_button.png");                    // placeholder image. Change button image
    Sprite submitButton(m_SubmitButtonTexture);
    submitButton.setScale(Vector2f(5.f, 5.f));
    submitButton.setOrigin(m_SubmitButtonTexture.getSize().x/2, m_SubmitButtonTexture.getSize().y/2);
    submitButton.setPosition(Vector2f(m_vGameWindowSize.x/2,m_vGameWindowSize.y*2/3));
    m_aButtonBoxes.emplace_back(submitButton);
    //Initialise submit button text
    m_SubmitButtonPressedTexture.loadFromFile("../Images/placeholder_play_button_pressed.png");                    // placeholder image. Change button image
    Sprite submitButtonPressed(m_SubmitButtonPressedTexture);
    submitButtonPressed.setScale(Vector2f(5.f, 5.f));
    submitButtonPressed.setOrigin(m_SubmitButtonPressedTexture.getSize().x/2, m_SubmitButtonTexture.getSize().y/2);
    submitButtonPressed.setPosition(Vector2f(m_vGameWindowSize.x/2,m_vGameWindowSize.y*2/3));
    m_aButtonBoxes.emplace_back(submitButtonPressed);
}

void Game::LoadMapEditorAssets()
{
    // Map editor mode assets
    
    // m_GrassTileTemplate.SetTexture(m_GrassTexture);
    // m_GrassTileTemplate.SetScale(Vector2f(1.f, 1.f));
    // m_GrassTileTemplate.SetTextureRect(sf::IntRect(0,0,50,50));

    m_GrassTexture.loadFromFile("../Images/grass_tile.png");

    m_aTiles.clear();
    for (int i = 0; i < m_vGameWindowSize.y; ++i)
    {
        std::vector<Entity> row;
        for (int j = 0; j < m_vGameWindowSize.x; ++j)
        {
            Tile tempGrassTile;
            tempGrassTile.SetTexture(m_GrassTexture);
            tempGrassTile.SetScale(Vector2f(1.f, 1.f));
            tempGrassTile.SetTextureRect(sf::IntRect(0,0,50,50));
            tempGrassTile.SetPosition(Vector2f(j * m_iTileSize, i * m_iTileSize));
            row.emplace_back(tempGrassTile);
        }
        m_aTiles.emplace_back(row);
    }
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
        // Handle inputs for initial SetUp
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
                    // convert the user input string to unsigned int and resize the window
                    m_vGameWindowSize.x = std::stoi(m_WidthSizeInput.getString().toAnsiString());                // converting sf::String -> std::string -> unsigned int
                    m_vGameWindowSize.y = std::stoi(m_HeightSizeInput.getString().toAnsiString());
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
                }
            }
        }
    }
}

void Game::ChangeSizeInputText(Event& event, String& currentText)       // Add limit condition for input (input must be between 5 and 30??)
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

void Game::DrawInitialSetUp()
{
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
}

void Game::DrawMapEditorMode()
{
    m_Window.clear();

    for (std::vector row : m_aTiles)
    {
        for (Entity grassTile : row)
        {
            m_Window.draw(grassTile.m_Sprite);
        }
    }

    m_Window.display();
}
