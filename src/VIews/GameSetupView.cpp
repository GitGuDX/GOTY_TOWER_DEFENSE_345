#include "GameSetupView.h"

#include <iostream>

using namespace sf;

GameSetupView::GameSetupView(RenderWindow &m_Window, sf::Font &font)
    : m_Window(m_Window)
    , m_Font(font)
    , m_eCurrentlyActiveInputBox(ClickedInputBox::None)
    , m_iInputFontSize(30)
    , m_bIsSizeLimitTextShown(false)
    , m_SubmitButtonClicked(false)

{

    #ifdef LINUX
    m_SubmitButtonTexture.loadFromFile("../src/Images/placeholder_play_button.png");                    // placeholder image. Change button image
    m_SubmitButtonPressedTexture.loadFromFile("../src/Images/placeholder_play_button_pressed.png");                    // placeholder image. Change button image
    #endif
    #ifdef MAC
    m_SubmitButtonTexture.loadFromFile("Images/placeholder_play_button.png");                    // placeholder image. Change button image
    m_SubmitButtonPressedTexture.loadFromFile("Images/placeholder_play_button_pressed.png");                    // placeholder image. Change button image
    #endif
    #ifdef WINDOW
    // add for window
    #endif
    
    
}

void GameSetupView::Update(const IGameSubject &subject)
{
    const GameSetup *gameSetup = dynamic_cast<const GameSetup *>(&subject);
    if (gameSetup)
    {
        auto &data = m_GameSetupSubjects[gameSetup];
        data.m_IntroTitle = gameSetup->GetIntroTitle();
        data.m_EnterSizeSign = gameSetup->GetEnterSizeSign();
        data.m_UserInputWindowHeight = gameSetup->GetUserInputWindowHeight();
        data.m_UserInputWindowWidth = gameSetup->GetUserInputWindowWidth();
        data.m_SizeLimitWarning = gameSetup->GetSizeLimitWarning();
    }

    InitializeIntroText();
    InitializeEnterSizeText();
    InitializeSizeLimitText();
    InitializeInputBox();
    InitializeSubmitButton();
}

void GameSetupView::Draw()
{
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
}

void GameSetupView::InitializeIntroText()
{
    m_IntroText.setFont(m_Font);
    if (!m_GameSetupSubjects.empty()) {
        m_IntroText.setString(m_GameSetupSubjects.begin()->second.m_IntroTitle);
    }
    m_IntroText.setCharacterSize(40);
    m_IntroText.setFillColor(Color::White);
    // Get text size
    float fIntroTextWidth = m_IntroText.getLocalBounds().width;
    float fIntroTextHeight = m_IntroText.getLocalBounds().height;
    // Reset the origin to the center of the text
    m_IntroText.setOrigin(Vector2f(fIntroTextWidth/2, fIntroTextHeight/2));
    // Set text to the center of the screen
    m_IntroText.setPosition(Vector2f(m_Window.getSize().x/2, m_Window.getSize().y/5));
}

void GameSetupView::InitializeEnterSizeText()
{
    // Initialize "Enter Size" text
    m_EnterSizeText.setFont(m_Font);
    if (!m_GameSetupSubjects.empty()) {
        m_EnterSizeText.setString(m_GameSetupSubjects.begin()->second.m_EnterSizeSign);
    }
    m_EnterSizeText.setCharacterSize(25);
    //m_SizeLimitText.setScale(0.80, 0.80);
    // Get "Enter Size" text size
    float fEnterSizeTextWidth = m_EnterSizeText.getLocalBounds().width;
    float fEnterSizeTextHeight = m_EnterSizeText.getLocalBounds().height;
    // Reset the origin to the center of the text
    m_EnterSizeText.setOrigin(Vector2f(fEnterSizeTextWidth/2, fEnterSizeTextHeight/2));
    // Set "Enter Size" text to the center of the screen
    m_EnterSizeText.setPosition(Vector2f(m_Window.getSize().x/2, m_Window.getSize().y/3));
    m_EnterSizeText.setFillColor(Color::White);
}

void GameSetupView::InitializeSizeLimitText()
{
    // Initialize "Size Limit" text
    m_SizeLimitText.setFont(m_Font);
    if (!m_GameSetupSubjects.empty()) {
        m_SizeLimitText.setString(m_GameSetupSubjects.begin()->second.m_SizeLimitWarning);
    }
    m_SizeLimitText.setCharacterSize(20);
    // Get "Size Limit" text size
    float fSizeLimitTextWidth = m_SizeLimitText.getLocalBounds().width;
    float fSizeLimitTextHeight = m_SizeLimitText.getLocalBounds().height;
    // Reset the origin to the center of the text
    m_SizeLimitText.setOrigin(Vector2f(fSizeLimitTextWidth/2, fSizeLimitTextHeight/2));
    // Set "Size Limit" text to the center of the screen
    m_SizeLimitText.setPosition(Vector2f(m_Window.getSize().x/2, m_Window.getSize().y*4/5));
    m_SizeLimitText.setFillColor(Color::White);
}

void GameSetupView::InitializeInputBox()
{
    //Initialize width input box and store them in an array (index 0)
    RectangleShape InputBoxWidth(Vector2f(m_iInputFontSize * 1.5, m_iInputFontSize));
    InputBoxWidth.setOrigin(InputBoxWidth.getSize().x/2, InputBoxWidth.getSize().y/2);
    InputBoxWidth.setPosition(Vector2f(m_Window.getSize().x*3/8, m_Window.getSize().y/2));
    InputBoxWidth.setFillColor(Color::White);
    m_aUserInputBoxWindowSize[0] = InputBoxWidth;

    //Initialize height input box and store them in an array (index 1)
    RectangleShape InputBoxHeight(Vector2f(m_iInputFontSize * 1.5, m_iInputFontSize));
    InputBoxHeight.setOrigin(InputBoxHeight.getSize().x/2, InputBoxHeight.getSize().y/2);
    InputBoxHeight.setPosition(Vector2f(m_Window.getSize().x*5/8, m_Window.getSize().y/2));
    InputBoxHeight.setFillColor(Color::White);
    m_aUserInputBoxWindowSize[1] = InputBoxHeight;

    // Initialize window Width size input Text
    m_WidthSizeInput.setFont(m_Font);
    m_WidthSizeInput.setCharacterSize(m_iInputFontSize);
    m_WidthSizeInput.setString(m_GameSetupSubjects.begin()->second.m_UserInputWindowWidth);                                                           // For test
    m_WidthSizeInput.setFillColor(Color::Red);
    float fWidthSizeInputHeight = m_WidthSizeInput.getLocalBounds().height;
    m_WidthSizeInput.setOrigin(0, fWidthSizeInputHeight);
    // Set position relative to the input box       
    m_WidthSizeInput.setPosition(InputBoxWidth.getPosition().x - InputBoxWidth.getSize().x/2 + 3, InputBoxWidth.getPosition().y + 1);  

    // Initialize window height size input Text
    m_HeightSizeInput.setFont(m_Font);
    m_HeightSizeInput.setCharacterSize(m_iInputFontSize);
    m_HeightSizeInput.setString(m_GameSetupSubjects.begin()->second.m_UserInputWindowHeight);                                                                // For test
    m_HeightSizeInput.setFillColor(Color::Red);
    float fHeightSizeInputHeight = m_HeightSizeInput.getLocalBounds().height;
    m_HeightSizeInput.setOrigin(0, fHeightSizeInputHeight);
    // Set position relative to the input box
    m_HeightSizeInput.setPosition(InputBoxHeight.getPosition().x - InputBoxHeight.getSize().x/2 + 3, InputBoxHeight.getPosition().y + 1);
}

void GameSetupView::InitializeSubmitButton()
{
    // Initialize submit button and store it in the m_abuttonboxes array
    Sprite submitButton(m_SubmitButtonTexture);
    submitButton.setScale(Vector2f(5.f, 5.f));
    submitButton.setOrigin(m_SubmitButtonTexture.getSize().x/2, m_SubmitButtonTexture.getSize().y/2);
    submitButton.setPosition(Vector2f(m_Window.getSize().x/2,m_Window.getSize().y*2/3));
    m_aButtonBoxes[0] = submitButton;
    //Initialise submit button text
    Sprite submitButtonPressed(m_SubmitButtonPressedTexture);
    submitButtonPressed.setScale(Vector2f(5.f, 5.f));
    submitButtonPressed.setOrigin(m_SubmitButtonPressedTexture.getSize().x/2, m_SubmitButtonTexture.getSize().y/2);
    submitButtonPressed.setPosition(Vector2f(m_Window.getSize().x/2,m_Window.getSize().y*2/3));
    m_aButtonBoxes[1] = submitButtonPressed;
}
