#ifndef INFOUI_H
#define INFOUI_H

#include "../GameEvents.h"
#include "../Generators/TowerGeneratorData.h"   
#include <SFML/Graphics.hpp>

#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>


using namespace sf;

class InfoUI : public IGameSubject
{

public:
    InfoUI();
    ~InfoUI() = default;

    void AddObserver(IGameObserver* observer) override {
        m_observers.push_back(observer);
    }

    void RemoveObserver(IGameObserver* observer) override {
        m_observers.erase(
            std::remove(m_observers.begin(), m_observers.end(), observer),
            m_observers.end()
        );
    }

    void InitializeInfoUI();

private:
    void notifyObservers() {
        for (auto observer : m_observers) {
            observer->Update(*this);
        }
    }

private:
    std::vector<IGameObserver*> m_observers;

    int m_InfoUIWidth;

    std::string m_scoreString;
    std::string m_levelString;
    std::string m_instructionString;

    std::string m_TowerSelectionTitleString;
    std::string m_towerNameString;
    std::string m_towerLevelString;
    std::string m_towerDamagStringe;
    std::string m_towerCooldownString;
    std::string m_towerRangeString;
    std::string m_towerSpeedString;
    std::string m_towerUpgradeCostString;
    std::string m_towerEffectString;
    std::string m_towerInstructionString_1;
    std::string m_towerInstructionString_2;

    //std::string m_modeString;
    std::string m_woodTowerPriceString;
    std::string m_stoneTowerPriceString;
    std::string m_FlameThrowerTowerPriceString;
    std::string m_upgradeString;
    
    std::string m_gameOverString1;
    std::string m_gameOverString2;
    std::string m_gameOverString3;

    std::string m_nextMonsterTitleString;
    std::string m_nextMonsterLevelString;
    std::string m_nextMonsterDescriptionString;

    std::string m_warningString;


    int m_iCurrentLevel;
    int m_iCurrentWealth;

    Vector2f m_CrossPosition; // Center the X at the hovered tower

    Clock m_warningShown;

public:
    int GetInfoUIWidth() const {
        return m_InfoUIWidth;
    }

    void SetScoreString(const String& score) {
        m_scoreString = score;
        notifyObservers();
    }

    void SetLevelString(const String& level) {
        m_levelString = level;
        notifyObservers();
    }

    void SetInstructionString(const String& instruction) {
        m_instructionString = instruction;
        notifyObservers();
    }

    void SetTowerNameString(const String& name) {
        m_towerNameString = name;
        notifyObservers();
    }

    void SetTowerLevelString(const String& level) {
        m_towerLevelString = level;
        notifyObservers();
    }

    void SetTowerDamageString(const String& damage) {
        m_towerDamagStringe = damage;
        notifyObservers();
    }

    void SetTowerCooldownString(const String& cooldown) {
        m_towerCooldownString = cooldown;
        notifyObservers();
    }

    void SetTowerRangeString(const String& range) {
        m_towerRangeString = range;
        notifyObservers();
    }

    void SetTowerSpeedString(const String& speed) {
        m_towerSpeedString = speed;
        notifyObservers();
    }   

    void SetTowerUpgradeCostString(const String& cost) {
        m_towerUpgradeCostString = cost;
        notifyObservers();
    }

    void SetTowerInstructionString_1(const String& instruction) {
        m_towerInstructionString_1 = instruction;
        notifyObservers();
    }

    void SetTowerInstructionString_2(const String& instruction) {
        m_towerInstructionString_2 = instruction;
        notifyObservers();
    }

    void SetWarningString(const String& warning) {
        m_warningString = warning;
        notifyObservers();
    }

    // void SetModeString(const String& mode) {
    //     m_modeString = mode;
    //     notifyObservers();
    // }

    void SetWoodTowerPriceString(const String& price) {
        m_woodTowerPriceString = price;
        notifyObservers();
    }

    void SetStoneTowerPriceString(const String& price) {
        m_stoneTowerPriceString = price;
        notifyObservers();
    }

    void SetFlameThrowerTowerPriceString(const String& price) {
        m_FlameThrowerTowerPriceString = price;
        notifyObservers();
    }

    void SetGameOverString1(const String& gameOver) {
        m_gameOverString1 = gameOver;
        notifyObservers();
    }

    void SetGameOverString2(const String& gameOver) {
        m_gameOverString2 = gameOver;
        notifyObservers();
    }

    void SetGameOverString3(const String& gameOver) {
        m_gameOverString3 = gameOver;
        notifyObservers();
    }

    void SetTowerSelectionTitleString(const String& towerSelectionTitle) {
        m_TowerSelectionTitleString = towerSelectionTitle;
        notifyObservers();
    }

    void SetUpgradeString(const String& upgrade) {
        m_upgradeString = upgrade;
        notifyObservers();
    }

    void SetEffectString(const String& effect) {
        m_towerEffectString = effect;
        notifyObservers();
    }

    void SetCurrentLevel(int level) {
        m_iCurrentLevel = level;
        SetLevelString("Level: " + std::to_string(level));
    }

    void SetCurrentWealth(int wealth) {
        m_iCurrentWealth = wealth;
        SetScoreString("Score: " + std::to_string(wealth));
    }

    void SetHoverTowerName(TowerGeneratorData::TowerType type) {
        switch (type)
        {
            case (TowerGeneratorData::TowerType::FlameThrower):
                SetTowerNameString("Flame Thrower Tower");
                break;
            case (TowerGeneratorData::TowerType::Sniper):
                SetTowerNameString("Sniper Tower");
                break;
            case (TowerGeneratorData::TowerType::Rapid):
                SetTowerNameString("Rapid Tower");
                break;
            default:
                SetTowerNameString("No Type Tower");
                break;
        }
    }

    void SetHoverTowerLevel(int level) {
        SetTowerLevelString("Level: " + std::to_string(level));
    }

    void SetHoverTowerDamage(float damage) {
        // format to 2 decimal places
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << damage;
        std::string s = ss.str();

        SetTowerDamageString("Damage: " + s);
    }

    void SetHoverTowerCooldown(float cooldown) {
        // format to 2 decimal places
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << cooldown;
        std::string s = ss.str();

        SetTowerCooldownString("Cooldown: " + s);
    }  

    void SetHoverTowerRange(float range) {
        // format to 2 decimal places
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << range;
        std::string s = ss.str();

        SetTowerRangeString("Range: " + s);
    }

    void SetHoverTowerSpeed(float speed) {
        // format to 2 decimal places
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << speed;
        std::string s = ss.str();

        SetTowerSpeedString("Fire Rate: " + s);
    }

    void SetHoverTowerUpgradeCost(int cost) {
        SetTowerUpgradeCostString("Upgrade Cost: " + std::to_string(cost));
    }

    void SetHoverTowerEffect(TowerGeneratorData::TowerType type) {
        switch (type)
        {
            case (TowerGeneratorData::TowerType::FlameThrower):
                SetEffectString("Effect: Burn");
                break;
            case (TowerGeneratorData::TowerType::Sniper):
                SetEffectString("Effect: Slow");
                break;
            case (TowerGeneratorData::TowerType::Rapid):
                SetEffectString("Effect: None");
                break;
            default:
                SetEffectString("Effect: None");
                break;
        }
    }

    void SetCrossPosition(Vector2f position) {
        m_CrossPosition = position;
        notifyObservers();
    }

    void SetNextMonsterTitleString(const String& title) {
        m_nextMonsterTitleString = title;
        notifyObservers();
    }

    void SetNextMonsterLevelString(const String& level) {
        m_nextMonsterLevelString = level;
        notifyObservers();
    }

    void SetNextMonsterDescriptionString(const String& description) {
        m_nextMonsterDescriptionString = description;
        notifyObservers();
    }

    const std::string& GetScoreString() const {
        return m_scoreString;
    }

    const std::string& GetLevelString() const {
        return m_levelString;
    }

    const std::string& GetInstructionString() const {
        return m_instructionString;
    }

    const std::string& GetTowerNameString() const {
        return m_towerNameString;
    }

    const std::string& GetTowerLevelString() const {
        return m_towerLevelString;
    }

    const std::string& GetTowerDamageString() const {
        return m_towerDamagStringe;
    }

    const std::string& GetTowerCooldownString() const {
        return m_towerCooldownString;
    }

    const std::string& GetTowerRangeString() const {
        return m_towerRangeString;
    }

    const std::string& GetTowerSpeedString() const {
        return m_towerSpeedString;
    }

    const std::string& GetTowerUpgradeCostString() const {
        return m_towerUpgradeCostString;
    }

    const std::string& GetTowerInstructionString_1() const {
        return m_towerInstructionString_1;
    }

    const std::string& GetTowerInstructionString_2() const {
        return m_towerInstructionString_2;
    }

    const std::string& GetWarningString() const {
        return m_warningString;
    }

    // const std::string& GetModeString() const {
    //     return m_modeString;
    // }

    const std::string& GetWoodTowerPriceString() const {
        return m_woodTowerPriceString;
    }

    const std::string& GetStoneTowerPriceString() const {
        return m_stoneTowerPriceString;
    }

    const std::string& GetFlameThrowerTowerPriceString() const {
        return m_FlameThrowerTowerPriceString;
    }

    const std::string& GetGameOverString1() const {
        return m_gameOverString1;
    }

    const std::string& GetGameOverString2() const {
        return m_gameOverString2;
    }

    const std::string& GetGameOverString3() const {
        return m_gameOverString3;
    }

    const std::string& GetTowerSelectionTitleString() const {
        return m_TowerSelectionTitleString;
    }

    const std::string& GetUpgradeString() const {
        return m_upgradeString;
    }

    const std::string& GetEffectString() const {
        return m_towerEffectString;
    }

    const std::string& GetNextMonsterTitleString() const {
        return m_nextMonsterTitleString;
    }

    const std::string& GetNextMonsterLevelString() const {
        return m_nextMonsterLevelString;
    }

    const std::string& GetNextMonsterDescriptionString() const {
        return m_nextMonsterDescriptionString;
    }

    int GetCurrentLevel() const {
        return m_iCurrentLevel;
    }

    int GetCurrentWealth() const {
        return m_iCurrentWealth;
    }

    Vector2f GetCrossPosition() const {
        return m_CrossPosition;
    }

    Clock& GetWarningShown() {
        return m_warningShown;
    }
    


};

#endif // INFOUI_H