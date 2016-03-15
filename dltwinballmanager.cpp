#include "dltwinballmanager.h"

DLTWINBallManager::DLTWINBallManager(QObject* parent)
    :QObject(parent)
{
    this->m_nwm = new NetworkManager(this);
}

// init
bool DLTWINBallManager::init()
{
    // start to fectch the recent win ball from web
    this->m_nwm->load_recent_balls();
    return true;
}

void DLTWINBallManager::loadLocalWinBallData()
{

}

void DLTWINBallManager::loadSuggestBallData()
{

}

bool DLTWINBallManager::check4FetchWinBallDataFromWeb()
{

}

void DLTWINBallManager::handleFetchRecentWinBallsDataFinished()
{
    qDebug() << "fetch Recent Win ball finished";
}

void DLTWINBallManager::handleFetchRecentWinBallsDataError()
{
    qDebug() << "fetch Recent Win ball falied";
}

