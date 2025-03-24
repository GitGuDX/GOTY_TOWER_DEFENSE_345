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
    LoadButtonTextures();
    InitializeIntroText();
    InitializeEnterSizeText();
    InitializeSizeLimitText();
    InitializeInputBox();
    InitializeInputBoxText();
    InitializeButtons();
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

        UpdateIntroText(data.m_IntroTitle);
        UpdateEnterSizeText(data.m_EnterSizeSign);
        UpdateSizeLimitText(data.m_SizeLimitWarning);
        UpdateWidthInputBoxText(data.m_UserInputWindowWidth);
        UpdateHeightInputBoxText(data.m_UserInputWindowHeight);
    }
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
    // if (m_SubmitButtonClicked)
    // {
    //     m_Window.draw(m_aButtonBoxes[1]);
    // }
    // else
    // {
    //     m_Window.draw(m_aButtonBoxes[0]);
    // }
    m_Window.draw(m_PlayButton->GetSprite());
    m_Window.draw(m_BackButton->GetSprite());
}

void GameSetupView::LoadButtonTextures()
{
    m_SubmitButtonTexture.loadFromFile("../src/Images/Buttons/button_play.png");                    // placeholder image. Change button image
    m_SubmitButtonPressedTexture.loadFromFile("../src/Images/Buttons/button_play_pressed.png");                    // placeholder image. Change button image
    m_SubmitButtonHoverTexture.loadFromFile("../src/Images/Buttons/button_play_hover.png");

    m_BackButtonTexture.loadFromFile("../src/Images/Buttons/button_back.png");                    // placeholder image. Change button image
    m_BackButtonHoverTexture.loadFromFile("../src/Images/Buttons/button_back_hover.png");                    // placeholder image. Change button image
    m_BackButtonPressedTexture.loadFromFile("../src/Images/Buttons/button_back_pressed.png");
}

void GameSetupView::InitializeIntroText()
{
    m_IntroText.setFont(m_Font);
    m_IntroText.setCharacterSize(40);
    m_IntroText.setFillColor(Color::White);
    m_IntroText.setPosition(Vector2f(m_Window.getSize().x/2, m_Window.getSize().y/5));    
}

void GameSetupView::InitializeEnterSizeText()
{
    // Initialize "Enter Size" text
    m_EnterSizeText.setFont(m_Font);
    m_EnterSizeText.setCharacterSize(25);
    m_EnterSizeText.setFillColor(Color::White);
    m_EnterSizeText.setPosition(Vector2f(m_Window.getSize().x/2, m_Window.getSize().y/3));   
}

void GameSetupView::InitializeSizeLimitText()
{
    // Initialize "Size Limit" text
    m_SizeLimitText.setFont(m_Font);
    m_SizeLimitText.setCharacterSize(20);
    m_SizeLimitText.setFillColor(Color::White);
    m_SizeLimitText.setPosition(Vector2f(m_Window.getSize().x/2, m_Window.getSize().y*7/8));
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
}

void GameSetupView::InitializeInputBoxText()
{
    if (!m_aUserInputBoxWindowSize.empty())
    {
        RectangleShape& widthInputBox = m_aUserInputBoxWindowSize[0];
        RectangleShape& heightInputBox = m_aUserInputBoxWindowSize[1];
        // Initialize window Width size input Text
        m_WidthSizeInput.setFont(m_Font);
        m_WidthSizeInput.setCharacterSize(m_iInputFontSize);
        m_WidthSizeInput.setFillColor(Color::Red);
        m_WidthSizeInput.setPosition(widthInputBox.getPosition().x - widthInputBox.getSize().x/2 + 3, widthInputBox.getPosition().y + 1);  

        // Initialize window height size input Text
        m_HeightSizeInput.setFont(m_Font);
        m_HeightSizeInput.setCharacterSize(m_iInputFontSize);
        m_HeightSizeInput.setFillColor(Color::Red);
        m_HeightSizeInput.setPosition(heightInputBox.getPosition().x - heightInputBox.getSize().x/2 + 3, heightInputBox.getPosition().y + 1);
    }
    else
    {
        #ifdef DEBUG
        std::cout << "Input box has not been loaded." << std::endl;
        #endif
    }
}

void GameSetupView::InitializeButtons()
{
    m_PlayButton = std::make_unique<Button>(m_SubmitButtonTexture, Vector2f(m_Window.getSize().x/2,m_Window.getSize().y*2/3));
    m_PlayButton->SetScale(Vector2f(0.9f, 0.9f));
    m_PlayButton->SetOriginToCenter();

    m_BackButton = std::make_unique<Button>(m_BackButtonTexture, Vector2f(m_Window.getSize().x/2,m_Window.getSize().y*4/5));
    m_BackButton->SetScale(Vector2f(0.6f, 0.6f));
    m_BackButton->SetOriginToCenter();

    // Sprite submitButton(m_SubmitButtonTexture);
    // submitButton.setScale(Vector2f(5.f, 5.f));
    // submitButton.setOrigin(m_SubmitButtonTexture.getSize().x/2, m_SubmitButtonTexture.getSize().y/2);
    // submitButton.setPosition(Vector2f(m_Window.getSize().x/2,m_Window.getSize().y*2/3));
    // m_aButtonBoxes[0] = submitButton;
    // //Initialise submit button text
    // Sprite submitButtonPressed(m_SubmitButtonPressedTexture);
    // submitButtonPressed.setScale(Vector2f(0.7f, 0.7f));
    // submitButtonPressed.setOrigin(m_SubmitButtonPressedTexture.getSize().x/2, m_SubmitButtonTexture.getSize().y/2);
    // submitButtonPressed.setPosition(Vector2f(m_Window.getSize().x/2,m_Window.getSize().y*2/3));
    // m_aButtonBoxes[1] = submitButtonPressed;
}

void GameSetupView::UpdateIntroText(std::string& title)
{
    m_IntroText.setString(title);
    // Get text size
    float fIntroTextWidth = m_IntroText.getLocalBounds().width;
    float fIntroTextHeight = m_IntroText.getLocalBounds().height;
    // Reset the origin to the center of the text
    m_IntroText.setOrigin(Vector2f(fIntroTextWidth/2, fIntroTextHeight/2));
}

void GameSetupView::UpdateEnterSizeText(std::string& enterSizeInstruction)
{
    m_EnterSizeText.setString(enterSizeInstruction);
    // Get "Enter Size" text size
    float fEnterSizeTextWidth = m_EnterSizeText.getLocalBounds().width;
    float fEnterSizeTextHeight = m_EnterSizeText.getLocalBounds().height;
    // Reset the origin to the center of the text
    m_EnterSizeText.setOrigin(Vector2f(fEnterSizeTextWidth/2, fEnterSizeTextHeight/2)); 
}

void GameSetupView::UpdateSizeLimitText(std::string& sizeLimitWarning)
{
    m_SizeLimitText.setString(sizeLimitWarning);
    // Get "Size Limit" text size
    float fSizeLimitTextWidth = m_SizeLimitText.getLocalBounds().width;
    float fSizeLimitTextHeight = m_SizeLimitText.getLocalBounds().height;
    // Reset the origin to the center of the text
    m_SizeLimitText.setOrigin(Vector2f(fSizeLimitTextWidth/2, fSizeLimitTextHeight/2));
}

void GameSetupView::UpdateWidthInputBoxText(std::string& initialWidth)
{
    m_WidthSizeInput.setString(initialWidth);                                        
    float fWidthSizeInputHeight = m_WidthSizeInput.getLocalBounds().height;
    m_WidthSizeInput.setOrigin(0, fWidthSizeInputHeight);
}

void GameSetupView::UpdateHeightInputBoxText(std::string& initialHeight)
{
    m_HeightSizeInput.setString(initialHeight); 
    float fHeightSizeInputHeight = m_HeightSizeInput.getLocalBounds().height;
    m_HeightSizeInput.setOrigin(0, fHeightSizeInputHeight);
}

void GameSetupView::HandleButtonHover(Vector2f mousePos)
{
    if (m_PlayButton->IsMouseOver(mousePos))
    {
        m_PlayButton->SetTexture(m_SubmitButtonHoverTexture);
    }
    else if (m_BackButton->IsMouseOver(mousePos))
    {
        m_BackButton->SetTexture(m_BackButtonHoverTexture);
    }
    else
    {
        SetButtonDefaultTexture();
    }
}

void GameSetupView::HandleButtonCliked(Vector2f mousePos)
{
    if (m_PlayButton->IsMouseOver(mousePos))
    {
        m_PlayButton->SetTexture(m_SubmitButtonPressedTexture);
    }
    else if (m_BackButton->IsMouseOver(mousePos))
    {
        m_BackButton->SetTexture(m_BackButtonPressedTexture);
    }
    else
    {
        SetButtonDefaultTexture();
    }
}

void GameSetupView::SetButtonDefaultTexture()
{
    m_PlayButton->SetTexture(m_SubmitButtonTexture);
    m_BackButton->SetTexture(m_BackButtonTexture);
}
