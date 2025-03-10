#include "InfoUIView.h"

#include <iostream>

InfoUIView::InfoUIView(sf::RenderWindow& m_Window, Vector2i mapSize, sf::Font& font)
    : m_Window(m_Window)
    , m_MapSize(mapSize)
    , m_Font(font)
{
    LoadFromFile();
    InitializeTowerAssets();
    InitializeTextAssets(); 
    LoadCrossShapeAssets();
}

void InfoUIView::Update(const IGameSubject &subject)
{
    const InfoUI *infoUI = dynamic_cast<const InfoUI *>(&subject);
    if (infoUI)
    {
        auto &data = m_GameSetupSubjects[infoUI];
        data.m_scoreString = infoUI->GetScoreString();
        data.m_levelString = infoUI->GetLevelString();
        data.m_instructionString = infoUI->GetInstructionString();
        data.m_towerDamagStringe = infoUI->GetTowerDamageString();
        data.m_towerCooldownString = infoUI->GetTowerCooldownString();
        data.m_towerRangeString = infoUI->GetTowerRangeString();
        data.m_towerSpeedString = infoUI->GetTowerSpeedString();
        data.m_warningString = infoUI->GetWarningString();
        data.m_modeString = infoUI->GetModeString();
        data.m_woodTowerPriceString = infoUI->GetWoodTowerPriceString();
        data.m_stoneTowerPriceString = infoUI->GetStoneTowerPriceString();
        data.m_gameOverString = infoUI->GetGameOverString();
        data.m_nextRoundString = infoUI->GetNextRoundString();

        data.m_iCurrentLevel = infoUI->GetCurrentLevel();
        data.m_iCurrentWealth = infoUI->GetCurrentWealth();

        data.m_hoverTowerDamage = infoUI->GetHoverTowerDamage();
        data.m_hoverTowerCooldown = infoUI->GetHoverTowerCooldown();
        data.m_hoverTowerRange = infoUI->GetHoverTowerRange();
        data.m_hoverTowerSpeed = infoUI->GetHoverTowerSpeed();

        data.m_DraggedTowerPosition = infoUI->GetDraggedTowerPosition();
        data.m_CrossPosition = infoUI->GetCrossPosition();

        UpdateTextString(data);
    }
}

void InfoUIView::DrawHUD()
{
    //m_Window.draw(m_scoreText);
    m_Window.draw(m_levelText);
    m_Window.draw(m_instructionText);
    m_Window.draw(m_warningText);
    m_Window.draw(m_modeText);
}

void InfoUIView::DrawTowerInfo()
{
    if (!m_isHoveringOnTower)
    {
        m_Window.draw(m_woodTowerPriceText);
        m_Window.draw(m_stoneTowerPriceText);
    } 
    else
    {
        m_Window.draw(m_towerDamageText);
        m_Window.draw(m_towerCooldownText);
        m_Window.draw(m_towerRangeText);
        m_Window.draw(m_towerSpeedText);
    }
}

void InfoUIView::DrawDraggedTower()
{
    m_Window.draw(m_DraggedTower);
}

void InfoUIView::DrawCrossShape()
{
    if (m_isHoveringOnTower)
    {
        m_Window.draw(m_CrossLine1);
        m_Window.draw(m_CrossLine2);
    }
}

void InfoUIView::DrawNextRoundText()
{
    m_Window.draw(m_nextRoundText);
}

void InfoUIView::DrawUpgradeText()
{
    m_Window.draw(m_upgradeText);
}

void InfoUIView::LoadDraggedSprite(Sprite* sprite)
{
    m_DraggedSprite = sprite;
}

void InfoUIView::UpdateDraggedTowerAsset()
{
    m_DraggedTower.SetTexture(*m_DraggedSprite->getTexture());
    m_DraggedTower.SetScale(Vector2f(0.7f, 0.7f));
    FloatRect draggedTowerBounds = m_DraggedTower.GetSprite().getLocalBounds();
    m_DraggedTower.SetOrigin(Vector2f(draggedTowerBounds.width / 2, draggedTowerBounds.height / 2 + 10));
    m_DraggedTower.SetTextureRect(sf::IntRect(0, 0, 70, 100));
}

void InfoUIView::UpdateDraggedTowerPosition(Vector2f position)
{
    m_DraggedTower.SetPosition(position);
}

void InfoUIView::UpdateCrossShapePosition(Vector2f position)
{
    m_CrossLine1.setPosition(position);
    m_CrossLine2.setPosition(position);
}

void InfoUIView::UpdateTextString(InfoUIData& data)
{
    m_scoreText.setString(data.m_scoreString);   // Set text
    FloatRect scoreTextBounds = m_scoreText.getLocalBounds();
    m_scoreText.setOrigin(scoreTextBounds.width / 2, scoreTextBounds.height / 2);

    m_levelText.setString(data.m_levelString);   // Set text
    FloatRect levelTextBounds = m_levelText.getLocalBounds();
    m_levelText.setOrigin(levelTextBounds.width / 2, levelTextBounds.height / 2);

    m_warningText.setString(data.m_warningString);   // Set text
    FloatRect warningTextBounds = m_warningText.getLocalBounds();
    m_warningText.setOrigin(warningTextBounds.width / 2, warningTextBounds.height / 2);
    m_warningText.setFillColor(m_warningTextColor);

    m_woodTowerPriceText.setString(sf::String("Cost: ") + data.m_woodTowerPriceString);   // Set text
    FloatRect woodTowerPriceBounds = m_woodTowerPriceText.getLocalBounds();
    m_woodTowerPriceText.setOrigin(woodTowerPriceBounds.width / 2, woodTowerPriceBounds.height / 2);

    m_stoneTowerPriceText.setString(sf::String("Cost: ") + data.m_stoneTowerPriceString);   // Set text
    FloatRect stoneTowerPriceBounds = m_stoneTowerPriceText.getLocalBounds();
    m_stoneTowerPriceText.setOrigin(stoneTowerPriceBounds.width / 2, stoneTowerPriceBounds.height / 2);

    m_modeText.setString(data.m_modeString);   // Set text
    FloatRect modeTextBounds = m_modeText.getLocalBounds();
    m_modeText.setOrigin(modeTextBounds.width / 2, modeTextBounds.height / 2);

    m_gameOverText.setString(data.m_gameOverString);   // Set text
    FloatRect gameOverTextBounds = m_gameOverText.getLocalBounds();
    m_gameOverText.setOrigin(gameOverTextBounds.width/2, gameOverTextBounds.height/2);

    m_nextRoundText.setString(data.m_nextRoundString);   // Set text
    FloatRect nextRoundTextBounds = m_nextRoundText.getLocalBounds();
    m_nextRoundText.setOrigin(nextRoundTextBounds.width/2, nextRoundTextBounds.height/2);

    m_instructionText.setString(data.m_instructionString);   // Set text
    FloatRect instructionTextBounds = m_instructionText.getLocalBounds();
    m_instructionText.setOrigin(instructionTextBounds.width / 2, instructionTextBounds.height / 2);
    m_instructionText.setFillColor(m_instructionTextColor);     // Set color

    m_towerDamageText.setString(data.m_towerDamagStringe);   // Set text
    FloatRect towerDamageBounds = m_towerDamageText.getLocalBounds();
    m_towerDamageText.setOrigin(towerDamageBounds.width / 2, towerDamageBounds.height / 2);

    m_towerCooldownText.setString(data.m_towerCooldownString);   // Set text
    FloatRect towerCooldownBounds = m_towerCooldownText.getLocalBounds();
    m_towerCooldownText.setOrigin(towerCooldownBounds.width / 2, towerCooldownBounds.height / 2);

    m_towerRangeText.setString(data.m_towerRangeString);   // Set text
    FloatRect towerRangeBounds = m_towerRangeText.getLocalBounds();
    m_towerRangeText.setOrigin(towerRangeBounds.width / 2, towerRangeBounds.height / 2);

    m_towerSpeedText.setString(data.m_towerSpeedString);   // Set text
    FloatRect towerSpeedBounds = m_towerSpeedText.getLocalBounds();
    m_towerSpeedText.setOrigin(towerSpeedBounds.width / 2, towerSpeedBounds.height / 2);

    m_upgradeText.setString(data.m_upgradeString);   // Set text
}

void InfoUIView::UpdateUpgradeTextPosition(Vector2f position)
{
    m_upgradeText.setPosition(position);
}

void InfoUIView::LoadFromFile()
{
    #ifdef LINUX
    m_towerTexture1.loadFromFile("../src/Images/Tower1_Frame_1.png");
    m_towerTexture2.loadFromFile("../src/Images/Tower2_Frame_1.png");
    #endif
    #ifdef MAC
    m_towerTexture1.loadFromFile("Images/Tower1_Frame_1.png");
    m_towerTexture2.loadFromFile("Images/Tower2_Frame_1.png");
    #endif
}

void InfoUIView::InitializeTowerAssets()
{
    Tower tower1;
    tower1.SetTexture(m_towerTexture1);
    tower1.SetScale(Vector2f(0.7f, 0.7f));
    FloatRect tower1Bounds = tower1.GetSprite().getLocalBounds(); // Assuming getSprite() returns an sf::Sprite reference
    tower1.SetOrigin(Vector2f(tower1Bounds.width / 2, tower1Bounds.height / 2));
    tower1.SetTextureRect(sf::IntRect(0,0,70,100));
    tower1.SetPosition(Vector2f(m_MapSize.x + 100, m_MapSize.y/3 + 75));
    a_TowerMenu.push_back(tower1);

    Tower tower2;
    tower2.SetTexture(m_towerTexture2);
    FloatRect tower2Bounds = tower2.GetSprite().getLocalBounds(); // Assuming getSprite() returns an sf::Sprite reference
    tower2.SetOrigin(Vector2f(tower2Bounds.width / 2, tower2Bounds.height / 2));
    tower2.SetScale(Vector2f(0.7f, 0.7f));
    tower2.SetTextureRect(sf::IntRect(0,0,70,100));
    tower2.SetPosition(Vector2f(m_MapSize.x + 200, m_MapSize.y/3 + 75));
    a_TowerMenu.push_back(tower2);

}

void InfoUIView::InitializeTextAssets()
{

    Vector2f scoreTextPosition = Vector2f(m_MapSize.x + 150, m_MapSize.y/10 + 10);
    Vector2f levelTextPosition = Vector2f(m_MapSize.x + 150, m_MapSize.y/10 + 35);
    Vector2f instructionTextPosition = Vector2f(m_MapSize.x + 150, m_MapSize.y/10 + 135);
    Vector2f warningTextPosition = Vector2f(m_MapSize.x + 150, m_MapSize.y - 30);
    Vector2f modeTextPosition = Vector2f(m_MapSize.x + 150, m_MapSize.y/10 + 65);
    Vector2f woodTowerPricePosition = Vector2f(m_MapSize.x + 100, m_MapSize.y/3 + 125);
    Vector2f stoneTowerPricePosition = Vector2f(m_MapSize.x + 200, m_MapSize.y/3 + 125);
    Vector2f gameOverTextPosition = Vector2f(m_MapSize.x/2, m_MapSize.y/2);
    Vector2f towerDamagePosition = Vector2f(m_MapSize.x + 150, m_MapSize.y/10 + 170);
    Vector2f towerCooldownPosition = Vector2f(m_MapSize.x + 150, m_MapSize.y/10 + 200);
    Vector2f towerRangePosition = Vector2f(m_MapSize.x + 150, m_MapSize.y/10 + 230);
    Vector2f towerSpeedPosition = Vector2f(m_MapSize.x + 150, m_MapSize.y/10 + 260);
    Vector2f nextRoundTextPosition = Vector2f(m_MapSize.x + 230, m_MapSize.y/10 + 110); //Fix this because it should be the same values as instruciton but its not

    // Score text 
    m_scoreText.setFont(m_Font);               // Set font
    m_scoreText.setCharacterSize(25);        // Set size
    m_scoreText.setFillColor(Color::Red);     // Set color
    m_scoreText.setPosition(scoreTextPosition);       // Set position

    // Level text 
    m_levelText.setFont(m_Font);               // Set font
    m_levelText.setCharacterSize(25);        // Set size
    m_levelText.setFillColor(Color::Red);     // Set color
    m_levelText.setPosition(levelTextPosition);       // Set position

    // Warning text 
    m_warningText.setFont(m_Font);               // Set font
    m_warningText.setCharacterSize(15);        // Set size
    m_warningText.setPosition(warningTextPosition);       // Set position

    // Wood tower price
    m_woodTowerPriceText.setFont(m_Font);               // Set font
    m_woodTowerPriceText.setCharacterSize(12);        // Set size
    m_woodTowerPriceText.setPosition(woodTowerPricePosition);       // Set position

    // Stone tower price
    m_stoneTowerPriceText.setFont(m_Font);               // Set font
    m_stoneTowerPriceText.setCharacterSize(12);        // Set size
    m_stoneTowerPriceText.setPosition(stoneTowerPricePosition);       // Set position

    // Current mode text 
    m_modeText.setFont(m_Font);               // Set font
    m_modeText.setCharacterSize(18);        // Set size
    m_modeText.setFillColor(Color::Red);     // Set color
    m_modeText.setPosition(modeTextPosition);       // Set position

    // Game Over text 
    m_gameOverText.setFont(m_Font);               // Set font
    m_gameOverText.setCharacterSize(55);        // Set size
    m_gameOverText.setFillColor(Color::Red);     // Set color
    m_gameOverText.setPosition(gameOverTextPosition);       // Set position

    // Next Round text 
    m_nextRoundText.setFont(m_Font);               // Set font
    m_nextRoundText.setCharacterSize(15);        // Set size
    m_nextRoundText.setFillColor(Color::Green);     // Set color
    m_nextRoundText.setPosition(nextRoundTextPosition);       // Set position

    // instruction text 
    m_instructionText.setFont(m_Font);               // Set font
    m_instructionText.setCharacterSize(20);        // Set size
    m_instructionText.setPosition(instructionTextPosition);       // Set position

    // Damage text 
    m_towerDamageText.setFont(m_Font);               // Set font
    m_towerDamageText.setCharacterSize(15);        // Set size
    m_towerDamageText.setPosition(towerDamagePosition);       // Set position

    // Cooldown text 
    m_towerCooldownText.setFont(m_Font);               // Set font
    m_towerCooldownText.setCharacterSize(15);        // Set size
    m_towerCooldownText.setPosition(towerCooldownPosition);       // Set position

    // Range text 
    m_towerRangeText.setFont(m_Font);               // Set font
    m_towerRangeText.setCharacterSize(15);        // Set size
    m_towerRangeText.setPosition(towerRangePosition);       // Set position

    // Speed text 
    m_towerSpeedText.setFont(m_Font);               // Set font
    m_towerSpeedText.setCharacterSize(15);        // Set size
    m_towerSpeedText.setPosition(towerSpeedPosition);       // Set position

    // Upgrade text
    m_upgradeText.setFont(m_Font);
    m_upgradeText.setCharacterSize(15);
    m_upgradeText.setFillColor(Color::White);
}

void InfoUIView::LoadCrossShapeAssets()
{
    m_LineThickness = 6.0f;     // Thickness of X
    m_LineLength = 30.0f;       // Length of each line in X

    // Set the size of the cross lines
    m_CrossLine1.setSize(sf::Vector2f(m_LineLength, m_LineThickness)); // Horizontal line
    m_CrossLine2.setSize(sf::Vector2f(m_LineLength, m_LineThickness)); // Vertical line

    // Set colors
    m_CrossLine1.setFillColor(sf::Color::Red);
    m_CrossLine2.setFillColor(sf::Color::Red);

    // Set origins to center of each line (half of its length and thickness)
    m_CrossLine1.setOrigin(m_LineLength / 2, m_LineThickness / 2);
    m_CrossLine2.setOrigin(m_LineLength / 2, m_LineThickness / 2);

    // Set rotations (diagonal lines)
    m_CrossLine1.setRotation(45);  // Diagonal top-left to bottom-right
    m_CrossLine2.setRotation(-45); // Diagonal top-right to bottom-left
}
