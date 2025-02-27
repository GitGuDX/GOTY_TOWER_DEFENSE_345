#include "GUIManager.h"

void GUIManager::InitializeGameSetup()
{
    m_gameSetup = new GameSetup();
    //m_gameSetupView = new GameSetupView(m_gameSetup);
    //m_gameSetup->AddObserver(this);
    m_gameSetup->SetIntroTitle("Welcome to Tower Defense!");
    m_gameSetup->SetEnterSizeSign("Enter the size of the grid:");
    m_gameSetup->SetUserInputWindowHeight("Height: ");
    m_gameSetup->SetUserInputWindowWidth("Width: ");
    m_gameSetup->SetSizeLimitWarning("Size must be between 5 and 20.");
}