#ifndef MAP_SELECTION_DRIVER_H
#define MAP_SELECTION_DRIVER_H

#include "Button.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

using namespace sf;

class MapSelectionDriver
{
public:
    MapSelectionDriver(RenderWindow& m_Window, Font &font);
    ~MapSelectionDriver() = default;

    void LoadMapSelectionMenuTextures();

    void InitializeMapSelectionAssets();

    void Draw();

    void HandleButtonHover(Vector2f mousePos);

    void HandleButtonClicked(Vector2f mousePos);
    
    void SetButtonDefault();

    Button* GetMediumMapButton()
    {
        return m_MediumMapButton.get();
    }

    Button* GetHardMapButton()
    {
        return m_HardMapButton.get();
    }

    Button* GetBackButton()
    {
        return m_BackButton.get();
    }

private:
    RenderWindow& m_Window;

    Font& m_Font;

    Text m_MapSelectionTitle;

    RectangleShape m_MediumHighlight;
    RectangleShape m_HardHighlight;

    std::unique_ptr<Button> m_MediumMapButton;
    std::unique_ptr<Button> m_HardMapButton;

    Text m_MediumDescription;
    Text m_HardDescription;

    Texture m_MediumMapButtonTexture;
    Texture m_HardMapButtonTexture;

    std::unique_ptr<Button> m_BackButton;

    sf::Texture m_BackButtonTexture;                                    
    sf::Texture m_BackButtonHoverTexture;
    sf::Texture m_BackButtonPressedTexture;  

    bool m_isHoveringMediumMap = false;
    bool m_isHoveringHardMap = false;
};

#endif