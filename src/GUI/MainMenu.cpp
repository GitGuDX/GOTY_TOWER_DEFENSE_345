#include "MainMenu.h"

MainMenu::MainMenu(RenderWindow &m_Window)
    : m_Window(m_Window)
{
}

void MainMenu::LoadTextures()
{
    m_TitleLogoTexture.loadFromFile("../src/Images/Title_Logos/Title_Logo_4.png");

    m_ChooseMapButtonTexture.loadFromFile("../src/Images/Buttons/button_choose-a-map.png");
    m_ChooseMapButtonHoverTexture.loadFromFile("../src/Images/Buttons/button_choose-a-map_hover.png");
    m_ChooseMapButtonPressedTexture.loadFromFile("../src/Images/Buttons/button_choose-a-map_pressed.png");

    m_MapEditorButtonTexture.loadFromFile("../src/Images/Buttons/button_map-editor.png");
    m_MapEditorButtonHoverTexture.loadFromFile("../src/Images/Buttons/button_map-editor_hover.png");
    m_MapEditorButtonPressedTexture.loadFromFile("../src/Images/Buttons/button_map-editor_pressed.png");

    m_ExitButtonTexture.loadFromFile("../src/Images/Buttons/button_exit.png");
    m_ExitButtonHoverTexture.loadFromFile("../src/Images/Buttons/button_exit_hover.png");
    m_ExitButtonPressedTexture.loadFromFile("../src/Images/Buttons/button_exit_pressed.png");
}

void MainMenu::InitializeTitleLogo()
{
    m_TitleLogo.setTexture(m_TitleLogoTexture);
    m_TitleLogo.setScale(Vector2f(0.45f, 0.45f));
    m_TitleLogo.setOrigin(Vector2f(m_TitleLogoTexture.getSize().x/2, m_TitleLogoTexture.getSize().y/2));
    m_TitleLogo.setPosition(Vector2f(m_Window.getSize().x/2, m_Window.getSize().y*3/9));
}

void MainMenu::InitializeButtons()
{
    Vector2f chooseButtonPosition = Vector2f(m_Window.getSize().x/2, m_Window.getSize().y*6/9);
    Vector2f mapEditorButtonPosition = Vector2f(m_Window.getSize().x/2, m_Window.getSize().y*7/9);
    Vector2f exitButtonPosition = Vector2f(m_Window.getSize().x/2, m_Window.getSize().y*8/9);

    m_ChooseMapButton = std::make_unique<Button>(m_ChooseMapButtonTexture, chooseButtonPosition);
    m_MapEditorButton = std::make_unique<Button>(m_MapEditorButtonTexture, mapEditorButtonPosition);
    m_ExitButton = std::make_unique<Button>(m_ExitButtonTexture, exitButtonPosition);

    m_ChooseMapButton->SetOriginToCenter();
    m_MapEditorButton->SetOriginToCenter();
    m_ExitButton->SetOriginToCenter();

    Vector2f buttonScale = Vector2f(0.7f, 0.7f);
    m_ChooseMapButton->SetScale(buttonScale);
    m_MapEditorButton->SetScale(buttonScale);
    m_ExitButton->SetScale(buttonScale);
}

void MainMenu::Draw()
{
    m_Window.draw(m_TitleLogo);
    m_ChooseMapButton->Draw(m_Window);
    m_MapEditorButton->Draw(m_Window);
    m_ExitButton->Draw(m_Window);
}
