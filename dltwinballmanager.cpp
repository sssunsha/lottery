#include "dltwinballmanager.h"

DLTWINBallManager::DLTWINBallManager(QObject* parent)
    :QObject(parent)
{
    this->m_nwm = new NetworkManager(this);
}

// init
bool DLTWINBallManager::init()
{
    return true;
}

void DLTWINBallManager::loadLocalWinBallData()
{

}

void DLTWINBallManager::loadSuggestBallData()
{

}

void DLTWINBallManager::check4FetchWinBallDataFromWeb()
{

}

