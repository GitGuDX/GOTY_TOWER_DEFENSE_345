#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Button.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

using namespace sf;

class MainMenu
{
public:
    MainMenu(RenderWindow& m_Window);
    ~MainMenu() = default;

    void LoadTextures();

    void InitializeTitleLogo();

    void InitializeButtons();

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