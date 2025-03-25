#include "MainMenuDriver.h"


MainMenuDriver::MainMenuDriver(RenderWindow &m_Window)
    : m_Window(m_Window)
{
}

void MainMenuDriver::LoadTextures()
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

void MainMenuDriver::InitializeTitleLogo()
{
    m_TitleLogo.setTexture(m_TitleLogoTexture);
    m_TitleLogo.setScale(Vector2f(0.45f, 0.45f));
    m_TitleLogo.setOrigin(Vector2f(m_TitleLogoTexture.getSize().x/2, m_TitleLogoTexture.getSize().y/2));
    m_TitleLogo.setPosition(Vector2f(m_Window.getSize().x/2, m_Window.getSize().y*3/9));
}

void MainMenuDriver::InitializeButtons()
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

void MainMenuDriver::HandleButtonHover(Vector2f mousePos)
{
    if (m_ChooseMapButton->IsMouseOver(mousePos))
    {
        m_ChooseMapButton->SetTexture(m_ChooseMapButtonHoverTexture);
    }
    else if (m_MapEditorButton->IsMouseOver(mousePos))
    {
        m_MapEditorButton->SetTexture(m_MapEditorButtonHoverTexture);
    }
    else if (m_ExitButton->IsMouseOver(mousePos))
    {
        m_ExitButton->SetTexture(m_ExitButtonHoverTexture);
    }
    else
    {
        SetButtonDefaultTexture();
    }
}

void MainMenuDriver::HandleButtonClicked(Vector2f mousePos)
{
    if (m_ChooseMapButton->IsMouseOver(mousePos))
    {
        m_ChooseMapButton->SetTexture(m_ChooseMapButtonPressedTexture);
    }
    else if (m_MapEditorButton->IsMouseOver(mousePos))
    {
        m_MapEditorButton->SetTexture(m_MapEditorButtonPressedTexture);
    }
    else if (m_ExitButton->IsMouseOver(mousePos))
    {
        m_ExitButton->SetTexture(m_ExitButtonPressedTexture);
    }
    else
    {
        SetButtonDefaultTexture();
    }
}

void MainMenuDriver::SetButtonDefaultTexture()
{
    m_ChooseMapButton->SetTexture(m_ChooseMapButtonTexture);
    m_MapEditorButton->SetTexture(m_MapEditorButtonTexture);
    m_ExitButton->SetTexture(m_ExitButtonTexture);
}

void MainMenuDriver::Draw()
{
    m_Window.draw(m_TitleLogo);
    m_Window.draw(m_ChooseMapButton->GetSprite());
    m_Window.draw(m_MapEditorButton->GetSprite());
    m_Window.draw(m_ExitButton->GetSprite());
}
