
#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "GameSetup.h"
#include "../Views/GameSetupView.h"


class GUIManager
{
public:
    GUIManager() = default;
    ~GUIManager() = default;

    void InitializeGameSetup();
private:
    
    GameSetup *m_gameSetup;
    GameSetupView *m_gameSetupView;
};



#endif // GUIMANAGER_H