/**

@file Monster.h

@brief Defines the Monster class with movement, health, and attack mechanics.
*/

#ifndef MONSTER_H
#define MONSTER_H

#include<iostream>
#include "Entity.h"
#include "Monster_Generator.h"
#include "GameEvents.h"
#include "Tower.h"

////////// Monster Class ////////////
/*
**Feel free to make any suggestions

Monsters will have five stats.
    Level
    Health
    Speed
    Strength (Strength impacts the amount of coin it steals from the player once it reaches the exit tile)
    Reward  (Reward is amount of coin the player wins for eliminating the monster)
Monster also has a m_stCurrentPathIndex member variable that keeps track of the index of its current tile it is on.
*/

class Monster : public Entity, public IGameSubject
{
public:
    Monster();
    ~Monster();

    bool CanAttack();  // Checks if the monster is ready to attack
    void Attack(Tower& tower);  // Attacks a nearby tower
    void UpdateAttackCooldown(float deltaTime);  // Updates attack timer

public:
    void AddObserver(IGameObserver* observer) override {
        m_observers.push_back(observer);
    }

    void RemoveObserver(IGameObserver* observer) override {
        m_observers.erase(
            std::remove(m_observers.begin(), m_observers.end(), observer),
            m_observers.end()
        );
    }

    void NotifyStatsChanged() {
        for (auto observer : m_observers) {
            observer->Update(*this);
        }
    }

    size_t GetCurrentPathIndex() const
    {
        return m_stCurrentPathIndex;
    }

    float GetHealth() const
    {
        return m_iHealth;
    }

    float GetMaxHealth() const
    {
        return m_iMaxHealth;
    }

    RectangleShape& GetHealthBar()
    {
        return m_HealthBar;
    }

    float GetSpeed() const
    {
        return m_fSpeed;
    }

    int GetLevel() const
    {
        return m_iLevel;
    }

    int GetDeathFrame() const
    {
        return deathFrame;
    }

    int GetStrength() const
    {
        return m_iStrength;
    }

    int GetReward() const
    {
        return m_iReward;
    }

    int GetMonsterType()
    {
        return 0;
    }

    void SetCurrentPathIndex(size_t newIndex)
    {
        m_stCurrentPathIndex = newIndex;
        NotifyStatsChanged();
    }

    void SetHealth(float newHealth)
    {
        m_iHealth = newHealth;
        NotifyStatsChanged();
    }

    void SetMaxHealth(float newHealth)
    {
        m_iMaxHealth = newHealth;
        NotifyStatsChanged();
    }

    void SetSpeed(float newSpeed)
    {
        m_fSpeed = newSpeed;
        NotifyStatsChanged();
    }

    void SetDeathFrame(int frameNum)
    {
        deathFrame = frameNum;
        NotifyStatsChanged();
    }

    void SetLevel(int newLevel)
    {
        m_iLevel = newLevel;
        NotifyStatsChanged();
    }

    void SetStrength(int newStrength)
    {
        m_iStrength = newStrength;
        NotifyStatsChanged();
    }

    void SetHealthBar(sf::RectangleShape& HealthBar)
    {
        m_HealthBar = HealthBar;
        NotifyStatsChanged();
    }

    void SetReward(int newReward)
    {
        m_iReward = newReward;
        NotifyStatsChanged();
    }

    // void SetMonsterType(Monster_Generator::Type newType)
    // {
    //     m_eMonsterType = newType;
    //     NotifyStatsChanged();
    // }

private:
    std::vector<IGameObserver*> m_observers;    
    sf::RectangleShape m_HealthBar;
    size_t m_stCurrentPathIndex;           // index of the monster's current path
    float m_iHealth;
    float m_iMaxHealth;
    float m_fSpeed;
    int m_iLevel;
    int m_iStrength;                           // Determines the rate that the monster steals coin from the player
    int m_iReward;
    int deathFrame = 0;
    //Monster_Generator::Type m_eMonsterType;

    float m_fAttackCooldown = 2.0f;  // Time between attacks (seconds)
    float m_fTimeSinceLastAttack = 0.0f;  // Time tracker
    float m_fAttackDamage = 10.0f;   // Damage dealt to towers
};

#endif
