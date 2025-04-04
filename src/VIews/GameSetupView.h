#ifndef GAMESETUPVIEW_H
#define GAMESETUPVIEW_H

#include "../Platform.h"
#include "../GameEvents.h"
#include "../GUI/Button.h"
#include "../GUI/GameSetup.h"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <unordered_map>
#include <array>
#include <memory>


class GameSetupView : public IGameObserver
{
private:
    struct GameSetupData
    {
        std::string m_IntroTitle;
        std::string m_EnterSizeSign;
        std::string m_UserInputWindowHeight;
        std::string m_UserInputWindowWidth;
        std::string m_SizeLimitWarning;
    };

public:
    enum ClickedInputBox
    {
        Width,
        Height,
        None
    };

public:
    GameSetupView(sf::RenderWindow& m_Window, sf::Font& font);
    ~GameSetupView() = default;

    void Update(const IGameSubject& subject);

    void Draw();

    bool GetSubmitButtonClicked() const { return m_SubmitButtonClicked; }
    bool GetIsSizeLimitTextShown() const { return m_bIsSizeLimitTextShown; }
    std::array<sf::RectangleShape, 2>& GetUserInputBoxWindowSize() { return m_aUserInputBoxWindowSize; }
    //std::array<sf::Sprite, 2>& GetButtonBoxes() { return m_aButtonBoxes; }
    const Button* GetPlayButton() const { return m_PlayButton.get(); }
    const Button* GetBackButton() const { return m_BackButton.get(); }
    const ClickedInputBox& GetCurrentlyActiveInputBox() const { return m_eCurrentlyActiveInputBox; }

    void SetSubmitButtonClicked(bool clicked) { m_SubmitButtonClicked = clicked; }
    void SetIsSizeLimitTextShown(bool shown) { m_bIsSizeLimitTextShown = shown; }
    void SetCurrentlyActiveInputBox(ClickedInputBox box) { m_eCurrentlyActiveInputBox = box; }

    void ClearSubjects() { m_GameSetupSubjects.clear(); }

    void HandleButtonHover(sf::Vector2f mousePos);

    void HandleButtonCliked(sf::Vector2f mousePos);
private:
    // ** Load class
    void LoadButtonTextures();

    void InitializeIntroText();
    void InitializeEnterSizeText();
    void InitializeSizeLimitText();
    void InitializeInputBox();
    void InitializeInputBoxText();
    void InitializeButtons();

    void UpdateIntroText(std::string& title);
    void UpdateEnterSizeText(std::string& enterSizeInstruction);
    void UpdateSizeLimitText(std::string& sizeLimitWarning);
    void UpdateWidthInputBoxText(std::string& initialWidth);
    void UpdateHeightInputBoxText(std::string& initialHeight);

    void SetButtonDefaultTexture();
private:

    std::unordered_map<const GameSetup*, GameSetupData> m_GameSetupSubjects;

    std::array<sf::RectangleShape, 2> m_aUserInputBoxWindowSize;            // GAMESETUP VIEW, Array storing current input box assets
    std::unique_ptr<Button> m_PlayButton;
    std::unique_ptr<Button> m_BackButton;
    //std::array<sf::Sprite, 2> m_aButtonBoxes;                                 // GAMESETUP VIEW, Array storing button box assets

    sf::RenderWindow& m_Window;

    sf::Font& m_Font;

    sf::Text m_IntroText;
    sf::Text m_EnterSizeText;
    sf::Text m_SizeLimitText;
    sf::Text m_WidthSizeInput;
    sf::Text m_HeightSizeInput;

    sf::Texture m_SubmitButtonTexture;                                      // GAMESETUP VIEW
    sf::Texture m_SubmitButtonHoverTexture;
    sf::Texture m_SubmitButtonPressedTexture;                               // GAMESETUP VIEW

    sf::Texture m_BackButtonTexture;                                    
    sf::Texture m_BackButtonHoverTexture;
    sf::Texture m_BackButtonPressedTexture;  

    ClickedInputBox m_eCurrentlyActiveInputBox;                         // GAMESETUP VIEW

    int m_iInputFontSize;                          // GAMESETUP VIEW
    
    bool m_bIsSizeLimitTextShown;               // GAMESETUP VIEW
    bool m_SubmitButtonClicked;                                 // GAMESETUP VIEW

};

#endif // GAMESETUPVIEW_H