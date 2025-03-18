#ifndef INFOUI_H
#define INFOUI_H

#include "../GameEvents.h"
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

    std::string m_towerLevelString;
    std::string m_towerDamagStringe;
    std::string m_towerCooldownString;
    std::string m_towerRangeString;
    std::string m_towerSpeedString;
    std::string m_towerUpgradeCostString;
    std::string m_towerInstructionString_1;
    std::string m_towerInstructionString_2;

    std::string m_warningString;
    std::string m_modeString;
    std::string m_woodTowerPriceString;
    std::string m_stoneTowerPriceString;
    std::string m_gameOverString1;
    std::string m_gameOverString2;
    std::string m_gameOverString3;
    std::string m_nextRoundString;
    std::string m_upgradeString;

    int m_iCurrentLevel;
    int m_iCurrentWealth;

    int m_hoverTowerLevel;
    float m_hoverTowerDamage;
    float m_hoverTowerCooldown;
    float m_hoverTowerRange;
    float m_hoverTowerSpeed;
    int m_hoverTowerUpgradeCost;

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

    void SetModeString(const String& mode) {
        m_modeString = mode;
        notifyObservers();
    }

    void SetWoodTowerPriceString(const String& price) {
        m_woodTowerPriceString = price;
        notifyObservers();
    }

    void SetStoneTowerPriceString(const String& price) {
        m_stoneTowerPriceString = price;
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

    void SetNextRoundString(const String& nextRound) {
        m_nextRoundString = nextRound;
        notifyObservers();
    }

    void SetUpgradeString(const String& upgrade) {
        m_upgradeString = upgrade;
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

    void SetHoverTowerLevel(int level) {
        m_hoverTowerLevel = level;
        SetTowerLevelString("Tower Level: " + std::to_string(level));
    }

    void SetHoverTowerDamage(float damage) {
        m_hoverTowerDamage = damage;

        // format to 2 decimal places
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << damage;
        std::string s = ss.str();

        SetTowerDamageString("Damage: " + s);
    }

    void SetHoverTowerCooldown(float cooldown) {
        m_hoverTowerCooldown = cooldown;

        // format to 2 decimal places
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << cooldown;
        std::string s = ss.str();

        SetTowerCooldownString("Cooldown: " + s);
    }  

    void SetHoverTowerRange(float range) {
        m_hoverTowerRange = range;

        // format to 2 decimal places
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << range;
        std::string s = ss.str();

        SetTowerRangeString("Range: " + s);
    }

    void SetHoverTowerSpeed(float speed) {
        m_hoverTowerSpeed = speed;

        // format to 2 decimal places
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << speed;
        std::string s = ss.str();

        SetTowerSpeedString("Fire Rate: " + s);
    }

    void SetHoverTowerUpgradeCost(int cost) {
        m_hoverTowerUpgradeCost = cost;
        SetTowerUpgradeCostString("Upgrade Cost: " + std::to_string(cost));
    }

    void SetCrossPosition(Vector2f position) {
        m_CrossPosition = position;
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

    const std::string& GetModeString() const {
        return m_modeString;
    }

    const std::string& GetWoodTowerPriceString() const {
        return m_woodTowerPriceString;
    }

    const std::string& GetStoneTowerPriceString() const {
        return m_stoneTowerPriceString;
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

    const std::string& GetNextRoundString() const {
        return m_nextRoundString;
    }

    const std::string& GetUpgradeString() const {
        return m_upgradeString;
    }

    int GetCurrentLevel() const {
        return m_iCurrentLevel;
    }

    int GetCurrentWealth() const {
        return m_iCurrentWealth;
    }

    float GetHoverTowerDamage() const {
        return m_hoverTowerDamage;
    }

    float GetHoverTowerCooldown() const {
        return m_hoverTowerCooldown;
    }

    float GetHoverTowerRange() const {
        return m_hoverTowerRange;
    } 

    float GetHoverTowerSpeed() const {
        return m_hoverTowerSpeed;
    }

    Vector2f GetCrossPosition() const {
        return m_CrossPosition;
    }

    Clock& GetWarningShown() {
        return m_warningShown;
    }


};

#endif // INFOUI_H