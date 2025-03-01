#ifndef INFOUI_H
#define INFOUI_H

#include "../GameEvents.h"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <algorithm>

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
    Vector2f m_CrossPosition; // Center the X at the hovered tower

    Clock m_warningShown;

public:

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

    void SetGameOverString(const String& gameOver) {
        m_gameOverString = gameOver;
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
        SetLevelString("Score: " + std::to_string(level));
        notifyObservers();
    }

    void SetCurrentWealth(int wealth) {
        m_iCurrentWealth = wealth;
        SetScoreString("Score: " + std::to_string(wealth));
        notifyObservers();
    }

    void SetHoverTowerDamage(float damage) {
        m_hoverTowerDamage = damage;
        SetTowerDamageString("Damage: " + std::to_string(damage));
        notifyObservers();
    }

    void SetHoverTowerCooldown(float cooldown) {
        m_hoverTowerCooldown = cooldown;
        SetTowerCooldownString("Cooldown: " + std::to_string(cooldown));
        notifyObservers();
    }  

    void SetHoverTowerRange(float range) {
        m_hoverTowerRange = range;
        SetTowerRangeString("Range: " + std::to_string(range));
        notifyObservers();
    }

    void SetHoverTowerSpeed(float speed) {
        m_hoverTowerSpeed = speed;
        SetTowerSpeedString("Speed: " + std::to_string(speed));
        notifyObservers();
    }

    void SetDraggedTowerPosition(Vector2f position) {
        m_DraggedTowerPosition = position;
        notifyObservers();
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

    const std::string& GetGameOverString() const {
        return m_gameOverString;
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

    Vector2f GetDraggedTowerPosition() const {
        return m_DraggedTowerPosition;
    }

    Vector2f GetCrossPosition() const {
        return m_CrossPosition;
    }

    Clock& GetWarningShown() {
        return m_warningShown;
    }
};

#endif // INFOUI_H