#ifndef INFOUIVIEW_H
#define INFOUIVIEW_H

#include "../Platform.h"
#include "../GameEvents.h"
#include "../GUI/InfoUI.h"
#include "../Tower.h"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <unordered_map> 
#include <vector>

using namespace sf;

class InfoUIView : public IGameObserver
{
private:
    struct InfoUIData
    {
        std::string m_scoreString;
        std::string m_levelString;
        std::string m_instructionString;
        std::string m_towerDamagStringe;
        std::string m_towerCooldownString;
        std::string m_towerRangeString;
        std::string m_towerSpeedString;
        std::string m_warningString;
        std::string m_modeString;
        std::string m_woodTowerPriceString;
        std::string m_stoneTowerPriceString;
        std::string m_gameOverString;
        std::string m_nextRoundString;
        std::string m_upgradeString;

        int m_iCurrentLevel;
        int m_iCurrentWealth;

        float m_hoverTowerDamage;
        float m_hoverTowerCooldown;
        float m_hoverTowerRange;
        float m_hoverTowerSpeed;

        Vector2f m_DraggedTowerPosition;
        Vector2f m_CrossPosition;

    };

public:
    InfoUIView(sf::RenderWindow& m_Window, Vector2i mapSize, sf::Font& font);
    ~InfoUIView() = default;

    void Update(const IGameSubject& subject);

    void DrawHUD();

    void DrawTowerInfo();

    void DrawDraggedTower();

    void DrawCrossShape();

    void DrawNextRoundText();

    void DrawUpgradeText();

    void LoadDraggedSprite(Sprite* sprite);

    void UpdateDraggedTowerAsset();

    void UpdateDraggedTowerPosition(Vector2f position);

    void UpdateCrossShapePosition(Vector2f position);

    void UpdateTextString(InfoUIData& data);

    void UpdateUpgradeTextPosition(Vector2f position);
    
    void LoadFromFile();

    void InitializeTowerAssets();

    void InitializeTextAssets();

    void LoadCrossShapeAssets();

    void SetInstructionTextColor(Color color) {
        m_instructionTextColor = color;
    }

    void SetWarningTextColor(Color color) {
        m_warningTextColor = color;
    }

    void SetHoveringOnTower(bool isHovering) {
        m_isHoveringOnTower = isHovering;
    }

    Sprite* GetDraggedSprite() const {
        return m_DraggedSprite;
    }

    std::vector<Tower>& GetTowerMenu() {
        return a_TowerMenu;
    }

    Tower& GetDraggedTower() {
        return m_DraggedTower;
    }

    Texture& GetTowerTexture1() {
        return m_towerTexture1;
    }

    Texture& GetTowerTexture2() {
        return m_towerTexture2;
    }


private:
    std::unordered_map<const InfoUI*, InfoUIData> m_GameSetupSubjects;

    sf::RenderWindow& m_Window;

    Vector2i m_MapSize;

    sf::Font& m_Font;

    std::vector<Tower> a_TowerMenu;
    Tower m_DraggedTower;

    Sprite* m_DraggedSprite = nullptr;

    Texture m_towerTexture1;
    Texture m_towerTexture2;

    Text m_scoreText;
    Text m_levelText;
    Text m_instructionText;
    Text m_towerDamageText;
    Text m_towerCooldownText;
    Text m_towerRangeText;
    Text m_towerSpeedText;
    Text m_warningText;
    Text m_modeText;
    Text m_woodTowerPriceText;
    Text m_stoneTowerPriceText;
    Text m_gameOverText;
    Text m_nextRoundText;
    Text m_upgradeText;

    Color m_instructionTextColor;
    Color m_warningTextColor;

    RectangleShape m_CrossLine1;
    RectangleShape m_CrossLine2;
    
    float m_LineThickness;     // Thickness of X
    float m_LineLength;       // Length of each line in X

    bool m_isHoveringOnTower = false;
};

#endif // INFOUIVIEW_H