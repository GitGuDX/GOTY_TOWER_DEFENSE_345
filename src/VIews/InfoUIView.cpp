#include "InfoUIView.h"

#include <iostream>

InfoUIView::InfoUIView(sf::RenderWindow& m_Window, Vector2i mapSize, int infoUIWidth, sf::Font& font)
    : m_Window(m_Window)
    , m_MapSize(mapSize)
    , m_infoUIWidth(infoUIWidth)
    , m_Font(font)
{
    //LoadFromFile();
    //InitializeTowerAssets();
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

        data.m_towerLevelString = infoUI->GetTowerLevelString();
        data.m_towerDamagStringe = infoUI->GetTowerDamageString();
        data.m_towerCooldownString = infoUI->GetTowerCooldownString();
        data.m_towerRangeString = infoUI->GetTowerRangeString();
        data.m_towerSpeedString = infoUI->GetTowerSpeedString();
        data.m_towerUpgradeCostString = infoUI->GetTowerUpgradeCostString();
        data.m_towerEffectString = infoUI->GetEffectString();
        data.m_towerInstructionString_1 = infoUI->GetTowerInstructionString_1();
        data.m_towerInstructionString_2 = infoUI->GetTowerInstructionString_2();

        data.m_nextMonsterTitleString = infoUI->GetNextMonsterTitleString();
        data.m_nextMonsterLevelString = infoUI->GetNextMonsterLevelString();
        data.m_nextMonsterDescriptionString = infoUI->GetNextMonsterDescriptionString();
        
        data.m_warningString = infoUI->GetWarningString();
        data.m_modeString = infoUI->GetModeString();
        data.m_woodTowerPriceString = infoUI->GetWoodTowerPriceString();
        data.m_stoneTowerPriceString = infoUI->GetStoneTowerPriceString();
        data.m_FlameThrowerTowerPriceString = infoUI->GetFlameThrowerTowerPriceString();
        data.m_nextRoundString = infoUI->GetNextRoundString();

        data.m_gameOverString1 = infoUI->GetGameOverString1();
        data.m_gameOverString2 = infoUI->GetGameOverString2();
        data.m_gameOverString3 = infoUI->GetGameOverString3();

        data.m_CrossPosition = infoUI->GetCrossPosition();

        UpdateTextString(data);
    }
}

void InfoUIView::DrawHUD()
{
    m_Window.draw(m_scoreText);
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
        m_Window.draw(m_FlameThrowerTowerPriceText);
        m_Window.draw(m_nextMonsterTitleText);
        m_Window.draw(m_nextMonsterLevelText);
        m_Window.draw(m_nextMonsterDescriptionText);
    } 
    else
    {
        m_Window.draw(m_towerLevelText);
        m_Window.draw(m_towerDamageText);
        m_Window.draw(m_towerCooldownText);
        m_Window.draw(m_towerRangeText);
        m_Window.draw(m_towerSpeedText);
        m_Window.draw(m_towerUpgradeCostText);
        m_Window.draw(m_towerEffectText);
        m_Window.draw(m_towerInstructionText_1);
        m_Window.draw(m_towerInstructionText_2);
    }
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

void InfoUIView::DrawGameOverText()
{
    m_Window.draw(m_gameOverText_1);
    m_Window.draw(m_gameOverText_2);
    m_Window.draw(m_gameOverText_3);
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

    m_FlameThrowerTowerPriceText.setString(sf::String("Cost: ") + data.m_FlameThrowerTowerPriceString);   // Set text
    FloatRect FlameThrowerTowerPriceBounds = m_FlameThrowerTowerPriceText.getLocalBounds();
    m_FlameThrowerTowerPriceText.setOrigin(FlameThrowerTowerPriceBounds.width / 2, FlameThrowerTowerPriceBounds.height / 2);

    m_modeText.setString(data.m_modeString);   // Set text
    FloatRect modeTextBounds = m_modeText.getLocalBounds();
    m_modeText.setOrigin(modeTextBounds.width / 2, modeTextBounds.height / 2);

    m_gameOverText_1.setString(data.m_gameOverString1);   // Set text
    FloatRect gameOverTextBounds_1 = m_gameOverText_1.getLocalBounds();
    m_gameOverText_1.setOrigin(gameOverTextBounds_1.width/2, gameOverTextBounds_1.height/2);

    m_gameOverText_2.setString(data.m_gameOverString2);   // Set text
    FloatRect gameOverTextBounds_2 = m_gameOverText_2.getLocalBounds();
    m_gameOverText_2.setOrigin(gameOverTextBounds_2.width/2, gameOverTextBounds_2.height/2);

    m_gameOverText_3.setString(data.m_gameOverString3);   // Set text
    FloatRect gameOverTextBounds_3 = m_gameOverText_3.getLocalBounds();
    m_gameOverText_3.setOrigin(gameOverTextBounds_3.width/2, gameOverTextBounds_3.height/2);

    m_nextRoundText.setString(data.m_nextRoundString);   // Set text
    FloatRect nextRoundTextBounds = m_nextRoundText.getLocalBounds();
    m_nextRoundText.setOrigin(nextRoundTextBounds.width/2, nextRoundTextBounds.height/2);

    m_instructionText.setString(data.m_instructionString);   // Set text
    FloatRect instructionTextBounds = m_instructionText.getLocalBounds();
    m_instructionText.setOrigin(instructionTextBounds.width / 2, instructionTextBounds.height / 2);
    m_instructionText.setFillColor(m_instructionTextColor);     // Set color

    m_towerLevelText.setString(data.m_towerLevelString);   // Set text
    FloatRect towerLevelBounds = m_towerLevelText.getLocalBounds();
    m_towerLevelText.setOrigin(towerLevelBounds.width / 2, towerLevelBounds.height / 2);

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

    m_towerUpgradeCostText.setString(data.m_towerUpgradeCostString);   // Set text
    FloatRect towerUpgradeCostBounds = m_towerUpgradeCostText.getLocalBounds();
    m_towerUpgradeCostText.setOrigin(towerUpgradeCostBounds.width / 2, towerUpgradeCostBounds.height / 2);

    m_towerEffectText.setString(data.m_towerEffectString);   // Set text
    FloatRect towerEffectBounds = m_towerEffectText.getLocalBounds();
    m_towerEffectText.setOrigin(towerEffectBounds.width / 2, towerEffectBounds.height / 2);

    m_towerInstructionText_1.setString(data.m_towerInstructionString_1);   // Set text
    FloatRect towerInstructionBounds_1 = m_towerInstructionText_1.getLocalBounds();
    m_towerInstructionText_1.setOrigin(towerInstructionBounds_1.width / 2, towerInstructionBounds_1.height / 2);

    m_towerInstructionText_2.setString(data.m_towerInstructionString_2);   // Set text
    FloatRect towerInstructionBounds_2 = m_towerInstructionText_2.getLocalBounds();
    m_towerInstructionText_2.setOrigin(towerInstructionBounds_2.width / 2, towerInstructionBounds_2.height / 2);

    m_nextMonsterTitleText.setString(data.m_nextMonsterTitleString);   // Set text
    FloatRect nextMonsterTitleBounds = m_nextMonsterTitleText.getLocalBounds();
    m_nextMonsterTitleText.setOrigin(nextMonsterTitleBounds.width / 2, nextMonsterTitleBounds.height / 2);

    m_nextMonsterLevelText.setString(data.m_nextMonsterLevelString);   // Set text
    FloatRect nextMonsterLevelBounds = m_nextMonsterLevelText.getLocalBounds();
    m_nextMonsterLevelText.setOrigin(nextMonsterLevelBounds.width / 2, nextMonsterLevelBounds.height / 2);

    m_nextMonsterDescriptionText.setString(data.m_nextMonsterDescriptionString);   // Set text
    FloatRect nextMonsterDescriptionBounds = m_nextMonsterDescriptionText.getLocalBounds();
    m_nextMonsterDescriptionText.setOrigin(nextMonsterDescriptionBounds.width / 2, nextMonsterDescriptionBounds.height / 2);
}

void InfoUIView::UpdateUpgradeTextPosition(Vector2f position)
{
    m_upgradeText.setPosition(position);
}

void InfoUIView::InitializeTextAssets()
{

    Vector2f scoreTextPosition = Vector2f(m_MapSize.x + m_infoUIWidth/2, m_MapSize.y/10 + 10);
    Vector2f levelTextPosition = Vector2f(m_MapSize.x + m_infoUIWidth/2, m_MapSize.y/10 + 35);
    Vector2f instructionTextPosition = Vector2f(m_MapSize.x + m_infoUIWidth/2, m_MapSize.y/10 + 115);
    Vector2f warningTextPosition = Vector2f(m_MapSize.x + m_infoUIWidth/2, m_MapSize.y - 30);
    Vector2f modeTextPosition = Vector2f(m_MapSize.x + m_infoUIWidth/2, m_MapSize.y/10 + 65);
    Vector2f woodTowerPricePosition = Vector2f(m_MapSize.x + m_infoUIWidth*1/4, m_MapSize.y/3 + 125);
    Vector2f stoneTowerPricePosition = Vector2f(m_MapSize.x + m_infoUIWidth*2/4, m_MapSize.y/3 + 125);
    Vector2f FlameThrowerTowerPricePosition = Vector2f(m_MapSize.x + m_infoUIWidth*1/4 + 200, m_MapSize.y/3 + 125);
    Vector2f gameOverTextPosition1 = Vector2f(m_MapSize.x/2, m_MapSize.y/2 - 30);
    Vector2f gameOverTextPosition2 = Vector2f(m_MapSize.x/2, m_MapSize.y/2);
    Vector2f gameOverTextPosition3 = Vector2f(m_MapSize.x/2, m_MapSize.y/2 + 30);

    Vector2f towerLevelPosition = Vector2f(m_MapSize.x + m_infoUIWidth/2, m_MapSize.y/10 + 145);
    Vector2f towerDamagePosition = Vector2f(m_MapSize.x + m_infoUIWidth/2, m_MapSize.y/10 + 175);
    Vector2f towerCooldownPosition = Vector2f(m_MapSize.x + m_infoUIWidth/2, m_MapSize.y/10 + 205);
    Vector2f towerRangePosition = Vector2f(m_MapSize.x + m_infoUIWidth/2, m_MapSize.y/10 + 235);
    Vector2f towerSpeedPosition = Vector2f(m_MapSize.x + m_infoUIWidth/2, m_MapSize.y/10 + 265);
    Vector2f towerUpgradeCostPosition = Vector2f(m_MapSize.x + m_infoUIWidth/2, m_MapSize.y/10 + 295);
    Vector2f towerEffectPosition = Vector2f(m_MapSize.x + m_infoUIWidth/2, m_MapSize.y/10 + 325);
    Vector2f towerInstructionPosition_1 = Vector2f(m_MapSize.x + m_infoUIWidth/2, m_MapSize.y/10 + 360);
    Vector2f towerInstructionPosition_2 = Vector2f(m_MapSize.x + m_infoUIWidth/2, m_MapSize.y/10 + 390);

    Vector2f nextMonsterTitlePosition = Vector2f(m_MapSize.x + m_infoUIWidth/2, m_MapSize.y / 3 + 165);
    Vector2f nextMonsterLevelPosition = Vector2f(m_MapSize.x + m_infoUIWidth/2, m_MapSize.y / 3 + 245);
    Vector2f nextMonsterDescriptionPosition = Vector2f(m_MapSize.x + m_infoUIWidth/2, m_MapSize.y / 3 + 270);

    Vector2f nextRoundTextPosition = Vector2f(m_MapSize.x + m_infoUIWidth/2, m_MapSize.y/10 + 80); //Fix this because it should be the same values as instruciton but its not

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
    m_warningText.setCharacterSize(16);        // Set size
    m_warningText.setPosition(warningTextPosition);       // Set position

    // Wood tower price
    m_woodTowerPriceText.setFont(m_Font);               // Set font
    m_woodTowerPriceText.setCharacterSize(12);        // Set size
    m_woodTowerPriceText.setPosition(woodTowerPricePosition);       // Set position

    // Stone tower price
    m_stoneTowerPriceText.setFont(m_Font);               // Set font
    m_stoneTowerPriceText.setCharacterSize(12);        // Set size
    m_stoneTowerPriceText.setPosition(stoneTowerPricePosition);       // Set position

    m_FlameThrowerTowerPriceText.setFont(m_Font);               // Set font
    m_FlameThrowerTowerPriceText.setCharacterSize(12);        // Set size
    m_FlameThrowerTowerPriceText.setPosition(FlameThrowerTowerPricePosition);       // Set position

    // Current mode text 
    m_modeText.setFont(m_Font);               // Set font
    m_modeText.setCharacterSize(18);        // Set size
    m_modeText.setFillColor(Color::Red);     // Set color
    m_modeText.setPosition(modeTextPosition);       // Set position

    // Game Over text 
    m_gameOverText_1.setFont(m_Font);               // Set font
    m_gameOverText_1.setCharacterSize(25);        // Set size
    m_gameOverText_1.setFillColor(Color::Red);     // Set color
    m_gameOverText_1.setOutlineColor(Color::White);
    m_gameOverText_1.setOutlineThickness(3);
    m_gameOverText_1.setPosition(gameOverTextPosition1);       // Set position

    m_gameOverText_2.setFont(m_Font);               // Set font
    m_gameOverText_2.setCharacterSize(20);        // Set size
    m_gameOverText_2.setFillColor(Color::Red);     // Set color
    m_gameOverText_2.setOutlineColor(Color::White);
    m_gameOverText_2.setOutlineThickness(3);
    m_gameOverText_2.setPosition(gameOverTextPosition2);       // Set position

    m_gameOverText_3.setFont(m_Font);               // Set font
    m_gameOverText_3.setCharacterSize(20);        // Set size
    m_gameOverText_3.setFillColor(Color::Red);     // Set color
    m_gameOverText_3.setOutlineColor(Color::White);
    m_gameOverText_3.setOutlineThickness(3);
    m_gameOverText_3.setPosition(gameOverTextPosition3);       // Set position

    // Next Round text 
    m_nextRoundText.setFont(m_Font);               // Set font
    m_nextRoundText.setCharacterSize(20);        // Set size
    m_nextRoundText.setFillColor(Color::Green);     // Set color
    m_nextRoundText.setPosition(nextRoundTextPosition);       // Set position

    // instruction text 
    m_instructionText.setFont(m_Font);               // Set font
    m_instructionText.setCharacterSize(20);        // Set size
    m_instructionText.setPosition(instructionTextPosition);       // Set position

    // Tower level text
    m_towerLevelText.setFont(m_Font);               // Set font
    m_towerLevelText.setCharacterSize(15);        // Set size
    m_towerLevelText.setPosition(towerLevelPosition);       // Set position

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

    // Upgrade cost text
    m_towerUpgradeCostText.setFont(m_Font);               // Set font
    m_towerUpgradeCostText.setCharacterSize(15);        // Set size
    m_towerUpgradeCostText.setPosition(towerUpgradeCostPosition);       // Set position

    // Tower effect text
    m_towerEffectText.setFont(m_Font);               // Set font
    m_towerEffectText.setCharacterSize(15);        // Set size
    m_towerEffectText.setPosition(towerEffectPosition);       // Set position

    // Tower instruction text 1
    m_towerInstructionText_1.setFont(m_Font);               // Set font
    m_towerInstructionText_1.setCharacterSize(15);        // Set size
    m_towerInstructionText_1.setFillColor(Color::Yellow);
    m_towerInstructionText_1.setPosition(towerInstructionPosition_1);       // Set position

    // Tower instruction text 2
    m_towerInstructionText_2.setFont(m_Font);               // Set font
    m_towerInstructionText_2.setCharacterSize(15);        // Set size
    m_towerInstructionText_2.setFillColor(Color::Yellow);
    m_towerInstructionText_2.setPosition(towerInstructionPosition_2);       // Set position

    m_nextMonsterTitleText.setFont(m_Font);               // Set font
    m_nextMonsterTitleText.setCharacterSize(15);        // Set size
    m_nextMonsterTitleText.setFillColor(Color::White);    
    m_nextMonsterTitleText.setPosition(nextMonsterTitlePosition);       // Set position

    m_nextMonsterLevelText.setFont(m_Font);               // Set font
    m_nextMonsterLevelText.setCharacterSize(15);        // Set size
    m_nextMonsterLevelText.setFillColor(Color::White);
    m_nextMonsterLevelText.setPosition(nextMonsterLevelPosition);       // Set position

    m_nextMonsterDescriptionText.setFont(m_Font);               // Set font
    m_nextMonsterDescriptionText.setCharacterSize(15);        // Set size
    m_nextMonsterDescriptionText.setFillColor(Color::White);
    m_nextMonsterDescriptionText.setPosition(nextMonsterDescriptionPosition);       // Set position

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
