#include "dltwinballmanager.h"

DLTWINBallManager::DLTWINBallManager(QObject* parent)
    :QObject(parent)
{
    this->m_nwm = new NetworkManager(this);
    this->m_ldm = new LocalDataManager(this);
}

// init
bool DLTWINBallManager::init()
{
    loadLocalWinBallData();
    loadSuggestBallData();
    fetchRecentWinBallDataFromWeb();
    return true;
}

void DLTWINBallManager::loadLocalWinBallData()
{
    this->m_ldm->loadRecentWinBallData();
}

void DLTWINBallManager::loadSuggestBallData()
{
    this->m_ldm->loadSuggestBallData();
}

void DLTWINBallManager::fetchRecentWinBallDataFromWeb()
{
    // start to fectch the recent win ball from web
    this->m_nwm->load_recent_balls();
}

NetworkManager *DLTWINBallManager::getNetWorkManager()
{
        return this->m_nwm;
}

LocalDataManager *DLTWINBallManager::getLocalDataManager()
{
    return this->m_ldm;
}

void DLTWINBallManager::handleFetchRecentWinBallsDataFinished()
{
    qDebug() << "fetch Recent Win ball finished";
}

void DLTWINBallManager::handleFetchRecentWinBallsDataError()
{
    qDebug() << "fetch Recent Win ball falied";
}

void DLTWINBallManager::handleLoadRecentWinBallDataFinished()
{
    qDebug() << "load recent win ball data finished";
}

void DLTWINBallManager::handleLoadRecentWinBallDataFailed()
{
    qDebug() << "load recent win ball data failed";
}

void DLTWINBallManager::handleLoadSuggestBallDataFinished()
{
    qDebug() << "load suggest ball data finished";
}

void DLTWINBallManager::handleLoadSuggestBallDataFailed()
{
    qDebug() << "load suggest ball data failed";
}

