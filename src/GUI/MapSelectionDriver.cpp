#include "MapSelectionDriver.h"

MapSelectionDriver::MapSelectionDriver(RenderWindow &m_Window, sf::Font &font)
    : m_Window(m_Window)
    , m_Font(font)
{
}

void MapSelectionDriver::LoadMapSelectionMenuTextures()
{
    m_MediumMapButtonTexture.loadFromFile("../src/Images/Map_Icons/Medium_Map.png");
    m_HardMapButtonTexture.loadFromFile("../src/Images/Map_Icons/Hard_Map.png");

    m_BackButtonTexture.loadFromFile("../src/Images/Buttons/button_back.png");  
    m_BackButtonHoverTexture.loadFromFile("../src/Images/Buttons/button_back_hover.png");                    // placeholder image. Change button image
    m_BackButtonPressedTexture.loadFromFile("../src/Images/Buttons/button_back_pressed.png");
}

void MapSelectionDriver::InitializeMapSelectionAssets()
{
    m_MapSelectionTitle.setFont(m_Font);
    m_MapSelectionTitle.setCharacterSize(40);
    m_MapSelectionTitle.setFillColor(Color::White);
    m_MapSelectionTitle.setPosition(Vector2f(m_Window.getSize().x/2, m_Window.getSize().y/6));
    m_MapSelectionTitle.setString("Choose a Map");
    FloatRect mapSelectionTitleBounds = m_MapSelectionTitle.getLocalBounds();
    m_MapSelectionTitle.setOrigin(mapSelectionTitleBounds.width/2, mapSelectionTitleBounds.height/2);

    m_MediumHighlight.setSize(Vector2f(m_MediumMapButtonTexture.getSize().x + 10, m_MediumMapButtonTexture.getSize().y + 10));
    m_MediumHighlight.setOrigin(m_MediumHighlight.getSize().x/2, m_MediumHighlight.getSize().y/2);
    m_MediumHighlight.setFillColor(Color::White);
    m_MediumHighlight.setPosition(Vector2f(m_Window.getSize().x*1/4, m_Window.getSize().y/2));
    
    m_HardHighlight.setSize(Vector2f(m_HardMapButtonTexture.getSize().x + 10, m_HardMapButtonTexture.getSize().y + 10));
    m_HardHighlight.setOrigin(m_HardHighlight.getSize().x/2, m_HardHighlight.getSize().y/2);
    m_HardHighlight.setFillColor(Color::White);
    m_HardHighlight.setPosition(Vector2f(m_Window.getSize().x*3/4, m_Window.getSize().y/2));

    m_MediumMapButton = std::make_unique<Button>(m_MediumMapButtonTexture, Vector2f(m_Window.getSize().x*1/4, m_Window.getSize().y/2));
    m_MediumMapButton->SetOriginToCenter();

    m_HardMapButton = std::make_unique<Button>(m_HardMapButtonTexture, Vector2f(m_Window.getSize().x*3/4, m_Window.getSize().y/2));
    m_HardMapButton->SetOriginToCenter();

    m_MediumDescription.setFont(m_Font);
    m_MediumDescription.setCharacterSize(20);
    m_MediumDescription.setFillColor(Color::White);
    m_MediumDescription.setPosition(Vector2f(m_Window.getSize().x*1/4, m_Window.getSize().y*6/8));
    m_MediumDescription.setString("Difficulty: Medium");
    FloatRect mediumDescriptionBounds = m_MediumDescription.getLocalBounds();
    m_MediumDescription.setOrigin(mediumDescriptionBounds.width/2, mediumDescriptionBounds.height/2);
    
    m_HardDescription.setFont(m_Font);
    m_HardDescription.setCharacterSize(20);
    m_HardDescription.setFillColor(Color::White);
    m_HardDescription.setPosition(Vector2f(m_Window.getSize().x*3/4, m_Window.getSize().y*6/8));
    m_HardDescription.setString("Difficulty: Hard");
    FloatRect hardDescriptionBounds = m_HardDescription.getLocalBounds();
    m_HardDescription.setOrigin(hardDescriptionBounds.width/2, hardDescriptionBounds.height/2);

    m_BackButton = std::make_unique<Button>(m_BackButtonTexture, Vector2f(m_Window.getSize().x/2,m_Window.getSize().y*5/6));
    m_BackButton->SetScale(Vector2f(0.6f, 0.6f));
    m_BackButton->SetOriginToCenter();
}

void MapSelectionDriver::Draw()
{
    m_Window.draw(m_MapSelectionTitle);

    if (m_isHoveringMediumMap)
    {
        m_Window.draw(m_MediumHighlight);
    }
    else if (m_isHoveringHardMap)
    {
        m_Window.draw(m_HardHighlight);
    }
    
    m_Window.draw(m_MediumMapButton->GetSprite());
    m_Window.draw(m_HardMapButton->GetSprite());

    m_Window.draw(m_MediumDescription);
    m_Window.draw(m_HardDescription);

    m_Window.draw(m_BackButton->GetSprite());
}

void MapSelectionDriver::HandleButtonHover(Vector2f mousePos)
{
    m_MediumHighlight.setFillColor(Color::White);
    m_HardHighlight.setFillColor(Color::White);
    if (m_MediumMapButton->IsMouseOver(mousePos))
    {
        m_isHoveringMediumMap = true;
    }
    else if (m_HardMapButton->IsMouseOver(mousePos))
    {
        m_isHoveringHardMap = true;
    }
    else if (m_BackButton->IsMouseOver(mousePos))
    {
        m_BackButton->SetTexture(m_BackButtonHoverTexture);
    }
    else
    {
        SetButtonDefault();
    }
}

void MapSelectionDriver::HandleButtonClicked(Vector2f mousePos)
{
    if (m_MediumMapButton->IsMouseOver(mousePos))
    {
        m_MediumHighlight.setFillColor(sf::Color(128, 128, 128));
    }
    else if (m_HardMapButton->IsMouseOver(mousePos))
    {
        m_HardHighlight.setFillColor(sf::Color(128, 128, 128));
    }
    else if (m_BackButton->IsMouseOver(mousePos))
    {
        m_BackButton->SetTexture(m_BackButtonPressedTexture);
    }
    else
    {
        SetButtonDefault();
    }
}

void MapSelectionDriver::SetButtonDefault()
{
    m_isHoveringMediumMap = false;
    m_isHoveringHardMap = false;
    
    m_BackButton->SetTexture(m_BackButtonTexture);
}