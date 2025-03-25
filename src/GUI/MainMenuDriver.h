#ifndef MAIN_MENU_DRIVER_H
#define MAIN_MENU_DRIVER_H

#include "Button.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

using namespace sf;

class MainMenuDriver
{
public:
    MainMenuDriver(RenderWindow& m_Window);
    ~MainMenuDriver() = default;

    void LoadTextures();

    void InitializeTitleLogo();

    void InitializeButtons();

    const Button* GetChooseMapButton() const
    {
        return m_ChooseMapButton.get();
    }

    const Button* GetMapEditorButton() const
    {
        return m_MapEditorButton.get();
    }

    const Button* GetExitButton() const
    {
        return m_ExitButton.get();
    }

    void HandleButtonHover(Vector2f mousePos);

    void HandleButtonClicked(Vector2f mousePos);

    void SetButtonDefaultTexture();
    
    void Draw();

private:
    sf::RenderWindow& m_Window;

    Texture m_TitleLogoTexture;

    Texture m_ChooseMapButtonTexture;
    Texture m_ChooseMapButtonHoverTexture;
    Texture m_ChooseMapButtonPressedTexture;

    Texture m_MapEditorButtonTexture;
    Texture m_MapEditorButtonHoverTexture;
    Texture m_MapEditorButtonPressedTexture;

    Texture m_ExitButtonTexture;
    Texture m_ExitButtonHoverTexture;
    Texture m_ExitButtonPressedTexture;

    Sprite m_TitleLogo;

    std::unique_ptr<Button> m_ChooseMapButton; 
    std::unique_ptr<Button> m_MapEditorButton; 
    std::unique_ptr<Button> m_ExitButton;
};

#endif