#ifndef GAMESETUPVIEW_H
#define GAMESETUPVIEW_H

#include "../GameEvents.h"

#include <unordered_map> 

class GameSetupView : public IGameObserver
{
public:
    GameSetupView();
    ~GameSetupView() = default;

private:
    struct GameSetupData {
        std::string m_IntroTitle;
        std::string m_EnterSizeSign;
        std::string m_UserInputWindowHeight;
        std::string m_UserInputWindowWidth;
        std::string m_SizeLimitWarning;
    };

    std::unordered_map<const Tower*, GameSetupData> m_GameSetupSubjects;

};

#endif // GAMESETUPVIEW_H