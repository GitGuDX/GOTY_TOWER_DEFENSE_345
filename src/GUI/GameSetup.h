
#ifndef GAMESETUP_H
#define GAMESETUP_H

#include "../GameEvents.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class GameSetup : public IGameSubject
{
public:
    GameSetup() = default;
    ~GameSetup() = default;

    void AddObserver(IGameObserver* observer) override {
        m_observers.push_back(observer);
    }

    void RemoveObserver(IGameObserver* observer) override {
        m_observers.erase(
            std::remove(m_observers.begin(), m_observers.end(), observer),
            m_observers.end()
        );
    }

    std::string GetIntroTitle() const {
        return m_IntroTitle;
    }

    std::string GetEnterSizeSign() const {
        return m_EnterSizeSign;
    }

    std::string GetUserInputWindowHeight() const {
        return m_UserInputWindowHeight;
    }

    std::string GetUserInputWindowWidth() const {
        return m_UserInputWindowWidth;
    }

    std::string GetSizeLimitWarning() const {
        return m_SizeLimitWarning;
    }

    void SetIntroTitle(std::string title) {
        m_IntroTitle = title;
        notifyObservers();
    }

    void SetEnterSizeSign(std::string sign) {
        m_EnterSizeSign = sign;
        notifyObservers();
    }

    void SetUserInputWindowHeight(std::string height) {
        m_UserInputWindowHeight = height;
        notifyObservers();
    }

    void SetUserInputWindowWidth(std::string width) {
        m_UserInputWindowWidth = width;
        notifyObservers();
    }

    void SetSizeLimitWarning(std::string warning) {
        m_SizeLimitWarning = warning;
        notifyObservers();
    }

    
private:
    void notifyObservers() {
        for (auto observer : m_observers) {

            observer->Update(*this);
        }
    }

private:
    std::vector<IGameObserver*> m_observers;

    std::string m_IntroTitle;
    std::string m_EnterSizeSign;
    std::string m_UserInputWindowHeight;
    std::string m_UserInputWindowWidth;
    std::string m_SizeLimitWarning;


};
#endif // GAMESETUP_H